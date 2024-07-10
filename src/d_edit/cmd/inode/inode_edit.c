#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"

void _inode_save(disk_t *d, int inode_number, inode_t inode)
{
    FILE *d_file = fopen(d->d_path, "r+");
    size_t _inode_offset = d->super_block->block_size + inode_number * d->super_block->inode_size;

    if (fseek(d_file, _inode_offset, SEEK_SET) == -1)
        return;
    if (fwrite(&inode, d->super_block->inode_size, 1, d_file) != 1)
        return;
    d->inode_table[inode_number] = inode;
    fclose(d_file);
}

short *_get_allocated_blocks(inode_t inode, unsigned int block_size)
{
    short *free_blocks = malloc(sizeof(short) * BLOCK_PER_NODE);
    unsigned int _remaining_size = inode.size;

    if (free_blocks == NULL)
        return NULL;
    for (int i = 0; i < BLOCK_PER_NODE; i++)
        free_blocks[i] = -1;
    if (_remaining_size == 0 || inode.mode == 0)
        return free_blocks;
    for (int j = 0; _remaining_size != 0; j++) {
        free_blocks[j] = inode.blocks[j];
        if (_remaining_size > block_size)
            _remaining_size -= block_size;
        else
            _remaining_size = 0;
    }
    return free_blocks;
}

void _free_no_more_used_blocks(disk_t *d, inode_t inode, short *allocated_blocks, unsigned int new_size)
{
    unsigned int _remaining_size = inode.size;
    unsigned int _new_remaining_size = new_size;

    for (int i = 0; _remaining_size != 0; i++) {
        if (_remaining_size <= new_size)
            break;
        if (_new_remaining_size == 0)
            free_block(d, allocated_blocks[i]);
        _remaining_size = _remaining_size > d->super_block->block_size ? _remaining_size - d->super_block->block_size : 0;
        _new_remaining_size = _new_remaining_size > d->super_block->block_size ? _new_remaining_size - d->super_block->block_size : 0;
    }
}

int inode_edit(disk_t *disk, int inode_number, unsigned char *data, unsigned int size)
{
    inode_t _inode = disk->inode_table[inode_number];
    short *_allocated_blocks = _get_allocated_blocks(_inode, disk->super_block->block_size);
    unsigned int _remaining_size_to_write = size;

    if (!(_inode.mode & INODE_MODE_AC_USER_W))
        return -1;
    if (_inode.locked == 1)
        return -2;
    for (int i = 0; _remaining_size_to_write != 0; i++) {
        if (_allocated_blocks[i] == -1) {
            _allocated_blocks[i] = alloc_block(disk);
            if (_allocated_blocks[i] == -1) return -3;
        }
        if (_remaining_size_to_write > disk->super_block->block_size) {
            edit_block(disk, _allocated_blocks[i], data, disk->super_block->block_size);
        } else {
            edit_block(disk, _allocated_blocks[i], data, _remaining_size_to_write);
            break;
        }
        data += disk->super_block->block_size;
        _remaining_size_to_write -= disk->super_block->block_size;
    }
    _free_no_more_used_blocks(disk, _inode, _allocated_blocks, size);
    _inode.size = size;
    for (int i = 0; i < BLOCK_PER_NODE && _allocated_blocks[i] != -1; i++)
        _inode.blocks[i] = _allocated_blocks[i];
    free(_allocated_blocks);
    _inode_save(disk, inode_number, _inode);
    return 0;
}