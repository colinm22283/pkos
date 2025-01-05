#include <stddef.h>

#include <paging/map.h>
#include <paging/paging.h>
#include <paging/tables.h>
#include <paging/allocator/allocator.h>
#include <paging/allocator/table_allocator.h>

bool page_allocator_init() {
    table_allocator_paddr = ((paging_alloc_region.base + paging_alloc_region.length) % 0x1000) - 0x1000;
    table_allocator_vaddr = PAGE_TABLE_ALLOCATOR_VIRTUAL_BASE;

    map_page(
        &paging_kernel_pml4t,
        &paging_kernel_pdpt,
        &paging_kernel_pdt,
        &paging_table_space_pt,
        PAGE_TABLE_ALLOCATOR_VIRTUAL_BASE,
        table_allocator_paddr
    );

    return true;
}
