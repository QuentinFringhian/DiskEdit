#include <ncurses.h>
#include <stdbool.h>
#include "tui/tui_cmd.h"

void _dir_input(disk_t *disk, tui_t *tui)
{
    int input = 0;

    do {
        input = wgetch(tui->dir_tui->dir_win);
        if (input == CMD_CHAR && dir_cli(disk, tui))
            break;
        if (input == KEY_UP || input == KEY_DOWN)
            dir_move_cmd(disk, tui, input);
        if (input == ENTER_PRESSED)
            fopen_cmd(disk, tui->dir_tui->file_selected, tui);
    } while (true);
}

void dir_tui_reset(disk_t *disk, tui_t *tui)
{
    tui->dir_tui->file_selected = disk->current_dir.file_list->data;
    tui->dir_tui->dir_cursor = 0;
    tui->dir_tui->dir_offset = 0;
    draw_dir(disk, tui->dir_tui->dir_win, 0, 0);
}

void dir_tui(disk_t *disk, tui_t *tui)
{
    tui->dir_tui->file_selected = disk->current_dir.file_list->data;
    draw_dir(disk, tui->dir_tui->dir_win, 0, 0);
    _dir_input(disk, tui);
}