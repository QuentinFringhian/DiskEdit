#include <stdlib.h>
#include <string.h>
#include "d_edit/d_edit_cmd.h"

void _rm_empty_dir(disk_t *disk, dir_buff_t *current_dir, int inode_number)
{
    inode_t inode = disk->inode_table[inode_number];
    file_list_t *curr = NULL;
    int index_in_dir = 0;

    if ((inode.mode & INODE_MODE_DIR_FILE) == 0)
        return;
    for (curr = current_dir->file_list; curr != NULL; curr = curr->n_node) {
        if (((file_t *)curr->data)->inode_number == inode_number)
            break;
        index_in_dir++;
    }
    if (curr == NULL) return;
    linked_list_remove(&current_dir->file_list, free, index_in_dir);
    free_inode(disk, inode_number);
    dir_save(disk, current_dir->file_list, current_dir->dir_inode_number);
}

void rmdir(disk_t *disk, dir_buff_t *current_dir, int inode_number)
{
    inode_t inode = disk->inode_table[inode_number];
    dir_buff_t dir_buff;

    if ((inode.mode & INODE_MODE_REG_FILE) == INODE_MODE_REG_FILE)
        return;
    if (inode_number == current_dir->dir_inode_number)
        return;
    dir_buff = read_dir(disk, inode_number);
    for (file_list_t *curr = current_dir->file_list; curr != NULL; curr = curr->n_node) {
        if (strcmp((char *)((file_t *)curr->data)->name, "..") == 0 || strcmp((char *)((file_t *)curr->data)->name, ".") == 0)
            continue;
        if ((disk->inode_table[((file_t *)curr->data)->inode_number].mode & INODE_MODE_REG_FILE) == INODE_MODE_REG_FILE)
            rm(disk, &dir_buff, ((file_t *)curr->data)->inode_number);
        else
            rmdir(disk, &dir_buff, ((file_t *)curr->data)->inode_number);
    }
    _rm_empty_dir(disk, current_dir, inode_number);
}