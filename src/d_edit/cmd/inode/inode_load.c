#include <string.h>
#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"

void _inode_buff_fill(disk_t *d, inode_buff_t *inode_buff)
{
    size_t _remaining_read = d->inode_table[inode_buff->inode_number].size;
    block_buff_t *_buff = NULL;
    unsigned int read_buff_size = 0;

    for (int i = 0; i < BLOCK_PER_NODE && _remaining_read != 0; i++) {
        if (_remaining_read > d->super_block->block_size) {
            read_buff_size = d->super_block->block_size;
        } else {
            read_buff_size = _remaining_read;
        }
        _buff = read_block(d, inode_buff->blocks[i], read_buff_size);
        if (_buff == NULL)
            return;
        memcpy(inode_buff->data + i * d->super_block->block_size, _buff->data, read_buff_size);
        if (_remaining_read > d->super_block->block_size)
            _remaining_read -= d->super_block->block_size;
        else
            _remaining_read = 0;
        free(_buff);
    }
}

inode_buff_t *read_inode(disk_t *d, int inode_number)
{
    inode_t inode = d->inode_table[inode_number];
    inode_buff_t *inode_buff = malloc(sizeof(inode_buff_t));

    if (inode_buff == NULL)
        return NULL;
    inode_buff->inode_number = inode_number;
    inode_buff->blocks = malloc(sizeof(short) * BLOCK_PER_NODE);
    for (int i = 0; i < BLOCK_PER_NODE; i++)
        inode_buff->blocks[i] = inode.blocks[i];
    if (inode.size == 0)
        return inode_buff;
    inode_buff->data = malloc(inode.size);
    if (inode_buff == NULL) return NULL;
    _inode_buff_fill(d, inode_buff);
    return inode_buff;
}