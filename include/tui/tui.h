#ifndef _TUI_H
#define _TUI_H

#include <ncurses.h>
#include "d_edit/d_edit.h"
#include "linked_list.h"

#define DIR_WIN_WIDTH_RATIO 20
#define FILE_WIN_WIDTH_RATIO 80

#define DIR_WIN_WIDTH (COLS * DIR_WIN_WIDTH_RATIO / 100)
#define FILE_WIN_WIDTH (COLS * FILE_WIN_WIDTH_RATIO / 100)

#define WIN_HEIGHT LINES - 3

#define DIR_WIN_MAX_X DIR_WIN_WIDTH - 1
#define FILE_WIN_MAX_X FILE_WIN_WIDTH - 1

#define WIN_START_Y 1
#define WIN_START_X 1

#define FILE_WIN_START_X WIN_START_X

#define SCROLL_MARGIN 0

#define CMD_CHAR ':'
#define CMD_PRINT "Input: "

#define CMD_TOUCH_PRINT "File name: "
#define CMD_MKDIR_PRINT "Directory name: "

#define CMD_Y_POS LINES - 2

#define BLANK " "

#define ENTER_PRESSED 10

typedef linked_list_t char_list_t;
typedef linked_list_t line_list_t;

typedef struct dir_tui_s {
    WINDOW *dir_win;
    file_t *file_selected;
    int dir_cursor;
    int dir_offset;
} dir_tui_t;

typedef struct file_tui_s {
    WINDOW *file_win;
    int inode_number;
    size_t file_offset_x;
    size_t file_offset_y;
    size_t cursor_x;
    size_t cursor_y;
} file_tui_t;

typedef struct tui_s {
    dir_tui_t *dir_tui;
    file_tui_t *file_tui;
} tui_t;

void d_edit_display(disk_t *disk);

void draw_areas(tui_t *tui);
void draw_message(WINDOW *win, char *message, int size);
void draw_input(WINDOW *win, char *prefix, int size);

void draw_dir(disk_t *disk, WINDOW *dir_win, int offset, int cursor);
void draw_file(file_tui_t *file_tui, line_list_t *extracted_file);

void dir_tui(disk_t *disk, tui_t *tui);
void dir_tui_reset(disk_t *disk, tui_t *tui);
bool dir_cli(disk_t *disk, tui_t *tui);

void file_tui(disk_t *disk, file_t *file, file_tui_t *file_tui);
bool file_cli(disk_t *disk, file_tui_t *file_tui, line_list_t *extracted_file, bool *edit_mode);

#endif /* _TUI_H */