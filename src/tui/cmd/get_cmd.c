#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "tui/tui.h"

void show_message(WINDOW *win, char *message)
{
    wattron(win, A_REVERSE);
    mvwprintw(win, CMD_Y_POS, 1, "%s", message);
    wrefresh(win);
    wattroff(win, A_REVERSE);
    wrefresh(win);
}

char *get_input(WINDOW *win, char *prefix, bool is_file_window)
{
    int _max_x = is_file_window ? FILE_WIN_MAX_X : DIR_WIN_MAX_X;
    char *cmd = malloc(sizeof(char) * _max_x);

    if (cmd == NULL)
        return NULL;
    wattron(win, A_REVERSE);
    draw_input(win, prefix, _max_x);
    echo();
    keypad(win, false);
    mvwgetnstr(win, CMD_Y_POS, strlen(prefix) + 1, cmd, _max_x);
    keypad(win, true);
    noecho();
    wattroff(win, A_REVERSE);
    box(win, 0, 0);
    return cmd;
}