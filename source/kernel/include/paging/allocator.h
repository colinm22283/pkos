#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <defs.h>

#define ALLOCATOR_PAGE_TAG_COUNT ((4096 - sizeof(uint16_t) - 2 * sizeof(union allocator_page_s *)) / sizeof(allocator_tag_t))

typedef void * allocator_handle_t;
#define ALLOCATOR_NULL_HANDLE ((allocator_handle_t *) NULL)

typedef struct __PACKED allocator_tag_s {
    void * start;
    uint64_t page_count;

    struct allocator_tag_s * prev;
    struct allocator_tag_s * next;
} allocator_tag_t;

typedef union __PACKED allocator_page_s {
    struct {
        uint16_t tag_count;
        allocator_tag_t tags[ALLOCATOR_PAGE_TAG_COUNT];
        union allocator_page_s * prev;
        union allocator_page_s * next;
    };
    char _padding[4096];
} allocator_page_t;

typedef union __PACKED {
    struct {
        allocator_page_t * head;
        allocator_page_t * tail;
    };
    char _padding[4096];
} root_allocator_page_t;

extern root_allocator_page_t * allocator_root_page;
extern void * allocator_space_start;

bool page_allocator_init();
allocator_handle_t page_allocator_alloc(uint64_t pages);
