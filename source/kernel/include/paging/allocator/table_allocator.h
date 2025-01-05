#pragma once

#include <stdint.h>

#include <defs.h>

#define PAGE_TABLE_ALLOCATOR_VIRTUAL_BASE ((void *) 0xD0000000)

typedef struct {
    uint8_t _reserved0 : 6;
    uint8_t in_use;
    uint64_t _reserved1 : 57;
} __PACKED generic_page_table_entry_t;

typedef generic_page_table_entry_t generic_page_table_t[512];

extern unsigned int current_
extern uint64_t table_allocator_paddr;
extern generic_page_table_t * table_allocator_vaddr;

void * allocate_page_table(void);