#include <stdio.h>
#include "d_edit/d_edit.h"

int main(int arg_c, char *arg_v[])
{
    FILE *d_img = NULL;

    if (arg_c != 2) {
        printf("Usage: ./dedit [file]\n");
        return 1;
    }
    d_img = fopen(arg_v[1], "r+");
    if (d_img == NULL) {
        printf("Error: Could not open file %s\n", arg_v[1]);
        return 1;
    }
    fclose(d_img);
    d_edit(arg_v[1]);
    return 0;
}