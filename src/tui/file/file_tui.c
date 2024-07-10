#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"
#include "tui/tui.h"
#include "tui/tui_cmd.h"

void _print_infos(file_tui_t *file_tui, bool edit_mode, unsigned char *file_name)
{
    int _margin = 16;
    size_t _x = file_tui->cursor_x;
    size_t _y = file_tui->cursor_y;

    if (_x > 9) _margin++;
    if (_x > 99) _margin++;
    if (_x > 999) _margin++;
    if (_y > 9) _margin++;
    if (_y > 99) _margin++;
    if (_y > 999) _margin++;
    if (edit_mode) _margin += 10;
    mvwprintw(file_tui->file_win, CMD_Y_POS, FILE_WIN_MAX_X - _margin, "%sLn: %ld, Col %ld", edit_mode ? "EDIT MODE " : "", _y, _x);
    mvwprintw(file_tui->file_win, 0, 1, "%s", file_name);
}

void _file_edit_input(file_tui_t *file_tui, line_list_t **extracted_file, int input)
{
    if (input == KEY_BACKSPACE)
        file_bs_char(file_tui, extracted_file);
    else if (input == KEY_DC)
        file_del_char(file_tui, extracted_file);
    else if (input == KEY_ENTER || input == 10)
        file_enter(file_tui, extracted_file);
    else if (input == '\t') {
        for (size_t i = 0; i < 4; i++)
            file_add_char(file_tui, extracted_file, ' ');
    } else if (input >= ' ' && input <= '~')
        file_add_char(file_tui, extracted_file, input);
}

void _file_input(disk_t *disk, file_tui_t *file_tui, unsigned char *file_name, line_list_t **extracted_file)
{
    int input = 0;
    bool edit_mode = false;

    do {
        _print_infos(file_tui, edit_mode, file_name);
        input = wgetch(file_tui->file_win);
        if (edit_mode) {
            if (input == 27) {
                edit_mode = false;
            } else _file_edit_input(file_tui, extracted_file, input);
        }
        if (!edit_mode && input == CMD_CHAR && file_cli(disk, file_tui, *extracted_file, &edit_mode))
            break;
        if (input == KEY_UP || input == KEY_DOWN || input == KEY_RIGHT || input == KEY_LEFT)
            file_move_cmd(file_tui, *extracted_file, input);
    } while (true);
}

void _file_tui_reset(file_tui_t *file_tui)
{
    file_tui->cursor_x = 0;
    file_tui->cursor_y = 0;
    file_tui->file_offset_x = 0;
    file_tui->file_offset_y = 0;
    werase(file_tui->file_win);
    box(file_tui->file_win, 0, 0);
    wrefresh(file_tui->file_win);
}

void file_tui(disk_t *disk, file_t *file, file_tui_t *file_tui)
{
    inode_buff_t *_inode_buff = read_inode(disk, file->inode_number);
    inode_t _inode = disk->inode_table[file->inode_number];
    line_list_t *extracted_file = extract_lines(_inode_buff->data, _inode.size);
    char_list_t *line_buff = NULL;

    draw_file(file_tui, extracted_file);
    _file_input(disk, file_tui, file->name, &extracted_file);
    _file_tui_reset(file_tui);
    for (line_list_t *tmp = extracted_file; tmp != NULL; tmp = tmp->n_node) {
        line_buff = tmp->data;
        linked_list_clear(&line_buff, free);
    }
    linked_list_clear(&extracted_file, NULL);
}