#pragma once

#include <entry.h>

#include <memory/kernel.h>
#include <memory/primary_region.h>

#include <paging/tables.h>

#include <sys/paging/read_page_table.h>

static inline uint64_t paging_kernel_virtual_to_physical(void * virtual_address) {
    return (uint64_t) ((intptr_t) virtual_address + primary_region_start - (intptr_t) KERNEL_START);
}

static inline void * paging_kernel_physical_to_virtual(uint64_t physical_address) {
    return (void *) (physical_address + (intptr_t) KERNEL_START - primary_region_start);
}

//static inline void * paging_table_physical_to_virtual(uint64_t paddr) {
//    void * kernel_vaddr = paging_kernel_physical_to_virtual(paddr);
//
//    if (
//        (void *) kernel_vaddr == &paging_kernel_pml4t ||
//        (void *) kernel_vaddr == &paging_kernel_pdpt ||
//        (void *) kernel_vaddr == &paging_kernel_pdt ||
//        (void *) kernel_vaddr == &paging_kernel_pt ||
//        (void *) kernel_vaddr == &paging_identity_pdt ||
//        (void *) kernel_vaddr == &paging_identity_pt ||
//        (void *) kernel_vaddr == &paging_bitmap_pdpt ||
//        (void *) kernel_vaddr == &paging_temp_pt
//    ) return kernel_vaddr;
//}

//static inline uint64_t paging_virtual_to_physical(void * vaddr) {
//    pml4t64_t * pml4t = read_page_table();
//
//    uint64_t pml4t_index = ((uint64_t) vaddr >> 39) & 0x1FF;
//    uint64_t pdpt_index  = ((uint64_t) vaddr >> 30) & 0x1FF;
//    uint64_t pdt_index   = ((uint64_t) vaddr >> 21) & 0x1FF;
//    uint64_t pt_index    = ((uint64_t) vaddr >> 12) & 0x1FF;
//
//
//}
