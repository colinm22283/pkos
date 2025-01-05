#pragma once

#include <entry.h>

#include <memory/kernel.h>

#include <paging/tables.h>
#include <paging/paging.h>
#include <paging/allocator/allocator.h>

extern uint64_t kernel_physical_address;

static inline uint64_t paging_kernel_virtual_to_physical(void * virtual_address) {
    return (uint64_t) ((intptr_t) virtual_address + kernel_physical_address - KERNEL_START);
}

static inline void * paging_kernel_physical_to_virtual(uint64_t physical_address) {
    return (void *) (physical_address + KERNEL_START - kernel_physical_address);
}

static inline void * page_table_physical_to_virtual_address(uint64_t paddr) {
    void * kernel_vaddr = paging_kernel_physical_to_virtual(paddr);

    if (
        kernel_vaddr == &paging_kernel_pml4t ||
        kernel_vaddr == &paging_kernel_pdpt ||
        kernel_vaddr == &paging_kernel_pdt ||
        kernel_vaddr == &paging_kernel_pt ||
        kernel_vaddr == &paging_identity_pdt ||
        kernel_vaddr == &paging_identity_pt ||
        kernel_vaddr == &paging_table_space_pt
    ) return kernel_vaddr;

    return (void *) (paddr - paging_alloc_region.base + PAGE_ALLOCATOR_VIRTUAL_BASE);
}

static inline uint64_t paging_virtual_to_physical(void * vaddr) {
    uint64_t pml4t_index = (((uint64_t) vaddr) >> 39) & 0x1FF;
    uint64_t pdpt_index  = (((uint64_t) vaddr) >> 30) & 0x1FF;
    uint64_t pdt_index   = (((uint64_t) vaddr) >> 21) & 0x1FF;
    uint64_t pt_index    = (((uint64_t) vaddr) >> 12) & 0x1FF;

    pdpt64_t * pdpt = page_table_physical_to_virtual_address((uint64_t) PML4T64_GET_ADDRESS(paging_kernel_pml4t[pml4t_index]));
    pdt64_t * pdt = page_table_physical_to_virtual_address((uint64_t) PDPT64_GET_ADDRESS((*pdpt)[pdpt_index]));
    pt64_t * pt = page_table_physical_to_virtual_address((uint64_t) PDT64_GET_ADDRESS((*pdt)[pdt_index]));
    return PT64_GET_ADDRESS((*pt)[pt_index]);
}
