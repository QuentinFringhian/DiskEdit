#include <stdlib.h>
#include "linked_list.h"

int linked_list_size(linked_list_t *ll_head)
{
    int size = 0;

    for (; ll_head != NULL; ll_head = ll_head->n_node)
        size++;
    return size;
}