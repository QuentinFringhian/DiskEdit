#include <string.h>
#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"

block_buff_t *_read_block_from_disk(disk_t *d, int block_number, unsigned int size)
{
    FILE *_d_img = fopen(d->d_path, "r");
    block_buff_t *block = malloc(sizeof(block_buff_t));
    unsigned int _block_offset = d->blocks_offset + block_number * d->super_block->block_size;

    if (block == NULL) return NULL;
    block->block_number = block_number;
    block->data = malloc(size);
    if (block->data == NULL) return NULL;
    if (fseek(_d_img, _block_offset, SEEK_SET) == -1)
        return NULL;
    if (fread(block->data, size, 1, _d_img) != 1)
        return NULL;
    fclose(_d_img);
    add_block_cache(d, block);
    return block;
}

block_buff_t *read_block(disk_t *d, int block_number, unsigned int size)
{
    block_buff_t *block = get_block_cache(d, block_number);

    if (block != NULL) return block;
    return _read_block_from_disk(d, block_number, size);
}