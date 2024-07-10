#include <stdlib.h>
#include "linked_list.h"

void linked_list_append(linked_list_t **ll_head, void *new_data)
{
    linked_list_t *_ll = *ll_head;
    linked_list_t *_new_node = linked_list_new(new_data);

    if (_new_node == NULL) return;
    if (*ll_head == NULL) {
        *ll_head = _new_node;
        return;
    }
    for (;_ll->n_node != NULL; _ll = _ll->n_node);
    _ll->n_node = _new_node;
    _new_node->p_node = _ll;
}