#include <paging/allocator.h>

#include <memory/memory_map.h>

bool page_allocator_init() {
    primary_memory_region_t primary_region = get_primary_memory_region();

    if (primary_region.length == 0) {
        return false;
    }



    return true;
}