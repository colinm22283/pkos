#pragma once

#include <stdint.h>

#include <paging/tables.h>
#include <paging/translation.h>

static inline void map_page(pml4t64_t * pml4t, pdpt64_t * pdpt, pdt64_t * pdt, pt64_t * pt, void * vaddr, uint64_t paddr) {
//    uint64_t pml4t_index = (((uint64_t) vaddr) >> 39) & 0x1FF;
//    uint64_t pdpt_index  = (((uint64_t) vaddr) >> 30) & 0x1FF;
//    uint64_t pdt_index   = (((uint64_t) vaddr) >> 21) & 0x1FF;
//    uint64_t pt_index    = (((uint64_t) vaddr) >> 12) & 0x1FF;

    pml4t64_entry_t * pml4t_entry = pml4t64_map_address(pml4t, (void *) paging_virtual_to_physical(pdpt), (uint64_t) vaddr);
    pdpt64_entry_t * pdpt_entry   = pdpt64_map_address(pdpt, (void *) paging_virtual_to_physical(pdt), (uint64_t) vaddr);
    pdt64_entry_t * pdt_entry     = pdt64_map_address(pdt, (void *) paging_virtual_to_physical(pt), (uint64_t) vaddr);
    pt64_entry_t * pt_entry     = pt64_map_address(pt, paddr, (uint64_t) vaddr);

    pml4t_entry->present = true;
    pdpt_entry->present = true;
    pdt_entry->present = true;
    pt_entry->present = true;
}