#pragma once

#include <stdint.h>
#include <stddef.h>
#include <sys/paging/pml4t.h>

static inline pml4t64_t * read_page_table() {
    pml4t64_t * page_table;
    asm volatile ("mov %%cr3, %0" : "=r" (page_table));
    return page_table;
}