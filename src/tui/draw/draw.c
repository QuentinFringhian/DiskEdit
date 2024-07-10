#include "tui/tui.h"

void draw_input(WINDOW *win, char *prefix, int size)
{
    for (int i = WIN_START_X; i < size; i++)
        mvwprintw(win, CMD_Y_POS, i, BLANK);
    mvwprintw(win, CMD_Y_POS, WIN_START_X, "%s", prefix);
}

void draw_message(WINDOW *win, char *message, int size)
{
    for (int i = WIN_START_X; i < size; i++)
        mvwprintw(win, CMD_Y_POS, i, BLANK);
    mvwprintw(win, CMD_Y_POS, WIN_START_X, "%s", message);
}

void draw_areas(tui_t *tui)
{
    wclear(tui->dir_tui->dir_win);
    wclear(tui->file_tui->file_win);
    box(tui->dir_tui->dir_win, 0, 0);
    box(tui->file_tui->file_win, 0, 0);
    wrefresh(tui->dir_tui->dir_win);
    wrefresh(tui->file_tui->file_win);
}