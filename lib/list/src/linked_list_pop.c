#include <stdlib.h>
#include "linked_list.h"

void *linked_list_pop(linked_list_t **ll_head, int index)
{
    linked_list_t *_ll = *ll_head;
    linked_list_t *_tmp = NULL;
    void *removed_data = NULL;

    if (*ll_head == NULL) return NULL;
    if (index < 0 || index >= linked_list_size(*ll_head)) return NULL;
    if (index == 0) {
        *ll_head = _ll->n_node;
        if (*ll_head != NULL) (*ll_head)->p_node = NULL;
        removed_data = _ll->data;
        free(_ll);
        return removed_data;
    }
    for (int i = 0; i != index; i++)
        _ll = _ll->n_node;
    _tmp = _ll->p_node;
    _tmp->n_node = _ll->n_node;
    if (_ll->n_node != NULL) _ll->n_node->p_node = _tmp;
    removed_data = _ll->data;
    free(_ll);
    return removed_data;
}