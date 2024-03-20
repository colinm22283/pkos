#include <paging/map_kernel.h>

#include <paging/tables.h>
#include <paging/translation.h>

#include <memory/memset.h>

#include <sys/paging/load_page_table.h>

#include <sys/msr/read_msr.h>
#include <sys/msr/write_msr.h>
#include <sys/msr/msr_numbers.h>

void paging_map_kernel() {
    // set the NXE flag
    write_msr(MSR_IA32_EFER, read_msr(MSR_IA32_EFER) | (1 << 11));

    memset(paging_kernel_pml4t,  0, sizeof(pml4t64_t));
    memset(paging_kernel_pdpt,   0, sizeof(pdpt64_t));
    memset(paging_kernel_pdt,    0, sizeof(pdt64_t));
    memset(paging_kernel_pt,     0, sizeof(pt64_t));
    memset(paging_identity_pdt,  0, sizeof(pdt64_t));
    memset(paging_identity_pt,   0, sizeof(pt64_t));

    PML4T64_SET_ADDRESS(paging_kernel_pml4t[0], paging_kernel_virtual_to_physical(paging_kernel_pdpt));
    paging_kernel_pml4t[0].present = 1;
    paging_kernel_pml4t[0].read_write = 1;

    PDPT64_SET_ADDRESS(paging_kernel_pdpt[3], paging_kernel_virtual_to_physical(paging_kernel_pdt));
    paging_kernel_pdpt[3].present = 1;
    paging_kernel_pdpt[3].read_write = 1;
    PDT64_SET_ADDRESS(paging_kernel_pdt[0], paging_kernel_virtual_to_physical(paging_kernel_pt));
    paging_kernel_pdt[0].present = 1;
    paging_kernel_pdt[0].read_write = 1;
    pt64_map_2mb(&paging_kernel_pt, 0x100000);

    PDPT64_SET_ADDRESS(paging_kernel_pdpt[0], paging_kernel_virtual_to_physical(paging_identity_pdt));
    paging_kernel_pdpt[0].present = 1;
    paging_kernel_pdpt[0].read_write = 1;
    PDT64_SET_ADDRESS(paging_identity_pdt[0], paging_kernel_virtual_to_physical(paging_identity_pt));
    paging_identity_pdt[0].present = 1;
    paging_identity_pdt[0].read_write = 1;
    paging_identity_pdt[0].execute_disable = true;
    pt64_map_2mb(&paging_identity_pt, 0x00);

    load_page_table(paging_kernel_virtual_to_physical(paging_kernel_pml4t));
}