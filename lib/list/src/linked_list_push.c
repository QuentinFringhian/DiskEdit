#include <stdlib.h>
#include "linked_list.h"

void linked_list_push(linked_list_t **ll_head, void *new_data)
{
    linked_list_t *_new_node = linked_list_new(new_data);

    if (_new_node == NULL) return;
    _new_node->n_node = *ll_head;
    if (*ll_head != NULL)
        (*ll_head)->p_node = _new_node;
    *ll_head = _new_node;
}