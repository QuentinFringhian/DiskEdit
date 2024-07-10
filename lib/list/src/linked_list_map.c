#include <unistd.h>
#include "linked_list.h"

void linked_list_map(linked_list_t *list, void (*func)(void *))
{
    linked_list_t *current = list;

    while (current != NULL) {
        func(current->data);
        current = current->n_node;
    }
}