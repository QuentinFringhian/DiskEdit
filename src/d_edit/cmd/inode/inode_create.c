#include <time.h>
#include "d_edit/d_edit_cmd.h"

int alloc_inode(disk_t *disk, unsigned int mode)
{
    FILE *disk_file = fopen(disk->d_path, "r+");
    int _inode_number = -1;

    for (unsigned int i = 0; i < disk->super_block->num_inodes; i++)
        if (disk->inode_table[i].mode == 0) {
            _inode_number = i;
            break;
        }
    if (_inode_number == -1) return -1;
    disk->inode_table[_inode_number].mode = mode;
    disk->inode_table[_inode_number].size = 0;
    disk->inode_table[_inode_number].locked = 0;
    disk->inode_table[_inode_number].indirect_block = -1;
    disk->inode_table[_inode_number].date = (unsigned int)time(NULL);
    for (int i = 0; i < 6; i++)
        disk->inode_table[_inode_number].blocks[i] = 0;
    fseek(disk_file, disk->super_block->block_size + _inode_number * disk->super_block->inode_size, SEEK_SET);
    fwrite(&disk->inode_table[_inode_number], 1, disk->super_block->inode_size, disk_file);
    fclose(disk_file);
    return _inode_number;
}

void free_inode(disk_t *disk, int inode_number)
{
    FILE *disk_file = fopen(disk->d_path, "r+");
    unsigned int remaining_free = disk->inode_table[inode_number].size;

    for (int i = 0; i < BLOCK_PER_NODE && remaining_free != 0; i++) {
        if (remaining_free > disk->super_block->block_size) {
            free_block(disk, disk->inode_table[inode_number].blocks[i]);
            remaining_free -= disk->super_block->block_size;
        } else {
            free_block(disk, disk->inode_table[inode_number].blocks[i]);
            remaining_free = 0;
        }
    }
    disk->inode_table[inode_number].mode = 0;
    disk->inode_table[inode_number].size = 0;
    disk->inode_table[inode_number].locked = 0;
    disk->inode_table[inode_number].indirect_block = -1;
    disk->inode_table[inode_number].date = 0;
    for (int i = 0; i < 6; i++)
        disk->inode_table[inode_number].blocks[i] = 0;
    fseek(disk_file, disk->super_block->block_size + inode_number * disk->super_block->inode_size, SEEK_SET);
    fwrite(&disk->inode_table[inode_number], 1, disk->super_block->inode_size, disk_file);
    fclose(disk_file);
}