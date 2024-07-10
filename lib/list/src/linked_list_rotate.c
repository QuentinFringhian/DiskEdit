#include <unistd.h>
#include "linked_list.h"

void _linked_list_rotate_one(linked_list_t **ll_head)
{
    linked_list_t *_node = *ll_head;
    linked_list_t *_tmp_node = *ll_head;

    if (_node == NULL || _node->n_node == NULL) return;
    *ll_head = (*ll_head)->n_node;
    (*ll_head)->p_node = NULL;
    for (;_node->n_node != NULL; _node = _node->n_node);
    _node->n_node = _tmp_node;
    _tmp_node->p_node = _node;
    _tmp_node->n_node = NULL;
}

void linked_list_rotate(linked_list_t **ll_head, int n)
{
    for (int i = 0; i < n; i++)
        _linked_list_rotate_one(ll_head);
}