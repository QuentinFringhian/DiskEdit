#include <string.h>
#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"
#include "tui/tui_cmd.h"

bool dir_cli(disk_t *disk, tui_t *tui)
{
    char *_cmd = get_input(tui->dir_tui->dir_win, CMD_PRINT, false);

    if (_cmd == NULL)
        return false;
    if (strcmp(_cmd, CMD_QUIT) == 0 || strcmp(_cmd, CMD_QUIT_SHORT) == 0) {
        free(_cmd);
        return true;
    }
    if (strcmp(_cmd, CMD_TOUCH) == 0) {
        char *file_name = get_input(tui->dir_tui->dir_win, CMD_TOUCH_PRINT, false);
        touch(disk, file_name);
    }
    if (strcmp(_cmd, CMD_MKDIR) == 0) {
        char *dir_name = get_input(tui->dir_tui->dir_win, CMD_MKDIR_PRINT, false);
        mkdir(disk, dir_name);
    }
    if (strcmp(_cmd, CMD_RM) == 0) {
        rm(disk, &disk->current_dir, tui->dir_tui->file_selected->inode_number);
    }
    if (strcmp(_cmd, CMD_RMDIR) == 0) {
        rmdir(disk, &disk->current_dir, tui->dir_tui->file_selected->inode_number);
    }
    free(_cmd);
    return false;
}