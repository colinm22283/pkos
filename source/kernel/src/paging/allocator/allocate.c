#include <paging/allocator.h>

allocator_handle_t page_allocator_alloc(uint64_t pages) {
    allocator_page_t * head_page = allocator_root_page->head;

    if (head_page->tag_count >= ALLOCATOR_PAGE_TAG_COUNT - 1) {
        // TODO: allocate new tag page
    }
    else {

    }

    return ALLOCATOR_NULL_HANDLE;
}