#include "paging/init.h"

#include "paging/tables.h"
#include "paging/translation.h"

#include <memory/kernel.h>

#include "util/memory/memset.h"

#include "sys/paging/load_page_table.h"

#include "sys/msr/set_msr.h"
#include "sys/msr/msr_numbers.h"
#include "sys/paging/read_page_table.h"

void paging_init() {
    // set the NXE flag
    set_msr(MSR_IA32_EFER, 1 << 11);

    memset(paging_kernel_pml4t,  0, sizeof(pml4t64_t));
    memset(paging_kernel_pdpt,   0, sizeof(pdpt64_t));
    memset(paging_kernel_pdt,    0, sizeof(pdt64_t));
    memset(paging_kernel_pt,     0, sizeof(pt64_t));
    memset(paging_identity_pdt,  0, sizeof(pdt64_t));
    memset(paging_identity_pt,   0, sizeof(pt64_t));

    pml4t64_t * old_pml4t = read_page_table();

    pdpt64_t * old_pdpt   = PML4T64_GET_ADDRESS((*old_pml4t)[0]);
    pdt64_t * old_pdt     = PDPT64_GET_ADDRESS((*old_pdpt)[3]);
    pt64_t * old_pt       = PDT64_GET_ADDRESS((*old_pdt)[0]);
    uint64_t kernel_physical_address = (uint64_t) PT64_GET_ADDRESS((*old_pt)[0]);



    pml4t64_entry_t * pml4t_entry = pml4t64_map_address(
        &paging_kernel_pml4t,
        paging_kernel_virtual_to_physical(
            paging_kernel_pdpt,
            kernel_physical_address
        ),
        KERNEL_START
    );
    pml4t_entry->present = 1;
    pml4t_entry->read_write = 1;

    pdpt64_entry_t * pdpt_entry  = pdpt64_map_address(
        &paging_kernel_pdpt,
        paging_kernel_virtual_to_physical(
            paging_kernel_pdt,
            kernel_physical_address
        ),
        KERNEL_START
    );
    pdpt_entry->present = 1;
    pdpt_entry->read_write = 1;

    pdt64_entry_t * pdt_entry = pdt64_map_address(
        &paging_kernel_pdt,
        paging_kernel_virtual_to_physical(
            paging_kernel_pt,
            kernel_physical_address
        ),
        KERNEL_START
    );
    pdt_entry->present = 1;
    pdt_entry->read_write = 1;

    pt64_map_2mb(&paging_kernel_pt, kernel_physical_address);

    PDPT64_SET_ADDRESS(paging_kernel_pdpt[0], paging_kernel_virtual_to_physical(paging_identity_pdt, kernel_physical_address));
    paging_kernel_pdpt[0].present = 1;
    paging_kernel_pdpt[0].read_write = 1;
    PDT64_SET_ADDRESS(paging_identity_pdt[0], paging_kernel_virtual_to_physical(paging_identity_pt, kernel_physical_address));
    paging_identity_pdt[0].present = 1;
    paging_identity_pdt[0].read_write = 1;
    paging_identity_pdt[0].execute_disable = true;
    pt64_map_2mb(&paging_identity_pt, 0x00);

    load_page_table(paging_kernel_virtual_to_physical(paging_kernel_pml4t, kernel_physical_address));
}