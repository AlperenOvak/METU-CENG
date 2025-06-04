#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "ext2fs_print.h" // Contains print functions for ext2 structures
#include "ext2fs.h"   // Contains struct ext2_super_block, ext2_block_group_descriptor, ext2_inode, ext2_dir_entry

// Global variables for convenience:
static int              img_fd        = -1;        // File descriptor for the ext2 image
static uint32_t         block_size    = 0;         // Computed block size (bytes)
static uint16_t         inode_size    = 0;         // Size of each inode (bytes)
static uint32_t         inodes_per_group = 0;      // From superblock
static std::vector<ext2_block_group_descriptor> bgdt; // Block‐group descriptor table 

struct InodeOccurrence {
    std::string full_path;     // e.g. "/foo/bar/baz.txt"
    uint32_t    parent_inode;  // e.g. 12
    bool        isLive;        // true if from live directory‐entry, false if from ghost
};

struct InodeInfo {
    uint32_t            inode_num;     // just store the inode number itself
    ext2_inode         inode_data;     // copy of the on‐disk inode (to get timestamps, size, mode, etc.)
    bool             is_directory;     // true if this inode is a directory 
    std::vector<InodeOccurrence> occurrences; // all parent/name pairs where this inode was found
};

enum class ActionType {
    TOUCH,
    MKDIR,
    RM,
    RMDIR,
    MV,
    UNKNOWN
};

struct ActionRecord {
    // If hasTimestamp == false, print “?” instead of timestamp
    uint32_t       timestamp;
    bool           hasTimestamp;

    ActionType     action;            // e.g. TOUCH or MKDIR

    // ARGS: for touch/mkdir/rm/rmdir, this is exactly one path string.
    // For mv, it should contain exactly two strings: {old_path, new_path}.
    std::vector<std::string> args;

    // AFFECTED_DIRECTORIES: 
    //   - For touch/mkdir/rm/rmdir, exactly one parent-inode. 
    //   - For mv, exactly two: {old_parent, new_parent}.
    std::vector<uint32_t>    affected_dirs;

    // AFFECTED_INODES: always contains exactly one inode number.
    std::vector<uint32_t>    affected_inodes;
};

static std::string actionTypeToString(ActionType a) {
    switch (a) {
        case ActionType::TOUCH:  return "touch";
        case ActionType::MKDIR:  return "mkdir";
        case ActionType::RM:     return "rm";
        case ActionType::RMDIR:  return "rmdir";
        case ActionType::MV:     return "mv";
        case ActionType::UNKNOWN:return "?";
    }
    return "?"; // fallback
}

static std::string stringifyArgs(const std::vector<std::string> &v) {
    if (v.empty()) {
        return "[?]";
    }
    std::string out = "[";
    for (size_t i = 0; i < v.size(); i++) {
        out += v[i];
        if (i + 1 < v.size()) {
            out += " ";
        }
    }
    out += "]";
    return out;
}


static std::string stringifyU32List(const std::vector<uint32_t> &v) {
    if (v.empty()) {
        return "[?]";
    }
    std::string out = "[";
    for (size_t i = 0; i < v.size(); i++) {
        if( v[i] == -1) {
            out += "?";
        } else {
            out += std::to_string(v[i]);
        }
        if (i + 1 < v.size()) {
            out += " ";
        }
    }
    out += "]";
    return out;
}


void sortAndPrintHistory(std::vector<ActionRecord> &output_list,
                         std::ofstream &out)
{
    // 1) Stable‐sort by timestamp, pushing all hasTimestamp == false to the end:
    std::stable_sort(
        output_list.begin(),
        output_list.end(),
        [](auto const &A, auto const &B) {
            // If both have timestamps, compare them numerically
            return A.timestamp < B.timestamp; //TODO: fix it later
            if (A.hasTimestamp && B.hasTimestamp) {
                return A.timestamp < B.timestamp;
            }
            // If A has a timestamp but B does not, A comes first
            if (A.hasTimestamp && !B.hasTimestamp) {
                return true;
            }
            // If B has a timestamp but A does not, B comes first => return false
            if (!A.hasTimestamp && B.hasTimestamp) {
                return false;
            }
            // If neither has a timestamp, keep original order (stable_sort will do that)
            return false;
        }
    );

    // 2) Print each record in the required format:
    //    TIMESTAMP ACTION [ARGS] [AFFECTED_DIRECTORIES] [AFFECTED_INODES]
    for (auto const &rec : output_list) {
        // (a) TIMESTAMP or "?"
        if (rec.hasTimestamp) {
            out << rec.timestamp;
        } else {
            out << "?";
        }
        out << " ";

        // (b) ACTION or "?"
        out << actionTypeToString(rec.action);
        out << " ";

        // (c) ARGS
        out << stringifyArgs(rec.args);
        out << " ";

        // (d) AFFECTED_DIRECTORIES
        out << stringifyU32List(rec.affected_dirs);
        out << " ";

        // (e) AFFECTED_INODES
        out << stringifyU32List(rec.affected_inodes);

        out << "\n";
    }
}

static std::unordered_map<uint32_t, InodeInfo> inode_map;
std::vector<ActionRecord> output_list;

// Forward declarations:
void read_superblock_and_bgdt(const char *image_path);
void read_inode(uint32_t inode_num, ext2_inode &out_inode);
void traverse_directory(uint32_t inode_num, int depth, std::ofstream &out);

static void record_inode_occurrence(uint32_t inode_num,
                                     const std::string &full_path,
                                     uint32_t parent_inode,
                                     bool is_direc,
                                     bool isLiveFlag)
{
    // 3.a) If this inode_num isn’t already in the map, read it once
    auto it = inode_map.find(inode_num);
    if (it == inode_map.end()) {
        // First time we’ve seen this inode_num ⇒ populate inode_data
        InodeInfo info;
        // read_inode fills “info.inode_data” from disk
        info.inode_num = inode_num; // Store the inode number
        info.is_directory = is_direc; // Default to false, will be set later if needed
        read_inode(inode_num, info.inode_data);
        inode_map.emplace(inode_num, std::move(info));
        it = inode_map.find(inode_num);
    }

    // 3.b) Build a new InodeOccurrence and append it
    InodeOccurrence occ;
    occ.full_path   = full_path;     // e.g. "/parent/child.txt"
    occ.parent_inode = parent_inode; // numeric inode of the directory containing this entry
    occ.isLive      = isLiveFlag;    // true for a normal entry, false for a ghost entry

    it->second.occurrences.push_back(std::move(occ));
}


/**
 * Helper: Read exactly 'sz' bytes from offset 'off' in img_fd into 'buf'.
 * Exits on any error.
 */
static void pread_or_die(int fd, void *buf, size_t sz, off_t off)
{
    ssize_t ret = pread(fd, buf, sz, off);
    if (ret < 0 || static_cast<size_t>(ret) != sz) {
        perror("pread");
        std::exit(EXIT_FAILURE);
    }
}

/**
 * read_superblock_and_bgdt:
 *   • Reads the ext2 superblock at offset 1024.
 *   • Computes block_size = 1024 << log_block_size.
 *   • Reads the block‐group descriptor table (we need only group 0 here).
 */
void read_superblock_and_bgdt(const char * /*unused*/)
{
    // 2.1 Read superblock at byte offset 1024:
    ext2_super_block sb;
    constexpr off_t SUPER_OFFSET = 1024;
    pread_or_die(img_fd, &sb, sizeof(ext2_super_block), SUPER_OFFSET);

    // Validate magic:
    if (sb.magic != EXT2_SUPER_MAGIC) {
        std::fprintf(stderr,"Error: not a valid ext2 image (magic=0x%x)\n",sb.magic);
        std::exit(EXIT_FAILURE);
    }

    // Print superblock details (for debugging):
    print_super_block(&sb);

    // Compute global parameters:
    block_size         = static_cast<uint32_t>(1 << (sb.log_block_size + 10)); 
    inode_size         = sb.inode_size;
    inodes_per_group   = sb.inodes_per_group;

    // 2.2 Locate BGDT:
    // If block_size == 1024, BGDT is at byte 2048 (block 2). Otherwise, at block 1.
    off_t bgdt_offset  = (block_size == 1024 ? 2048LL : static_cast<off_t>(block_size));


    int bgdt_block_count = (sb.block_count + sb.blocks_per_group - 1) / sb.blocks_per_group; // Total number of block groups
    std::fprintf(stderr, "Total block groups: %d\n", bgdt_block_count);
    bgdt.resize(bgdt_block_count); // Resize to number of groups
    for(int i = 0; i < bgdt_block_count; i++) {
        //read the group descriptor for each group
        off_t offset = bgdt_offset + i * sizeof(ext2_block_group_descriptor);
        if (pread(img_fd, &bgdt[i], sizeof(ext2_block_group_descriptor), offset) != sizeof(ext2_block_group_descriptor)) {
            std::fprintf(stderr, "Error reading block group descriptor %d\n", i);
            std::exit(EXIT_FAILURE);    
        }
    }

    // Print group descriptor details (for debugging):
    print_group_descriptor(&bgdt[0]);
}

void read_inode(uint32_t inode_num, ext2_inode &out_inode)
{
    uint32_t zero_based = inode_num -1;
    uint32_t group      = zero_based / inodes_per_group;   
    uint32_t index      = zero_based % inodes_per_group;

    uint32_t table_block = bgdt[group].inode_table;        // first block of that group’s inode table
    off_t    table_off   = static_cast<off_t>(table_block) * block_size;
    off_t    inode_off   = table_off + static_cast<off_t>(index) * inode_size;

    // Read exactly inode_size bytes:
    /*fprintf(stderr,
    "DEBUG: block_size=%u, inode_size=%u, inodes_per_group=%u, bgdt[0].inode_table=%u, inode_off=%u\n",
    block_size, sizeof(ext2_inode), inodes_per_group, bgdt[0].inode_table,inode_off);*/
    pread_or_die(img_fd, &out_inode, sizeof(ext2_inode), inode_off);
}

void collect_all_blocks(ext2_inode &inode, std::vector<uint32_t> &blocks)
{
    // Collect direct blocks
    for (int i = 0; i < EXT2_NUM_DIRECT_BLOCKS; i++) {
        if (inode.direct_blocks[i] != 0) {
            blocks.push_back(inode.direct_blocks[i]);
        }
    }

    std::vector<uint32_t> block_buf(block_size / sizeof(uint32_t)); // Buffer to read indirect blocks
    // Collect single indirect block
    if (inode.single_indirect != 0) {
        off_t single_indirect_off = static_cast<off_t>(inode.single_indirect) * block_size; //offset for single indirect block
        pread_or_die(img_fd, block_buf.data(), block_size, single_indirect_off);
        for (uint32_t blk : block_buf) {
            if (blk != 0) {
                blocks.push_back(blk);
            }
        }
    }

    if(inode.double_indirect != 0) {
        // Collect double indirect block
        off_t double_indirect_off = static_cast<off_t>(inode.double_indirect) * block_size; //offset for double indirect block
        pread_or_die(img_fd, block_buf.data(), block_size, double_indirect_off);
        for (uint32_t blk : block_buf) {
            if (blk != 0) {
                // Read each single indirect block, same logic as above
                off_t single_indirect_off = static_cast<off_t>(blk) * block_size;
                pread_or_die(img_fd, block_buf.data(), block_size, single_indirect_off);
                for (uint32_t sub_blk : block_buf) {
                    if (sub_blk != 0) {
                        blocks.push_back(sub_blk);
                    }
                }
            }
        }
    }

    if(inode.triple_indirect != 0) {
        // Collect triple indirect block
        off_t triple_indirect_off = static_cast<off_t>(inode.triple_indirect) * block_size; //offset for triple indirect block
        pread_or_die(img_fd, block_buf.data(), block_size, triple_indirect_off);
        for (uint32_t blk : block_buf) {
            if (blk != 0) {
                // Read each double indirect block, same logic as above
                off_t double_indirect_off = static_cast<off_t>(blk) * block_size;
                pread_or_die(img_fd, block_buf.data(), block_size, double_indirect_off);
                for (uint32_t sub_blk : block_buf) {
                    if (sub_blk != 0) {
                        // Read each single indirect block, same logic as above
                        off_t single_indirect_off = static_cast<off_t>(sub_blk) * block_size;
                        pread_or_die(img_fd, block_buf.data(), block_size, single_indirect_off);
                        for (uint32_t sub_sub_blk : block_buf) {
                            if (sub_sub_blk != 0) {
                                blocks.push_back(sub_sub_blk);
                            }
                        }
                    }
                }
            }
        }
    }
}

bool is_directory(uint8_t dirent_ft, uint16_t inode_mode)
{
    return dirent_ft == EXT2_D_DTYPE || (dirent_ft == 0 && (inode_mode & 0x4000));
}

void traverse_directory(uint32_t inode_num, int depth, const std::string &curr_path, std::ofstream &out,bool isLive = true)
{
    // 1) Read the inode for inode_num
    ext2_inode dir_inode;
    read_inode(inode_num, dir_inode);
    // Print inode details (for debugging):
    print_inode(&dir_inode, inode_num);

    // 2) Verify it’s actually a directory
    if ((dir_inode.mode & 0xF000) != EXT2_I_DTYPE) {
        // Not a directory – nothing to traverse
        return;
    }

    // 3) Gather only the direct block pointers (skip single/double/triple indirect)
    std::vector<uint32_t> blocks;
    blocks.reserve(EXT2_NUM_DIRECT_BLOCKS); // No need
    collect_all_blocks(dir_inode, blocks); // Collect direct and single/doucle/triple indirect blocks

    // 4) For each direct block, read the full block and scan directory entries
    std::vector<char> buffer(block_size);
    for (uint32_t blk : blocks) {
        off_t data_off = static_cast<off_t>(blk) * block_size;
        pread_or_die(img_fd, buffer.data(), block_size, data_off);

        off_t offset = 0;
        while (offset < static_cast<off_t>(block_size)) {
            ext2_dir_entry *d = reinterpret_cast<ext2_dir_entry *>(buffer.data() + offset);
            
            // Extract the name
            uint16_t name_len = d->name_length;
            std::string name;
            name.reserve(name_len + 1);
            name.assign(buffer.data() + offset + sizeof(ext2_dir_entry),
                        buffer.data() + offset + sizeof(ext2_dir_entry) + name_len);
            //name.push_back('\0'); no need to null-terminate, we use std::string

            // Skip “.” and “..”
            if ( d->inode != 0 &&!(name == "." || name == "..")) {
                // Print the entry with the correct number of dashes
                if(isLive){
                    for (int i = 0; i < depth; i++) {
                    out.put('-');
                    }
                    out.put(' ');
                    out << d->inode << ':' << name;
                    if (is_directory(d->file_type, dir_inode.mode)) {
                        out.put('/');
                    }
                    out.put('\n');
                }
                std::string child_full_path = curr_path + "/" + name;

                record_inode_occurrence(d->inode,
                                        child_full_path,
                                        inode_num,
                                        is_directory(d->file_type, dir_inode.mode),
                                        /*isLiveFlag=*/isLive);

                if(is_directory(d->file_type, dir_inode.mode)) {
                    // If it’s a directory, recurse (depth + 1)
                    traverse_directory(d->inode, depth + 1, child_full_path, out, isLive);
                }
            }
            // Scan for ghosts in the gap
            uint32_t min_len = 8 + ((d->name_length + 3) & ~3);
            uint32_t gap_start = offset + min_len;
            uint32_t gap_end = offset + d->length;

            uint32_t ghost_offset = gap_start;
            while (ghost_offset + 8 <= gap_end) {
                auto *ghost_entry = reinterpret_cast<ext2_dir_entry*>(buffer.data() + ghost_offset);

                if (ghost_entry->inode != 0) {
                    // Safe string for ghost entry
                    char ghost_buf[256 + 1] = {};
                    memcpy(ghost_buf, ghost_entry->name, ghost_entry->name_length);
                    ghost_buf[ghost_entry->name_length] = '\0';

                    std::string ghost_name(ghost_buf);

                    if (ghost_name != "." && ghost_name != "..") {
                        ext2_inode child_inode;
                        read_inode(ghost_entry->inode, child_inode);
                        if(isLive){
                            for (int d = 0; d < depth; ++d) out << "-";
                            out << " (" << ghost_entry->inode << ":" << ghost_name;
                            if (is_directory(ghost_entry->file_type, child_inode.mode)) {
                                out << "/";
                            }
                            out << ")" << std::endl;
                        }

                        std::string ghost_full_path = curr_path + "/" + ghost_name;

                        record_inode_occurrence(ghost_entry->inode,
                                                ghost_full_path,
                                                inode_num,
                                                is_directory(ghost_entry->file_type, child_inode.mode),
                                                /*isLiveFlag=*/false);

                        std::fprintf(stderr, "Ghost entry: %s (inode %u)\n", ghost_name.c_str(), ghost_entry->inode);

                        if (is_directory(ghost_entry->file_type, child_inode.mode)) {
                            std::fprintf(stderr, "Ghost directory: %s\n", ghost_name.c_str());
                            traverse_directory(ghost_entry->inode,
                                               depth + 1,
                                               ghost_full_path,
                                               out,
                                               /* isLive = */ false);
                        }
                    }
                }

                if (ghost_entry->length == 0) break;
                ghost_offset += ghost_entry->length;
            }

            if (d->length == 0) break;
            offset += d->length;
        }
    }
}

bool detectSimpleCreation(uint32_t inode_no, const InodeInfo &info,
                          uint32_t access_time, uint32_t change_time,
                          uint32_t deletion_time, uint32_t modification_time){
    if(modification_time == access_time &&
       modification_time == change_time &&
       deletion_time == 0) {
        // If all timestamps are equal and deletion time is zero, it’s a simple creation
        std::fprintf(stderr, "Inode %u is a simple creation.\n", inode_no);
        ActionRecord record;
        record.timestamp = access_time;
        record.hasTimestamp = true;
        record.action = info.is_directory ? ActionType::MKDIR : ActionType::TOUCH;
        record.args.push_back(info.occurrences[0].full_path); // Use the first occurrence's path
        record.affected_dirs.push_back(info.occurrences[0].parent_inode); // Use the first occurrence's parent inode
        record.affected_inodes.push_back(inode_no); // Add the inode number itself
        
        output_list.push_back(record);
        //std::fprintf(stderr, "Recorded simple creation for inode %u: %s\n", inode_no, info.occurrences[0].full_path.c_str());
        return true;
    } 
    
    return false; // Otherwise, it’s not a simple creation
}

bool detectCreation(uint32_t inode_no, const InodeInfo &info, uint32_t access_time,
                    uint32_t change_time, uint32_t deletion_time,
                    uint32_t modification_time){
    // 1) First try the “all‐equal” rule
        if (detectSimpleCreation(inode_no, info,
                                 access_time, change_time,
                                 deletion_time, modification_time))
        {
            return true; // move on to next inode_no
        }

        // 2) Fallback: try to match child.atime == parent.mtime
        bool foundMatch = false;
        for (const InodeOccurrence &occ : info.occurrences) {

            // Look up that parent’s modification_time
            const auto it_parent = inode_map.find(occ.parent_inode);  // TODO: embed the parent inode in InodeOccurrence?
            if (it_parent == inode_map.end()) {
                continue;
            }
            uint32_t parent_mtime = it_parent->second.inode_data.modification_time;

            // If child’s access_time == parent’s modification_time, 
            // then that is likely the exact create moment
            if (access_time != 0 && access_time == parent_mtime) {
                std::fprintf(stderr,
                             "Inode %u creation matched parent mtime: %u\n",
                             inode_no, access_time);

                ActionRecord record;
                record.timestamp     = access_time;
                record.hasTimestamp  = true;
                record.action        = info.is_directory
                                         ? ActionType::MKDIR
                                         : ActionType::TOUCH;

                // Use this live occurrence as the creation point
                record.args.push_back(occ.full_path);
                record.affected_dirs.push_back(occ.parent_inode);
                record.affected_inodes.push_back(inode_no);

                output_list.push_back(std::move(record));
                foundMatch = true;
                break;
            }
        }

        if (foundMatch) {
            return true; // we already emitted a creation
        }

        if(info.occurrences.size() == 1){
            // 3) If we get here and there is exactly one occurrence, assume known timestamp
            std::fprintf(stderr,
                         "Inode %u has one occurrence → fallback creation (%u)\n",
                         inode_no, access_time);

            ActionRecord record;
            record.timestamp      = access_time;      // known timestamp
            record.hasTimestamp   = true;
            record.action         = info.is_directory
                                      ? ActionType::MKDIR
                                      : ActionType::TOUCH;

            // Use the single occurrence’s path as “args”
            record.args.push_back(info.occurrences[0].full_path);
            record.affected_dirs.push_back(info.occurrences[0].parent_inode);
            record.affected_inodes.push_back(inode_no);

            output_list.push_back(std::move(record));
            return true; // move on to next inode_no
        }

        // 4) If we get here and there are exactly two occurrences, assume known timestamp but we cnat prove”
        if (info.occurrences.size() == 2) {
            // Identify which is ghost and which is live
            const InodeOccurrence *ghost_occ = nullptr;
            const InodeOccurrence *live_occ  = nullptr;
            for (const auto &occ : info.occurrences) {
                if (occ.isLive) {
                    live_occ = &occ;
                } else {
                    ghost_occ = &occ;
                }
            }
            if (live_occ && ghost_occ) {
                std::fprintf(stderr,
                             "Inode %u has two occurrences → fallback creation (%u)\n",
                             inode_no, access_time);

                ActionRecord record;
                record.timestamp      = access_time;      // unknown
                record.hasTimestamp   = true;
                record.action         = info.is_directory
                                          ? ActionType::MKDIR
                                          : ActionType::TOUCH;

                // Use the final (live) path as “args”
                record.args.push_back(ghost_occ->full_path);

                // The “creation parent” is where the ghost entry was
                record.affected_dirs.push_back(ghost_occ->parent_inode);

                record.affected_inodes.push_back(inode_no);

                output_list.push_back(std::move(record));
                return true; // move on to next inode_no
            }
        }

        // *** NEW: 5) “Parent‐access_time” rule for ghost entries:
        //
        // If we haven’t emitted a creation yet, look at every ghost occurrence.
        // If exactly one ghost_occ has parent.access_time < child.access_time, assume that’s the creation.
        {
            std::vector<const InodeOccurrence*> ghost_candidates;
            for (const auto &occ : info.occurrences) {
                if (!occ.isLive) {
                    auto it_par = inode_map.find(occ.parent_inode);
                    if (it_par != inode_map.end()) {
                        uint32_t parent_atime = it_par->second.inode_data.access_time;
                        // parent_atime == parent creation time
                        if (parent_atime < access_time) {
                            ghost_candidates.push_back(&occ);
                        }
                    }
                }
            }
            if (ghost_candidates.size() == 1) {
                const InodeOccurrence *chosen = ghost_candidates.front();
                std::fprintf(stderr,
                             "Inode %u creation inferred from one ghost with parent atime < child atime\n",
                             inode_no);

                ActionRecord record;
                record.timestamp    = access_time;  // use child’s atime as creation
                record.hasTimestamp = true;
                record.action       = info.is_directory
                                        ? ActionType::MKDIR
                                        : ActionType::TOUCH;

                record.args.push_back(chosen->full_path);
                record.affected_dirs.push_back(chosen->parent_inode);
                record.affected_inodes.push_back(inode_no);

                output_list.push_back(std::move(record));
                return true; // move on to next inode_no
            }
        }

        // 6) Otherwise, we cant know where it created, so we just emit a “?” record
        std::fprintf(stderr,
                     "Inode %u has no known creation place, emitting fallback record\n",
                     inode_no); 
        ActionRecord record;
        record.timestamp = access_time;
        record.hasTimestamp = true;
        record.action = info.is_directory ? ActionType::MKDIR : ActionType::TOUCH;
        record.args.push_back("?");
        record.affected_dirs.push_back(-1); // No known parent
        record.affected_inodes.push_back(inode_no); // Add the inode number itself

        output_list.push_back(std::move(record));
        return false; // we emitted a fallback record, so we can move on to next inode_no    
}




//-----------------------------------------------------------------------------
// Print the contents of inode_map into 'out'.
//-----------------------------------------------------------------------------
static void dump_inode_map(std::ofstream &out) {
    out << "==== BEGIN: Inode Map Dump ====\n\n";

    for (const auto &pair : inode_map) {
        uint32_t inode_no    = pair.first;
        const InodeInfo &info = pair.second;

        {// --- 1) Print the inode number and its raw timestamps ---
        // (Assuming ext2_inode has fields i_ctime, i_mtime, i_atime as uint32_t.)
        out << "Inode #" << inode_no << ":\n";
        out << "    atime = " << info.inode_data.access_time
            << "    ctime = " << info.inode_data.change_time
            << "    mtime = " << info.inode_data.modification_time // we don't need it
            << "    dtime = " << info.inode_data.deletion_time << "\n";

        // --- 2) Print how many times we saw it ---
        out << "    [Occurrences: " << info.occurrences.size() << "]\n";

        // --- 3) List each occurrence on its own line ---
        for (const auto &occ : info.occurrences) {
            out << "      - full_path = \"" << occ.full_path << "\"\n";
            out << "        parent_inode = " << occ.parent_inode
                << "    (isLive = " << (occ.isLive ? "true" : "false") << ")\n";
        }
        out << "\n";
}


        uint32_t access_time = info.inode_data.access_time;
        uint32_t change_time = info.inode_data.change_time;
        uint32_t deletion_time = info.inode_data.deletion_time;
        uint32_t modification_time = info.inode_data.modification_time;

        bool is_creation = detectCreation(inode_no, info,
                                                access_time, change_time,
                                                deletion_time, modification_time); // Detect the creation of inode

        
    }

    out << "====  END: Inode Map Dump  ====\n";
}



int main(int argc, char **argv)
{
    if (argc != 4) {
        std::fprintf(stderr, "Usage: %s <image_path> <state_output_path> <history_output_path>\n", argv[0]);
        return 1; // Exit with error if incorrect number of arguments
    }

    const char *image_path    = argv[1];
    const char *state_path    = argv[2];
    const char *history_path  = argv[3];  // Not used in Phase 1

    img_fd = open(image_path, O_RDONLY);
    if (img_fd < 0) {
        perror("open(image)");
        std::fprintf(stderr, "Error: could not open '%s'\n", image_path);
        return 1; // Exit with error if image cannot be opened
    }

    read_superblock_and_bgdt(image_path);

    std::ofstream state_out(state_path, std::ios::out | std::ios::trunc);
    if (!state_out.is_open()) {
        std::fprintf(stderr, "Error: could not open '%s' for writing\n", state_path);
        close(img_fd);
        return EXIT_FAILURE;
    }

    std::ofstream history_out(history_path, std::ios::out | std::ios::trunc);
    if (!history_out.is_open()) {
        std::fprintf(stderr, "Error: could not open '%s' for writing\n", history_path);
        close(img_fd);
        return EXIT_FAILURE;
    }

    state_out << "- 2:root/\n";

    traverse_directory(EXT2_ROOT_INODE, 2, "", state_out,true);

    dump_inode_map(state_out);

    sortAndPrintHistory(output_list, history_out);

    state_out.close();
    close(img_fd);
    std::fprintf(stderr, "Finished\n");
    return EXIT_SUCCESS;
}