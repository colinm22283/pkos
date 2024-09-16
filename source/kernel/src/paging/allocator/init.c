#include <stddef.h>

#include "paging/allocator.h"

#include "memory/memory_map.h"
#include <memory/kernel.h>

#include <util/math/max.h>

bool page_allocator_init() {
    allocator_root_page = (root_allocator_page_t *) KERNEL_END;
    allocator_page_t * allocator_page = (allocator_page_t *) (((char *) KERNEL_END) + sizeof(root_allocator_page_t));

    allocator_root_page->head = allocator_page;
    allocator_root_page->tail = allocator_page;

    return true;
}