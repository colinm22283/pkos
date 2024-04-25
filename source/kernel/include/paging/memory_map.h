#pragma once

#include <stdint.h>

#include <defs.h>

#include <sys/memory_map/memory_map.h>

__SECTION(".memory_map")      extern memory_map_entry_t memory_map[(0x200 - 4) / sizeof(memory_map_entry_t)];
__SECTION(".memory_map_size") extern const uint32_t     memory_map_size;

typedef struct {
    uint64_t base, length;
} primary_memory_region_t;

primary_memory_region_t get_primary_memory_region();