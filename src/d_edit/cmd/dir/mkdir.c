#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"

int mkdir(disk_t *disk, char *dir_name)
{
    int new_inode = alloc_inode(disk, INODE_MODE_DIR_FILE | INODE_MODE_AC_ALL);
    file_list_t *new_file_list = NULL;
    file_t *parent = malloc(sizeof(file_t));
    file_t *dir_file = malloc(sizeof(file_t));
    file_t *child = malloc(sizeof(file_t));

    if (parent == NULL || dir_file == NULL || child == NULL || new_inode == -1) return -1;
    dir_file->inode_number = new_inode;
    dir_file->name = (unsigned char *)dir_name;
    parent->inode_number = disk->current_dir.dir_inode_number;
    parent->name = (unsigned char *)"..";
    child->inode_number = new_inode;
    child->name = (unsigned char *)".";
    linked_list_append(&disk->current_dir.file_list, dir_file);
    linked_list_append(&new_file_list, parent);
    linked_list_append(&new_file_list, child);
    dir_save(disk, disk->current_dir.file_list, disk->current_dir.dir_inode_number);
    dir_save(disk, new_file_list, new_inode);
    return new_inode;
}