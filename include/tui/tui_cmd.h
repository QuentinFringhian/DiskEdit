#ifndef _TUI_CMD_H
#define _TUI_CMD_H

#include <stdbool.h>

#include "tui.h"

#define CMD_QUIT "quit"
#define CMD_QUIT_SHORT "q"

#define CMD_TOUCH "touch"
#define CMD_MKDIR "mkdir"
#define CMD_RM "rm"
#define CMD_RMDIR "rmdir"

#define CMD_EDIT "edit"
#define CMD_EDIT_SHORT "e"

#define CMD_SAVE "save"
#define CMD_SAVE_SHORT "s"

void show_message(WINDOW *win, char *message);
char *get_input(WINDOW *win, char *prefix, bool is_file_window);

void fopen_cmd(disk_t *disk, file_t *file, tui_t *tui);
void dir_move_cmd(disk_t *disk, tui_t *tui, int input);

line_list_t *extract_lines(unsigned char *data, unsigned int size);
unsigned char *concat_file(line_list_t *extracted_file);
void file_move_cmd(file_tui_t *file_tui, line_list_t *extracted_file, int input);
void file_del_char(file_tui_t *file_tui, line_list_t **extracted_file);
void file_bs_char(file_tui_t *file_tui, line_list_t **extracted_file);
void file_enter(file_tui_t *file_tui, line_list_t **extracted_file);
void file_add_char(file_tui_t *file_tui, line_list_t **extracted_file, unsigned char c);

#endif /* _TUI_CMD_H */