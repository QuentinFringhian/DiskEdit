#include <stdlib.h>
#include "tui/tui.h"

#include <string.h>

line_list_t *extract_lines(unsigned char *data, unsigned int size)
{
    line_list_t *lines = NULL;
    char_list_t *line = NULL;
    char *char_buff = NULL;

    for (unsigned int i = 0; i < size; i++) {
        line = NULL;
        for (; i < size; i++) {
            char_buff = malloc(sizeof(char));
            if (char_buff == NULL) return NULL;
            *char_buff = data[i];
            linked_list_append(&line, char_buff);
            char_buff = NULL;
            if (data[i] == '\n') break;
        }
        linked_list_append(&lines, line);
    }
    char_buff = malloc(sizeof(char));
    if (char_buff == NULL) return NULL;
    *char_buff = '\0';
    linked_list_append(&line, char_buff);
    if (lines == NULL) linked_list_append(&lines, line);
    return lines;
}

unsigned char *concat_file(line_list_t *extracted_file)
{
    unsigned char *file = NULL;
    size_t size = 0;
    size_t i = 0;

    for (line_list_t *line = extracted_file; line != NULL; line = line->n_node)
        size += linked_list_size(line->data);
    size--;
    file = malloc(sizeof(char) * size);
    if (file == NULL) return NULL;
    for (line_list_t *line = extracted_file; line != NULL; line = line->n_node) {
        for (char_list_t *c = line->data; c != NULL; c = c->n_node) {
            if (line->n_node == NULL && c->n_node == NULL) break;
            file[i] = *(char *)c->data;
            i++;
        }
    }
    return file;
}