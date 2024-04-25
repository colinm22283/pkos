#include <paging/allocator.h>

#include <paging/memory_map.h>

page_allocator_index_table_t * allocator_index_head;
uint64_t allocator_region_size;

bool page_allocator_init() {
    primary_memory_region_t primary_region = get_primary_memory_region();

    if (primary_region.length == 0) return false;

    allocator_index_head = (page_allocator_index_table_t *) primary_region.base;
    allocator_region_size = primary_region.length;

    return true;
}