#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"

int touch(disk_t *disk, char *file_name)
{
    file_t *file = malloc(sizeof(file_t));
    int new_inode = alloc_inode(disk, INODE_MODE_REG_FILE | INODE_MODE_AC_ALL);

    if (file == NULL || new_inode == -1) return -1;
    file->name = (unsigned char *)file_name;
    file->inode_number = new_inode;
    linked_list_append(&disk->current_dir.file_list, file);
    dir_save(disk, disk->current_dir.file_list, disk->current_dir.dir_inode_number);
    return new_inode;
}