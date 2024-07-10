#include <stdlib.h>
#include "linked_list.h"

void linked_list_clear(linked_list_t **ll_head, void (*free_data)(void *))
{
    linked_list_t *_ll = *ll_head;
    linked_list_t *_next_node = NULL;

    if (_ll == NULL) return;
    for (; _ll != NULL; _ll = _next_node) {
        _next_node = _ll->n_node;
        if (free_data != NULL)
            free_data(_ll->data);
        free(_ll);
    }
    *ll_head = NULL;
}