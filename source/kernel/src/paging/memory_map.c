#include <stddef.h>
#include <stdbool.h>

#include <paging/memory_map.h>

#include <sys/halt.h>

__SECTION(".memory_map")      volatile memory_map_entry_t memory_map[(0x200 - 4) / sizeof(memory_map_entry_t)];
__SECTION(".memory_map_size") volatile const uint32_t     memory_map_size;

primary_memory_region_t get_primary_memory_region() {
    primary_memory_region_t best_region = { .base = 0, .length = 0, };

    bool prev_region_free = false;
    for (uint32_t i = 0; i < memory_map_size; i++) {
        switch (memory_map[i].type) {
        case MEMORY_MAP_TYPE_USABLE: case MEMORY_MAP_TYPE_ACPI_RECLAIMABLE: {
            if (!prev_region_free) {
                best_region.base = memory_map[i].base;
                best_region.length = memory_map[i].length;
            }
            else {
                best_region.length += memory_map[i].length;
            }

            prev_region_free = true;
        } break;

        default: {
            prev_region_free = false;
        } break;
        }
    }

    return best_region;
}