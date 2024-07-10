#include <stdlib.h>
#include "tui/tui.h"

void _tui_destroy(tui_t *tui)
{
    delwin(tui->dir_tui->dir_win);
    delwin(tui->file_tui->file_win);
    free(tui);
    endwin();
}

dir_tui_t *_dir_tui_init(void)
{
    dir_tui_t *new_dir_tui = malloc(sizeof(dir_tui_t));

    if (new_dir_tui == NULL)
        return NULL;
    new_dir_tui->file_selected = NULL;
    new_dir_tui->dir_win = subwin(stdscr, LINES - 1, DIR_WIN_WIDTH, 1, 1);
    keypad(new_dir_tui->dir_win, true);
    new_dir_tui->dir_cursor = 0;
    new_dir_tui->dir_offset = 0;
    return new_dir_tui;
}

file_tui_t *_file_tui_init(void)
{
    file_tui_t *new_file_tui = malloc(sizeof(file_tui_t));

    if (new_file_tui == NULL)
        return NULL;
    new_file_tui->file_win = subwin(stdscr, LINES - 1, FILE_WIN_WIDTH, 1, DIR_WIN_WIDTH + 1);
    keypad(new_file_tui->file_win, TRUE);
    new_file_tui->inode_number = -1;
    new_file_tui->file_offset_x = 0;
    new_file_tui->file_offset_y = 0;
    new_file_tui->cursor_x = 0;
    new_file_tui->cursor_y = 0;
    return new_file_tui;
}

tui_t *_tui_init(void)
{
    tui_t *new_tui = malloc(sizeof(tui_t));

    if (new_tui == NULL) return NULL;
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    new_tui->dir_tui = _dir_tui_init();
    new_tui->file_tui = _file_tui_init();
    if (new_tui->dir_tui == NULL || new_tui->file_tui == NULL) {
        _tui_destroy(new_tui);
        return NULL;
    }
    return new_tui;
}

void d_edit_display(disk_t *disk)
{
    tui_t *tui = _tui_init();

    if (tui == NULL)
        return;
    draw_areas(tui);
    dir_tui(disk, tui);
    _tui_destroy(tui);
}