#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    void * vaddr;
    uint64_t paddr;
} mapped_segment_t;

bool paging_map(uint64_t paddr, void * vaddr);