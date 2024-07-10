#include <stdlib.h>
#include "linked_list.h"

void linked_list_insert(linked_list_t **ll_head, void *new_data, int index)
{
    linked_list_t *_ll = *ll_head;
    linked_list_t *_new_node = linked_list_new(new_data);

    if (index < 0 || index >= linked_list_size(*ll_head)) return;
    if (_new_node == NULL) return;
    if (*ll_head == NULL) {
        *ll_head = _new_node;
        return;
    }
    for (int i = 0; i != index; i++)
        _ll = _ll->n_node;
    _new_node->n_node = _ll->n_node;
    if (_ll->n_node != NULL)
        _ll->n_node->p_node = _new_node;
    _new_node->p_node = _ll;
    _ll->n_node = _new_node;
}