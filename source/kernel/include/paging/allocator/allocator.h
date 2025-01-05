#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <defs.h>

typedef struct {
    void * vaddr;
    uint64_t pages;
} page_allocation_t;

#define PAGING_NULL_ALLOCATION ((page_allocation_t) { .vaddr = NULL, .pages = 0, })
#define PAGING_ALLOCATION_VALID(alloc) (alloc.pages == 0)

bool page_allocator_init();
bool page_allocator_map(page_allocation_t * allocation, uint64_t paddr, void * vaddr, uint64_t pages);
bool page_allocator_free(page_allocation_t handle);
