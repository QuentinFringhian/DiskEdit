#include <stdio.h>
#include <stdlib.h>
#include "d_edit/d_edit_cmd.h"
#include "tui/tui.h"

void _destroy_disk(disk_t *d)
{
    linked_list_clear(&d->current_dir.file_list, free);
    free(d->inode_table);
    free(d->super_block);
    free(d);
}

void d_edit(char *d_path)
{
    disk_t *d = d_load(d_path);

    if (d == NULL) return;
    d_edit_display(d);
    _destroy_disk(d);
}