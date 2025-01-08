#include <paging/init.h>
#include <paging/tables.h>
#include <paging/region.h>
#include <paging/translation.h>
#include <paging/bitmap.h>

#include <memory/primary_region.h>
#include <memory/kernel.h>

#include <util/memory/memset.h>
#include <util/math/div_up.h>

#include <sys/msr/set_msr.h>
#include <sys/paging/load_page_table.h>

pdt64_t test_pdt;
pt64_t test_pt;

void paging_init() {
    paging_region_start = primary_region_start + KERNEL_SIZE;
    paging_region_end = primary_region_end;

    paging_region_start = DIV_UP(paging_region_start, 0x1000) * 0x1000;
    paging_region_end = (paging_region_end / 0x1000) * 0x1000;

    // set the NXE flag
    set_msr(MSR_IA32_EFER, 1 << 11);

    memset(paging_kernel_pml4t,    0, sizeof(pml4t64_t));
    memset(paging_kernel_pdpt,     0, sizeof(pdpt64_t));
    memset(paging_kernel_pdt,      0, sizeof(pdt64_t));
    memset(paging_kernel_pt,       0, sizeof(pt64_t));
    memset(paging_identity_pdt,    0, sizeof(pdt64_t));
    memset(paging_identity_pt,     0, sizeof(pt64_t));
    memset(paging_bitmap_pdpt,     0, sizeof(pdpt64_t));
    memset(paging_temp_pt,         0, sizeof(pt64_t));

    pml4t64_entry_t * pml4t_entry = pml4t64_map_address(
        &paging_kernel_pml4t,
        paging_kernel_virtual_to_physical(paging_kernel_pdpt),
        KERNEL_START
    );
    pml4t_entry->present = 1;
    pml4t_entry->read_write = 1;

    pdpt64_entry_t * pdpt_entry  = pdpt64_map_address(
        &paging_kernel_pdpt,
        paging_kernel_virtual_to_physical(paging_kernel_pdt),
        KERNEL_START
    );
    pdpt_entry->present = 1;
    pdpt_entry->read_write = 1;

    pdt64_entry_t * pdt_entry = pdt64_map_address(
        &paging_kernel_pdt,
        paging_kernel_virtual_to_physical(paging_kernel_pt),
        KERNEL_START
    );
    pdt_entry->present = 1;
    pdt_entry->read_write = 1;

    pt64_map_2mb(&paging_kernel_pt, primary_region_start);

    PDPT64_SET_ADDRESS(paging_kernel_pdpt[0], paging_kernel_virtual_to_physical(paging_identity_pdt));
    paging_kernel_pdpt[0].present = 1;
    paging_kernel_pdpt[0].read_write = 1;
    PDT64_SET_ADDRESS(paging_identity_pdt[0], paging_kernel_virtual_to_physical(paging_identity_pt));
    paging_identity_pdt[0].present = 1;
    paging_identity_pdt[0].read_write = 1;
    paging_identity_pdt[0].execute_disable = true;
    pt64_map_2mb(&paging_identity_pt, 0x00);

    pdt64_entry_t * temp_pdt_entry = pdt64_map_address(
        &paging_kernel_pdt,
        paging_kernel_virtual_to_physical(paging_temp_pt),
        PAGING_TEMP_PT_VADDR
    );
    temp_pdt_entry->present = true;
    temp_pdt_entry->read_write = true;

    load_page_table((void *) paging_kernel_virtual_to_physical(paging_kernel_pml4t));

    paging_bitmap_init();
}