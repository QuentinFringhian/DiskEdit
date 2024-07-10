#include <ncurses.h>
#include "tui/tui.h"

void file_move_cmd(file_tui_t *file_tui, line_list_t *extracted_file, int input)
{
    switch (input) {
    case KEY_UP:
        if (file_tui->cursor_y == 0) {
            file_tui->cursor_x = 0;
        } else {
            file_tui->cursor_y--;
            if (file_tui->cursor_x > (size_t)linked_list_size(linked_list_get(extracted_file, file_tui->cursor_y)) - 1)
                file_tui->cursor_x = (size_t)linked_list_size(linked_list_get(extracted_file, file_tui->cursor_y)) - 1;
        }
        break;
    case KEY_DOWN:
        if (file_tui->cursor_y == (size_t)linked_list_size(extracted_file) - 1) {
            file_tui->cursor_x = (size_t)linked_list_size(linked_list_get(extracted_file, file_tui->cursor_y)) - 1;
        } else {
            file_tui->cursor_y++;
            if (file_tui->cursor_x > (size_t)linked_list_size(linked_list_get(extracted_file, file_tui->cursor_y)) - 1)
                file_tui->cursor_x = (size_t)linked_list_size(linked_list_get(extracted_file, file_tui->cursor_y)) - 1;
        }
        break;
    case KEY_RIGHT:
        if (file_tui->cursor_x == (size_t)linked_list_size(linked_list_get(extracted_file, file_tui->cursor_y)) - 1) {
            if (file_tui->cursor_y == (size_t)linked_list_size(extracted_file) - 1) {
                file_tui->cursor_x = (size_t)linked_list_size(linked_list_get(extracted_file, file_tui->cursor_y)) - 1;
            } else {
                file_tui->cursor_y++;
                file_tui->cursor_x = 0;
            }
        } else {
            file_tui->cursor_x++;
        }
        break;
    case KEY_LEFT:
        if (file_tui->cursor_x == 0) {
            if (file_tui->cursor_y == 0) {
                file_tui->cursor_x = 0;
            } else {
                file_tui->cursor_y--;
                file_tui->cursor_x = (size_t)linked_list_size(linked_list_get(extracted_file, file_tui->cursor_y)) - 1;
            }
        } else {
            file_tui->cursor_x--;
        }
        break;
    }
    if (file_tui->cursor_x < file_tui->file_offset_x + 1) {
        if (file_tui->cursor_x != 0) file_tui->file_offset_x = file_tui->cursor_x - 1;
        else file_tui->file_offset_x = file_tui->cursor_x;
    }
    if (file_tui->cursor_y < file_tui->file_offset_y)
        file_tui->file_offset_y = file_tui->cursor_y;
    while (file_tui->cursor_x > file_tui->file_offset_x + FILE_WIN_MAX_X - FILE_WIN_START_X - 1)
        file_tui->file_offset_x++;
    while (file_tui->cursor_y > file_tui->file_offset_y + WIN_HEIGHT - 1)
        file_tui->file_offset_y++;
    draw_file(file_tui, extracted_file);
    wrefresh(file_tui->file_win);
}