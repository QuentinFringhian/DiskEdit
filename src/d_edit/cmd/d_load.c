#include <stdio.h>
#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"

inode_t *_get_inode_table(char *d_path, int num_inode, size_t offset)
{
    FILE *_d_img = fopen(d_path, "r");
    inode_t *inode_table = malloc(sizeof(inode_t) * num_inode);

    if (inode_table == NULL) return NULL;
    fseek(_d_img, offset, SEEK_SET);
    for (int i = 0; i < num_inode; i++) {
        fread(&inode_table[i], sizeof(inode_t), 1, _d_img);
    }
    fclose(_d_img);
    return inode_table;
}

super_block_t *_get_super_block(char *d_path)
{
    FILE *_d_img = fopen(d_path, "r");
    super_block_t *super_block = malloc(sizeof(super_block_t));

    if (super_block == NULL) return NULL;
    if (fread(super_block, sizeof(super_block_t), 1, _d_img) != 1)
        return NULL;
    fclose(_d_img);
    return super_block;
}

disk_t *d_load(char *d_path)
{
    disk_t *d = malloc(sizeof(disk_t));

    if (d == NULL) return NULL;
    d->d_path = d_path;
    d->super_block = _get_super_block(d_path);
    if (d->super_block == NULL) return NULL;
    d->blocks_offset = d->super_block->block_size + d->super_block->inode_size * d->super_block->num_inodes;
    d->inode_table = _get_inode_table(d_path, d->super_block->num_inodes, d->super_block->block_size);
    d->cache = NULL;
    d->current_dir = read_dir(d, d->super_block->first_inode);
    d->cache = NULL;
    return d;
}