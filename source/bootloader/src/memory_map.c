#include <memory_map.h>

__SECTION(".memory_map")      memory_map_entry_t memory_map[(0x200 - 4) / sizeof(memory_map_entry_t)];
__SECTION(".memory_map_size") const uint32_t           memory_map_size;

void memory_map_sort() {
    memory_map_entry_t * base_pointer = memory_map;
    memory_map_entry_t * const top_pointer = memory_map + memory_map_size - 1;

    for (; base_pointer <= top_pointer; base_pointer++) {
        for (memory_map_entry_t * current = base_pointer; current <= base_pointer; current++) {
            if (current->base < base_pointer->base) {
                memory_map_entry_t temp = *current;
                *current = *base_pointer;
                *base_pointer = temp;
            }
        }
    }
}