#include <string.h>
#include "tui/tui.h"

void _draw_file_char(WINDOW *win, unsigned char c, int y, int x, bool highlight)
{
    if (highlight) wattron(win, A_REVERSE);
    if (highlight) wattron(win, A_BLINK);
    mvwprintw(win, WIN_START_Y + y, FILE_WIN_START_X + x, "%c", c);
    if (highlight) wattroff(win, A_REVERSE);
    if (highlight) wattroff(win, A_BLINK);
}

void draw_file(file_tui_t *file_tui, line_list_t *extracted_file)
{
    size_t _pos_x = 0;
    size_t _pos_y = 0;
    int _size_y = 0;
    int _size_x = 0;
    char_list_t *line_buff = NULL;

    werase(file_tui->file_win);
    box(file_tui->file_win, 0, 0);
    for (size_t i = 0; i < file_tui->file_offset_y && extracted_file != NULL; i++) {
        _pos_y++;
        extracted_file = extracted_file->n_node;
    }
    for (; extracted_file != NULL; extracted_file = extracted_file->n_node) {
        if (_size_y >= WIN_HEIGHT) break;
        line_buff = extracted_file->data;
        for (size_t i = 0; i < file_tui->file_offset_x && line_buff != NULL; i++) {
            _pos_x++;
            line_buff = line_buff->n_node;
        }
        for (; line_buff != NULL; line_buff = line_buff->n_node) {
            if (_size_x >= FILE_WIN_MAX_X - FILE_WIN_START_X) break;
            if (*(char *)line_buff->data == '\n' || *(char *)line_buff->data == '\0')
                _draw_file_char(file_tui->file_win, ' ', _size_y, _size_x, _pos_x == file_tui->cursor_x && _pos_y == file_tui->cursor_y);
            else
                _draw_file_char(file_tui->file_win, *(char *)line_buff->data, _size_y, _size_x, _pos_x == file_tui->cursor_x && _pos_y == file_tui->cursor_y);
            _size_x++;
            _pos_x++;
        }
        _pos_x = 0;
        _size_x = 0;
        _pos_y++;
        _size_y++;
    }
}