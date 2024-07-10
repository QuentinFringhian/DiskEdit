#include <ncurses.h>
#include "tui/tui.h"

void dir_move_cmd(disk_t *disk, tui_t *tui, int input)
{
    int new_pos = tui->dir_tui->dir_cursor + (input == KEY_UP ? -1 : 1);

    if (new_pos < 0 || new_pos >= linked_list_size(disk->current_dir.file_list))
        return;
    if (new_pos < tui->dir_tui->dir_offset)
        tui->dir_tui->dir_offset = new_pos;
    if (new_pos >= tui->dir_tui->dir_offset + WIN_HEIGHT - SCROLL_MARGIN)
        tui->dir_tui->dir_offset++;
    draw_dir(disk, tui->dir_tui->dir_win, tui->dir_tui->dir_offset, new_pos);
    tui->dir_tui->dir_cursor = new_pos;
    tui->dir_tui->file_selected = linked_list_get(disk->current_dir.file_list, new_pos);
    wrefresh(tui->dir_tui->dir_win);
}