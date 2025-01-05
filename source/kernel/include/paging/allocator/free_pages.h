#pragma once

#include <stdint.h>
#include <stddef.h>

#define PAGING_REGIONS_COUNT_1 (8)
#define PAGING_REGIONS_COUNT_2 (8)
#define PAGING_REGIONS_COUNT_4 (8)
#define PAGING_REGIONS_COUNT_8 (8)
#define PAGING_REGIONS_COUNT_16 (8)
#define PAGING_REGIONS_COUNT_32 (8)
#define PAGING_REGIONS_COUNT_64 (8)
#define PAGING_REGIONS_COUNT_128 (8)

typedef struct {
    size_t start, end;
} free_page_info_t;

extern free_page_info_t free_pages_info_1[PAGING_REGIONS_COUNT_1];
extern free_page_info_t free_pages_info_2[PAGING_REGIONS_COUNT_2];
extern free_page_info_t free_pages_info_4[PAGING_REGIONS_COUNT_4];
extern free_page_info_t free_pages_info_8[PAGING_REGIONS_COUNT_8];
extern free_page_info_t free_pages_info_16[PAGING_REGIONS_COUNT_16];
extern free_page_info_t free_pages_info_32[PAGING_REGIONS_COUNT_32];
extern free_page_info_t free_pages_info_64[PAGING_REGIONS_COUNT_64];
extern free_page_info_t free_pages_info_128[PAGING_REGIONS_COUNT_128];

extern uint64_t free_pages_1[PAGING_REGIONS_COUNT_1];
extern uint64_t free_pages_2[PAGING_REGIONS_COUNT_2];
extern uint64_t free_pages_4[PAGING_REGIONS_COUNT_4];
extern uint64_t free_pages_8[PAGING_REGIONS_COUNT_8];
extern uint64_t free_pages_16[PAGING_REGIONS_COUNT_16];
extern uint64_t free_pages_32[PAGING_REGIONS_COUNT_32];
extern uint64_t free_pages_64[PAGING_REGIONS_COUNT_64];
extern uint64_t free_pages_128[PAGING_REGIONS_COUNT_128];