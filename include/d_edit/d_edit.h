#ifndef _D_EDIT_H_
#define _D_EDIT_H_

#include <stdio.h>
#include "fs.h"
#include "linked_list.h"

#define BLOCK_PER_NODE 6
#define MAX_BLOCK_IN_CACHE 6

typedef struct super_block super_block_t;
typedef struct inode inode_t;
typedef struct dentry dentry_t;

typedef linked_list_t file_list_t;
typedef linked_list_t cache_list_t;

typedef struct block_buff_s {
    int block_number;
    unsigned char *data;
} block_buff_t;

typedef struct inode_buff_s {
    int inode_number;
    unsigned short *blocks;
    unsigned char *data;
} inode_buff_t;

typedef struct dir_buff_s {
    int dir_inode_number;
    file_list_t *file_list;
} dir_buff_t;

typedef struct file_s {
    unsigned char *name;
    int inode_number;
} file_t;

typedef struct disk_s {
    super_block_t *super_block;
    inode_t *inode_table;
    dir_buff_t current_dir;
    cache_list_t *cache;
    unsigned int blocks_offset;
    char *d_path;
} disk_t;

void d_edit(char *d_path);

block_buff_t *get_block_cache(disk_t *d, int block_number);
void add_block_cache(disk_t *d, block_buff_t *block);
void update_block_cache(disk_t *d, int block_number, unsigned char *data);

#endif /* _D_EDIT_H_ */