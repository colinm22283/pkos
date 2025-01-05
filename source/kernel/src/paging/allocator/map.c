#include <paging/tables.h>
#include <paging/translation.h>
#include <paging/allocator/allocator.h>

#include <sys/paging/address_translation.h>

bool page_allocator_map(page_allocation_t * allocation, uint64_t paddr, void * vaddr, uint64_t pages) {
    if (
        ((uint64_t) paddr & 0xFFF) != 0 ||
        ((uint64_t) vaddr & 0xFFF) != 0
    ) return false;

    pml4t64_entry_t * pml4t_entry = pml4t_index(&paging_kernel_pml4t, vaddr);

    if (!pml4t_entry->present) {
        // allocate pdpt entry

        pml4t_entry->present = true;
    }

    pdpt64_t * pdpt = page_table_physical_to_virtual_address((uint64_t) PML4T64_GET_ADDRESS(*pml4t_entry));

    pdpt64_entry_t * pdpt_entry = pdpt_index(pdpt, vaddr);

    if (!pdpt_entry->present) {
        pdpt_entry->present = true;
    }

    pdt64_t * pdt = page_table_physical_to_virtual_address((uint64_t) PDPT64_GET_ADDRESS(*pdpt_entry));

    pdt64_entry_t * pdt_entry = pdt_index(pdt, vaddr);

    if (!pdt_entry->present) {
        pdt_entry->present = true;
    }

    pt64_t * pt = page_table_physical_to_virtual_address((uint64_t) PDT64_GET_ADDRESS(*pdt_entry));

    pt64_entry_t * pt_entry = pt_index(pt, vaddr);

    if (!pt_entry->present) {
        pt_entry->present = true;

        return true;
    }

    return false;
}
