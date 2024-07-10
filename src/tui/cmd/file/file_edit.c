#include <stdlib.h>
#include "tui/tui_cmd.h"

void file_bs_char(file_tui_t *file_tui, line_list_t **extracted_file)
{
    line_list_t *_line_current = *extracted_file;
    line_list_t *_line_prev = NULL;
    char_list_t *_char_buff = NULL;
    char_list_t *_char_line_prev = NULL;

    for (size_t i = 0; i < file_tui->cursor_y; i++)
        _line_current = _line_current->n_node;
    _char_buff = _line_current->data;
    _line_prev = _line_current->p_node;
    if (_line_prev != NULL) _char_line_prev = _line_prev->data;
    if (file_tui->cursor_x == 0) {
        if (file_tui->cursor_y == 0) return;
        file_tui->cursor_x = linked_list_size(_char_line_prev);
        if (linked_list_size(_char_line_prev) == 1) {
            linked_list_remove(extracted_file, free, file_tui->cursor_y - 1);
        } else {
            linked_list_remove(&_char_line_prev, free, linked_list_size(_char_line_prev) - 1);
            linked_list_concat(&_char_line_prev, _char_buff);
            linked_list_remove(extracted_file, NULL, file_tui->cursor_y);
        }
        file_tui->cursor_y--;
    } else if (file_tui->cursor_x == 1) {
        _line_current->data = _char_buff->n_node;
        if (_char_buff->n_node != NULL)
            _char_buff->n_node->p_node = NULL;
        free(_char_buff);
    } else if (file_tui->cursor_x > 1)
        linked_list_remove(&_char_buff, free, file_tui->cursor_x - 1);
    file_move_cmd(file_tui, *extracted_file, KEY_LEFT);
}

void file_del_char(file_tui_t *file_tui, line_list_t **extracted_file)
{
    line_list_t *_line_current = *extracted_file;
    line_list_t *_line_next = NULL;
    char_list_t *_char_buff = NULL;
    char_list_t *_char_line_next = NULL;

    for (size_t i = 0; i < file_tui->cursor_y; i++)
        _line_current = _line_current->n_node;
    _char_buff = _line_current->data;
    _line_next = _line_current->n_node;
    if (_line_next == NULL && file_tui->cursor_x == (size_t)linked_list_size(_char_buff) - 1) return;
    if (_line_next != NULL) _char_line_next = _line_next->data;
    if (file_tui->cursor_x == 0) {
        if (linked_list_size(_char_buff) == 1) {
            linked_list_remove(extracted_file, free, file_tui->cursor_y);
        } else {
            _line_current->data = _char_buff->n_node;
            if (_char_buff->n_node != NULL)
                _char_buff->n_node->p_node = NULL;
            free(_char_buff);
        }
    } else if (file_tui->cursor_x == (size_t)linked_list_size(_char_buff) - 1) {
        if (file_tui->cursor_y == (size_t)linked_list_size(*extracted_file) - 1) return;
        linked_list_remove(&_char_buff, free, file_tui->cursor_x);
        linked_list_concat(&_char_buff, _char_line_next);
        linked_list_remove(extracted_file, NULL, file_tui->cursor_y + 1);
    } else if (file_tui->cursor_x < (size_t)linked_list_size(_char_buff) - 1)
        linked_list_remove(&_char_buff, free, file_tui->cursor_x);
    file_move_cmd(file_tui, *extracted_file, -1);
}

void file_enter(file_tui_t *file_tui, line_list_t **extracted_file)
{
    line_list_t *line_current = *extracted_file;
    char_list_t *char_buff = NULL;
    char_list_t *new_line = NULL;
    char *new_break = malloc(sizeof(char));

    if (new_break == NULL) return;
    *new_break = '\n';
    for (size_t i = 0; i < file_tui->cursor_y; i++)
        line_current = line_current->n_node;
    char_buff = line_current->data;
    new_line = linked_list_split(&char_buff, file_tui->cursor_x);
    linked_list_append(&char_buff, new_break);
    line_current->data = char_buff;
    linked_list_insert(extracted_file, new_line, file_tui->cursor_y);
    file_tui->cursor_x = 0;
    file_tui->cursor_y++;
    file_move_cmd(file_tui, *extracted_file, -1);
}

void file_add_char(file_tui_t *file_tui, line_list_t **extracted_file, unsigned char c)
{
    line_list_t *line_current = *extracted_file;
    char_list_t *char_buff = NULL;
    char *new_char = malloc(sizeof(char));

    if (new_char == NULL) return;
    *new_char = c;
    for (size_t i = 0; i < file_tui->cursor_y; i++)
        line_current = line_current->n_node;
    char_buff = line_current->data;
    if (file_tui->cursor_x == 0)
        linked_list_push(&char_buff, new_char);
    else
        linked_list_insert(&char_buff, new_char, file_tui->cursor_x - 1);
    line_current->data = char_buff;
    file_move_cmd(file_tui, *extracted_file, KEY_RIGHT);
}