#include <string.h>
#include "d_edit/d_edit_cmd.h"
#include "tui/tui.h"

void fopen_cmd(disk_t *disk, file_t *file, tui_t *tui)
{
    inode_t inode = disk->inode_table[file->inode_number];

    if ((inode.mode & INODE_MODE_DIR_FILE) == INODE_MODE_DIR_FILE || strcmp((char *)file->name, ".") == 0) {
        dir_change(disk, file->inode_number);
        dir_tui_reset(disk, tui);
        return;
    }
    if ((inode.mode & INODE_MODE_REG_FILE) == INODE_MODE_REG_FILE) {
        tui->file_tui->inode_number = file->inode_number;
        file_tui(disk, file, tui->file_tui);
        return;
    }
}