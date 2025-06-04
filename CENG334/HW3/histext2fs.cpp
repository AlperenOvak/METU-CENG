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

#include "ext2fs_print.h" // Contains print functions for ext2 structures
#include "ext2fs.h"   // Contains struct ext2_super_block, ext2_block_group_descriptor, ext2_inode, ext2_dir_entry

// Global variables for convenience:
static int              img_fd        = -1;        // File descriptor for the ext2 image
static uint32_t         block_size    = 0;         // Computed block size (bytes)
static uint16_t         inode_size    = 0;         // Size of each inode (bytes)
static uint32_t         inodes_per_group = 0;      // From superblock
static std::vector<ext2_block_group_descriptor> bgdt; // Block‐group descriptor table 

// Forward declarations:
void read_superblock_and_bgdt(const char *image_path);
void read_inode(uint32_t inode_num, ext2_inode &out_inode);
void traverse_directory(uint32_t inode_num, int depth, std::ofstream &out);

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
    if (dirent_ft == EXT2_D_DTYPE) return true;
    if (dirent_ft == EXT2_D_FTYPE || dirent_ft == 0)
        return ((inode_mode & 0xF000) == EXT2_I_DTYPE);
    return false;
}

void traverse_directory(uint32_t inode_num, int depth, std::ofstream &out)
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
            if (d->inode != 0 &&!(name == "." || name == "..")) {
                // Print the entry with the correct number of dashes
                for (int i = 0; i < depth; i++) {
                    out.put('-');
                }
                out.put(' ');
                out << d->inode << ':' << name;
                if (is_directory(d->file_type, dir_inode.mode)) {
                    out.put('/');
                }
                out.put('\n');

                if(is_directory(d->file_type, dir_inode.mode)) {
                    // If it’s a directory, recurse (depth + 1)
                    traverse_directory(d->inode, depth + 1, out);
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
                        for (int d = 0; d < depth; ++d) out << "-";
                        out << " (" << ghost_entry->inode << ":" << ghost_name;
                        ext2_inode child_inode;
                        read_inode(ghost_entry->inode, child_inode);

                        if (is_directory(ghost_entry->file_type, child_inode.mode)) {
                            out << "/";
                        }
                        out << ")" << std::endl;
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


int main(int argc, char **argv)
{
    if (argc != 4) {
        std::fprintf(stderr, "Usage: %s <image_path> <state_output_path> <history_output_path>\n", argv[0]);
        return 1; // Exit with error if incorrect number of arguments
    }

    const char *image_path    = argv[1];
    const char *state_path    = argv[2];
    // const char *history_path = argv[3];  // Not used in Phase 1

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

    state_out << "- 2:root/\n";

    traverse_directory(EXT2_ROOT_INODE, 2, state_out);

    state_out.close();
    close(img_fd);
    std::fprintf(stderr, "Finished\n");
    return EXIT_SUCCESS;
}