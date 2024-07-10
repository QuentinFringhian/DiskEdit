#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"

void rm(disk_t *disk, dir_buff_t *current_dir, int inode_number)
{
    inode_t inode = disk->inode_table[inode_number];
    file_list_t *curr = NULL;
    int index_in_dir = 0;

    if ((inode.mode & INODE_MODE_DIR_FILE) == INODE_MODE_DIR_FILE)
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