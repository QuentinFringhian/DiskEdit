#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"

file_list_t *_dir_convert(disk_t *d, inode_buff_t *inode_buff)
{
    inode_t inode = d->inode_table[inode_buff->inode_number];
    file_list_t *dir = NULL;
    dentry_t *_buff = NULL;
    file_t *file = NULL;

    for (size_t i = 0; i < inode.size; i += d->super_block->inode_size) {
        _buff = (dentry_t *)(inode_buff->data + i);
        file = malloc(sizeof(file_t));
        if (file == NULL) return NULL;
        file->name = _buff->name;
        file->inode_number = _buff->inode;
        linked_list_append(&dir, file);
    }
    return dir;
}

dir_buff_t read_dir(disk_t *d, int inode_number)
{
    dir_buff_t dir_buff = { inode_number, NULL };
    file_list_t *file_list = NULL;
    inode_t inode = d->inode_table[inode_number];
    inode_buff_t *data = NULL;

    if ((inode.mode & INODE_MODE_DIR_FILE) == 0)
        return dir_buff;
    data = read_inode(d, inode_number);
    if (data == NULL) return dir_buff;
    file_list = _dir_convert(d, data);
    dir_buff.file_list = file_list;
    free(data);
    return dir_buff;
}