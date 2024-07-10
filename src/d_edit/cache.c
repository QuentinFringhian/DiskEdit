#include <stdlib.h>
#include "d_edit/d_edit.h"

void add_block_cache(disk_t *d, block_buff_t *block)
{
    int cache_size = linked_list_size(d->cache);
    block_buff_t *_buff = NULL;

    for (int i = 0; i < cache_size; i++) {
        _buff = linked_list_get(d->cache, i);
        if (_buff->block_number == block->block_number && i != 0) {
            linked_list_remove(&d->cache, NULL, i);
            linked_list_push(&d->cache, block);
            return;
        }
    }
    if (cache_size >= MAX_BLOCK_IN_CACHE) {
        linked_list_remove(&d->cache, NULL, 0);
        linked_list_push(&d->cache, block);
    }
}

block_buff_t *get_block_cache(disk_t *d, int block_number)
{
    block_buff_t *_buff = NULL;

    for (cache_list_t *cache = d->cache; cache != NULL; cache = cache->n_node) {
        _buff = cache->data;
        if (_buff->block_number == block_number)
            return _buff;
    }
    return NULL;
}

void update_block_cache(disk_t *d, int block_number, unsigned char *data)
{
    block_buff_t *block = get_block_cache(d, block_number);

    if (block == NULL) return;
    free(block->data);
    block->data = data;
}