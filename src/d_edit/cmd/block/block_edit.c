#include "d_edit/d_edit.h"

void edit_block(disk_t *d, int block_number, unsigned char *data, unsigned int size)
{
    FILE *d_file = fopen(d->d_path, "r+");
    size_t _block_offset = d->blocks_offset + block_number * d->super_block->block_size;

    if (fseek(d_file, _block_offset, SEEK_SET) == -1)
        return;
    if (fwrite(data, size, 1, d_file) != 1)
        return;
    update_block_cache(d, block_number, data);
    fclose(d_file);
}