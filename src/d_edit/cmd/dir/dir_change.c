#include "d_edit/d_edit_cmd.h"

void dir_change(disk_t *disk, int dir_inode_number)
{
    inode_t _inode = disk->inode_table[dir_inode_number];

    if ((_inode.mode & INODE_MODE_DIR_FILE) == 0)
        return;
    disk->current_dir = read_dir(disk, dir_inode_number);
}