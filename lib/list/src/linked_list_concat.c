#include <stdlib.h>
#include "linked_list.h"

void linked_list_concat(linked_list_t **list1, linked_list_t *list2)
{
    linked_list_t *_list1 = *list1;

    if (_list1 == NULL) {
        *list1 = list2;
        return;
    }
    for (; _list1->n_node != NULL; _list1 = _list1->n_node);
    _list1->n_node = list2;
    if (list2 != NULL)
        list2->p_node = _list1;
}