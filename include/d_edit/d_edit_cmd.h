#ifndef _D_EDIT_CMD_H
#define _D_EDIT_CMD_H

#include "d_edit.h"

disk_t *d_load(char *d_path);

inode_buff_t *read_inode(disk_t *d, int inode_number);
void free_inode(disk_t *disk, int inode_number);
int alloc_inode(disk_t *disk, unsigned int mode);
int inode_edit(disk_t *disk, int inode_number, unsigned char *data, unsigned int size);

block_buff_t *read_block(disk_t *d, int block_number, unsigned int size);
void free_block(disk_t *d, int block_number);
int alloc_block(disk_t *d);
void edit_block(disk_t *d, int block_number, unsigned char *data, unsigned int size);

dir_buff_t read_dir(disk_t *d, int inode_number);
void dir_change(disk_t *disk, int dir_inode_number);
void dir_save(disk_t *d, file_list_t *file_list, int inode_number);
int touch(disk_t *disk, char *file_name);
int mkdir(disk_t *disk, char *dir_name);
void rm(disk_t *disk, dir_buff_t *current_dir, int inode_number);
void rmdir(disk_t *disk, dir_buff_t *current_dir, int inode_number);

#endif /* _D_EDIT_CMD_H */