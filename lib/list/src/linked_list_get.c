#include <stdlib.h>
#include "linked_list.h"

void *linked_list_get(linked_list_t *ll_head, int index)
{
    for (int i = 0; i < index; i++) {
        if (ll_head->n_node == NULL) return NULL;
        ll_head = ll_head->n_node;
    }
    return ll_head->data;
}