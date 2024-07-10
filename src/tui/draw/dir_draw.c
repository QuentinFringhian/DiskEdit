#include <stdlib.h>
#include <ncurses.h>
#include "tui/tui.h"

void _print_reverse(WINDOW *dir_win, int y, file_t *file)
{
    wattron(dir_win, A_REVERSE);
    for (int i = WIN_START_X; i < DIR_WIN_MAX_X; i++)
        mvwprintw(dir_win, y, i, BLANK);
    mvwprintw(dir_win, y, WIN_START_X, "%s", file->name);
    wattroff(dir_win, A_REVERSE);
}

void draw_dir(disk_t *disk, WINDOW *dir_win, int offset, int cursor)
{
    file_list_t *_file_list = disk->current_dir.file_list;
    file_t *file = NULL;
    int _pos = 0;

    werase(dir_win);
    box(dir_win, 0, 0);
    for (int i = 0; i < offset; i++) _file_list = _file_list->n_node;
    for (int i = WIN_START_Y; i <= WIN_HEIGHT; i++) {
        if (_file_list == NULL) break;
        file = _file_list->data;
        if (_pos + offset == cursor)
            _print_reverse(dir_win, i, file);
        else
            mvwprintw(dir_win, i, WIN_START_X, "%s", file->name);
        _file_list = _file_list->n_node;
        _pos++;
    }
    wrefresh(dir_win);
}