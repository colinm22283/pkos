#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <defs.h>

#define ALLOCATOR_PAGE_TAG_COUNT ((4096 - sizeof(uint16_t) - 2 * sizeof(union allocator_page_s *)) / sizeof(allocator_tag_t))

typedef struct {
    void * vaddr;
    uint64_t pages;
} page_allocation_t;
#define PAGING_NULL_ALLOCATION ((page_allocation_t) { .vaddr = NULL, .pages = 0, })
#define PAGING_ALLOCATION_VALID(alloc) (alloc.pages == 0)

bool page_allocator_init();
page_allocation_t page_allocator_map(void * paddr, void * vaddr, uint64_t pages);
bool page_allocator_free(page_allocation_t handle);
