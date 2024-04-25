#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    PAGE_ALLOCATOR_INDEX_TABLE_ENTRY_FLAGS_IS_FREE = 1,
} page_allocator_index_table_entry_flags_t;

typedef struct {
    page_allocator_index_table_entry_flags_t flags;
    void * page_address;
    uint64_t size;
} page_allocator_index_table_entry_t;

typedef struct page_allocator_index_table_s {
    struct page_allocator_index_table_s * next;
    uint16_t elements;
    page_allocator_index_table_entry_t entries[
        (
            4096 -
            sizeof(struct page_allocator_index_table_s *) -
            sizeof(uint16_t)
        ) /
        sizeof(page_allocator_index_table_entry_t)
    ];
} page_allocator_index_table_t;


extern page_allocator_index_table_t * allocator_index_head;

bool page_allocator_init();