#include <stdlib.h>
#include "linked_list.h"

linked_list_t *linked_list_split(linked_list_t **list, int index)
{
    linked_list_t *tmp = *list;

    if (tmp == NULL)
        return NULL;
    if (index == 0) {
        *list = NULL;
        return (tmp);
    }
    for (int i = 0; i < index; i++)
        tmp = tmp->n_node;
    if (tmp == NULL) return NULL;
    if (tmp->p_node != NULL) {
        tmp->p_node->n_node = NULL;
        tmp->p_node = NULL;
    }
    return (tmp);
}