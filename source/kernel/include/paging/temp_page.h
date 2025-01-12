#pragma once

#include <paging/translation.h>
#include <paging/tables.h>

#include <sys/paging/pml4t.h>
#include <sys/paging/pdpt.h>
#include <sys/paging/pdt.h>
#include <sys/paging/pt.h>

#include <sys/paging/load_page_table.h>
#include <sys/paging/invalidate_page.h>

static inline void * temp_pt_map_page(uint64_t paddr) {
    pt64_entry_t * pt_entry = pt64_map_address(&paging_temp_pt, paddr, PAGING_TEMP_PT_VADDR);
    pt_entry->present = true;
    pt_entry->read_write = true;

    invalidate_page(PAGING_TEMP_PT_VADDR);

    return PAGING_TEMP_PT_VADDR;
}

static inline void * temp_pt_map_2mb(uint64_t paddr) {
    pt64_map_2mb(&paging_temp_pt, paddr);

    invalidate_page(PAGING_TEMP_PT_VADDR);

    return PAGING_TEMP_PT_VADDR;
}