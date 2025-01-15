#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <paging/region.h>

#include <util/math/min.h>

#define PAGING_BITMAP_LEVELS (4)
#define PAGING_BITMAP_VADDR ((uint64_t *) 0x008000000000)

extern uint64_t bitmap_paddr;
extern uint64_t bitmap_available_pages;
extern uint64_t bitmap_size;

static inline bool paging_bitmap_get_index(uint64_t index) {
    return (PAGING_BITMAP_VADDR[(index) / 64] >> (index % 64)) & 0b1;
}
static inline void paging_bitmap_set_index(uint64_t index) {
    PAGING_BITMAP_VADDR[index / 64] |= 0b1 << (index % 64);
}
static inline void paging_bitmap_clear_index(uint64_t index) {
    PAGING_BITMAP_VADDR[index / 64] &= ~(0b1 << (index % 64));
}

static inline uint64_t paging_bitmap_index(uint64_t level, uint64_t index) {
    uint64_t level_index = 0;
    for (uint64_t i = 0; i < level; i++) {
        level_index += bitmap_available_pages / (i + 1);
    }
    return level_index + index;
}

static inline uint64_t paging_bitmap_address_to_index(uint64_t level, uint64_t paddr) {
    return paging_bitmap_index(level, (paddr / 0x1000) >> level);
}

static inline bool paging_bitmap_get(uint64_t level, uint64_t index) {
    return paging_bitmap_get_index(paging_bitmap_index(level, index));
}
static inline void paging_bitmap_set(uint64_t level, uint64_t index) {
    paging_bitmap_set_index(paging_bitmap_index(level, index));
}
static inline void paging_bitmap_clear(uint64_t level, uint64_t index) {
    paging_bitmap_clear_index(paging_bitmap_index(level, index));
}

void paging_bitmap_init(void);

uint64_t bitmap_reserve_level(uint64_t level);
bool bitmap_free_level(uint64_t level, uint64_t address);
