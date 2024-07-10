#include <stdlib.h>
#include "linked_list.h"

linked_list_t *linked_list_new(void *new_data)
{
    linked_list_t *new_node = malloc(sizeof(linked_list_t));

    if (new_node == NULL) return NULL;
    new_node->data = new_data;
    new_node->n_node = NULL;
    new_node->p_node = NULL;
    return new_node;
}