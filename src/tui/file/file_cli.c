#include <string.h>
#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"
#include "tui/tui_cmd.h"

size_t _get_file_size(line_list_t *extracted_file)
{
    size_t size = 0;
    for (line_list_t *line = extracted_file; line != NULL; line = line->n_node)
        size += linked_list_size(line->data);
    size--;
    return size;
}

void _save_file(disk_t *disk, file_tui_t *file_tui, line_list_t *extracted_file)
{
    size_t _file_size = _get_file_size(extracted_file);
    unsigned char *_file = concat_file(extracted_file);

    switch (inode_edit(disk, file_tui->inode_number, _file, _file_size)) {
    case -1:
        show_message(file_tui->file_win, "Permission denied");
        break;
    case -2:
        show_message(file_tui->file_win, "File locked");
        break;
    case -3:
        show_message(file_tui->file_win, "Could not allocate block");
        break;
    default:
        show_message(file_tui->file_win, "File saved");
        break;
    }

}

bool file_cli(disk_t *disk, file_tui_t *file_tui, line_list_t *extracted_file, bool *edit_mode)
{
    char *_cmd = get_input(file_tui->file_win, CMD_PRINT, true);

    if (_cmd == NULL)
        return false;
    if (strcmp(_cmd, CMD_QUIT) == 0 || strcmp(_cmd, CMD_QUIT_SHORT) == 0) {
        free(_cmd);
        return true;
    } else if (strcmp(_cmd, CMD_EDIT) == 0 || strcmp(_cmd, CMD_EDIT_SHORT) == 0) {
        *edit_mode = true;
    } else if (strcmp(_cmd, CMD_SAVE) == 0 || strcmp(_cmd, CMD_SAVE_SHORT) == 0) {
        _save_file(disk, file_tui, extracted_file);
    }
    free(_cmd);
    return false;
}