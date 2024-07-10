#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_list_s {
    void *data;
    struct linked_list_s *n_node;
    struct linked_list_s *p_node;
} linked_list_t;

linked_list_t *linked_list_new(void *new_data);

void linked_list_push(linked_list_t **ll_head, void *new_data);
void linked_list_append(linked_list_t **ll_head, void *new_data);
void linked_list_insert(linked_list_t **ll_head, void *new_data, int index);

linked_list_t *linked_list_split(linked_list_t **list, int index);
void linked_list_concat(linked_list_t **list1, linked_list_t *list2);

void linked_list_map(linked_list_t *list, void (*func)(void *));
void linked_list_map_arg(linked_list_t *list, void (*func)(void *, void *), void *arg);

void linked_list_rotate(linked_list_t **ll_head, int n);

void *linked_list_get(linked_list_t *ll_head, int index);
void linked_list_remove(linked_list_t **ll_head, void (*free_data)(void *), int index);
void *linked_list_pop(linked_list_t **ll_head, int index);

int linked_list_size(linked_list_t *ll_head);

void linked_list_clear(linked_list_t **ll_head, void (*free_data)(void *));

#endif // LINKED_LIST_H