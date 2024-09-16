#include <stddef.h>

#include <paging/allocator.h>

root_allocator_page_t * allocator_root_page;
allocator_page_t * allocator_page;
void * allocator_space_start;