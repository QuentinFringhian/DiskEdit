#include <unistd.h>
#include "linked_list.h"

void linked_list_map_arg(linked_list_t *list, void (*func)(void *, void *), void *arg)
{
    linked_list_t *current = list;

    while (current != NULL) {
        func(current->data, arg);
        current = current->n_node;
    }
}