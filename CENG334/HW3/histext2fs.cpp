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
        std::fprintf(stderr,
                     "Error: not a valid ext2 image (magic=0x%x)\n",
                     sb.magic);
        std::exit(EXIT_FAILURE);
    }

    // Print superblock details (for debugging):
    print_super_block(&sb);

    // Compute global parameters:
    block_size         = static_cast<uint32_t>(1 << (sb.log_block_size + 10)); 
    inode_size         = sb.inode_size;
    inodes_per_group   = sb.inodes_per_group;

    // Print computed parameters (for debugging):
    std::fprintf(stderr, "  block_size = %u bytes\n", block_size);

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

    //pread_or_die(img_fd, &bgdt[0], sizeof(ext2_block_group_descriptor), bgdt_offset);

    // Print group descriptor details (for debugging):
    print_group_descriptor(&bgdt[0]);
}

/**
 * read_inode:
 *   Given an inode number (1‐based), compute which block group it belongs to,
 *   locate the correct entry in that group’s inode table, and read the inode into out_inode.
 *
 * Inode numbering:
 *   group_index = (inode_num - 1) / inodes_per_group
 *   local_index = (inode_num - 1) % inodes_per_group
 *
 * Table block = bgdt[group_index].inode_table
 * inode_offset = (table_block * block_size) + (local_index * inode_size).
 */
void read_inode(uint32_t inode_num, ext2_inode &out_inode)
{
    if (inode_num == 0) {
        std::fprintf(stderr, "Error: attempt to read inode 0\n");
        std::exit(EXIT_FAILURE);
    }

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

/**
 * traverse_directory:
 *   Recursively walks the directory whose inode is inode_num,
 *   printing each child at the given depth to 'out'.  Depth==2 => prefix “-- ”.
 *
 * Algorithm:
 *   1) read this inode → verify it’s a directory (mode & 0xF000 == EXT2_I_DTYPE).
 *   2) gather all data‐block pointers (direct + single‐indirect). 
 *   3) for each non‐zero block pointer:
 *        • read an entire block into a buffer
 *        • scan ext2_dir_entry entries (offset = 0; while offset < block_size)
 *          – skip if dir->inode == 0
 *          – read dir->name (length = name_length), null‐terminate
 *          – skip “.” and “..”
 *          – determine if entry is directory via dir->file_type (==2) or by reading its inode’s mode
 *          – print “[depth × '-'] inode:name[/]\n”
 *          – if directory, recurse with depth+1
 */
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
            if (d->inode == 0) {
                offset += d->length;
                continue;
            }

            // Extract the name
            uint16_t name_len = d->name_length;
            std::string name;
            name.reserve(name_len + 1);
            name.assign(buffer.data() + offset + sizeof(ext2_dir_entry),
                        buffer.data() + offset + sizeof(ext2_dir_entry) + name_len);
            //name.push_back('\0'); no need to null-terminate, we use std::string

            // Skip “.” and “..”
            if (name == "." || name == "..") {
                std::fprintf(stderr, "Skipping entry: %s\n", name.c_str());
                offset += d->length;
                continue;
            }

            // Determine if entry is a directory
            bool is_dir = false;
            if (d->file_type == EXT2_D_DTYPE) {
                is_dir = true;
            } else if (d->file_type == EXT2_D_FTYPE || d->file_type == 0) {
                // Fall back on reading the child inode’s mode
                ext2_inode child_inode;
                read_inode(d->inode, child_inode);
                if ((child_inode.mode & 0xF000) == EXT2_I_DTYPE) {
                    is_dir = true;
                }
            }

            // Print the entry with the correct number of dashes
            for (int i = 0; i < depth; i++) {
                out.put('-');
            }
            out.put(' ');
            out << d->inode << ':' << name;
            if (is_dir) {
                out.put('/');
            }
            out.put('\n');

            // If it’s a directory, recurse (depth + 1)
            //if (is_dir) {
                traverse_directory(d->inode, depth + 1, out);
            //}

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

    // 1) Open the ext2 image file read‐only:
    img_fd = open(image_path, O_RDONLY);
    if (img_fd < 0) {
        perror("open(image)");
        std::fprintf(stderr, "Error: could not open '%s'\n", image_path);
        return 1; // Exit with error if image cannot be opened
    }

    // 2) Read superblock (offset = 1024 bytes) and BGDT for group 0:
    read_superblock_and_bgdt(image_path);

    // 3) Open the state_output file for writing:
    std::ofstream state_out(state_path, std::ios::out | std::ios::trunc);
    if (!state_out.is_open()) {
        std::fprintf(stderr, "Error: could not open '%s' for writing\n", state_path);
        close(img_fd);
        return EXIT_FAILURE;
    }

    // 4) Print the root line at depth 1:
    //    “- 2:root/”
    state_out << "- 2:root/\n";

    // 5) Recursively traverse inode 2 (root), starting at depth 2 (“--”):
    traverse_directory(EXT2_ROOT_INODE, 2, state_out);
    // 6) Clean up:
    state_out.close();
    close(img_fd);
    std::fprintf(stderr, "Finished\n");
    return EXIT_SUCCESS;
}