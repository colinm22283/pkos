#pragma once

#include "../../../../../../../../opt/cross64/lib/gcc/x86_64-elf/14.0.1/include/stdint.h"

#include "../../../system/include/defs.h"

#include "../../../system/include/sys/memory_map/memory_map.h"

__SECTION(".memory_map")      extern volatile memory_map_entry_t memory_map[(0x200 - 4) / sizeof(memory_map_entry_t)];
__SECTION(".memory_map_size") extern volatile const uint32_t     memory_map_size;

typedef struct {
    uint64_t base, length;
} primary_memory_region_t;

primary_memory_region_t get_primary_memory_region();