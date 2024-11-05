#include <paging/tables.h>
#include <paging/allocator/allocator.h>

#include <sys/paging/address_translation.h>

page_allocation_t page_allocator_map(void * paddr, void * vaddr, uint64_t pages) {
    pml4t64_entry_t * pml4t_entry = pml4t_index(&paging_kernel_pml4t, vaddr);

    if (!pml4t_entry->present) {
        // allocate pdpt entry

        
    }

    pdpt64_t * pdpt = PML4T64_GET_ADDRESS(*pml4t_entry);

    pdpt64_entry_t * pdpt_entry = pdpt_index(pdpt, vaddr);

    if (!pdpt_entry->present) {

    }

    pdt64_t * pdt = PDPT64_GET_ADDRESS(*pdpt_entry);

    pdt64_entry_t * pdt_entry = pdt_index(pdt, vaddr);

    if (!pdt_entry->present) {

    }

    pt64_t * pt = PDT64_GET_ADDRESS(*pdt_entry);

    pt64_entry_t * pt_entry = pt_index(pt, vaddr);

    if (!pt_entry->present) {
        

        return (page_allocation_t) {
            .vaddr = vaddr,
            .pages = pages,
        };
    }

    return PAGING_NULL_ALLOCATION;
}
