#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <util/math/min.h>

#define PAGING_BITMAP_LEVELS (4)
#define PAGING_BITMAP_VADDR ((uint64_t *) 0x008000000000)

#define PAGING_BITMAP_GET_INDEX(index) ((bool) ((PAGING_BITMAP_VADDR[(index) / 64] >> (index % 64)) & 0b1))
#define PAGING_BITMAP_SET_INDEX(index) do { PAGING_BITMAP_VADDR[index / 64] |= 0b1 << (index % 64); } while (0);
#define PAGING_BITMAP_CLEAR_INDEX(index) do { PAGING_BITMAP_VADDR[index / 64] &= ~(0b1 << (index % 64)); } while (0);

// TODO: finish
#define PAGING_BITMAP_GET(level, index) ((bool) ((PAGING_BITMAP_VADDR[(index) / 64] >> (index % 64)) & 0b1))
#define PAGING_BITMAP_SET(level, index) do { PAGING_BITMAP_VADDR[index / 64] |= 0b1 << (index % 64); } while (0);
#define PAGING_BITMAP_CLEAR(level, index) do { PAGING_BITMAP_VADDR[index / 64] &= ~(0b1 << (index % 64)); } while (0);

extern uint64_t bitmap_paddr;
extern uint64_t bitmap_available_pages;
extern uint64_t bitmap_size;

void paging_bitmap_init(void);

static inline uint64_t bitmap_reserve(uint64_t level) {
    uint64_t * level_bits = PAGING_BITMAP_VADDR;

    uint64_t level_pages = bitmap_available_pages;
    uint64_t level_page_size = 0x1000;

    for (uint64_t i = 0; i < level; i++) {
        level_bits += level_pages / 64;

        level_pages /= 2;

        level_page_size *= 2;
    }
    level_pages *= 2;

    for (uint64_t i = 0; i < level_pages; i++) {
        if (PAGING_BITMAP_GET(level, i)) {

        }
    }

    return 0;
}
