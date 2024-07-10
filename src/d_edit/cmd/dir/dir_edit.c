#include <stdlib.h>
#include <string.h>
#include "d_edit/d_edit_cmd.h"

void dir_save(disk_t *d, file_list_t *file_list, int inode_number)
{
    unsigned long dir_size = sizeof(dentry_t) * linked_list_size(file_list);
    unsigned char *dir_buff = malloc(dir_size);
    file_t *file_buff = NULL;
    dentry_t dentry_buff;
    int offset = 0;

    if (dir_buff == NULL) return;
    for (file_list_t *current = file_list; current != NULL; current = current->n_node) {
        file_buff = (file_t *)current->data;
        dentry_buff.inode = file_buff->inode_number;
        dentry_buff.dir_length = 32;
        dentry_buff.file_type = d->inode_table[file_buff->inode_number].mode;
        dentry_buff.name_len = strlen((char *)file_buff->name);
        strcpy((char *)dentry_buff.name, (char *)file_buff->name);
        memcpy(dir_buff + offset, &dentry_buff, 32);
        offset += 32;
    }
    inode_edit(d, inode_number, dir_buff, offset);
    free(dir_buff);
}