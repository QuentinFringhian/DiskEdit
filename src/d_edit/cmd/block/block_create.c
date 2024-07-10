#include "d_edit/d_edit.h"

int alloc_block(disk_t *d)
{
    FILE *d_file = fopen(d->d_path, "r+");
    int _block_number = -1;

    for (int i = 0; _block_number == -1 && i < 511; i++) {
        for (int j = 0; j < 8; j++) {
            if (!(d->super_block->block_bitmap[i] & (1 << j))) {
                _block_number = i * 8 + j;
                d->super_block->block_bitmap[i] |= (1 << j);
                break;
            }
        }
    }
    if (_block_number != -1) {
        fseek(d_file, 64, SEEK_SET);
        fwrite(d->super_block->block_bitmap, 1, 511, d_file);
    }
    fclose(d_file);
    return _block_number;
}

void free_block(disk_t *d, int block_number)
{
    FILE *d_file = fopen(d->d_path, "r+");

    d->super_block->block_bitmap[block_number / 8] &= ~(1 << (block_number % 8));
    fseek(d_file, 64, SEEK_SET);
    fwrite(d->super_block->block_bitmap, 1, 511, d_file);
    fclose(d_file);
}