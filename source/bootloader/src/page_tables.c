#include <stdint.h>

#include <page_tables.h>

#include <memory/memset.h>

__SECTION(".page_tables") pml4t64_t pml4t;
__SECTION(".page_tables") pdpt64_t  identity_pdpt;
__SECTION(".page_tables") pdt64_t   identity_pdt;
__SECTION(".page_tables") pt64_t    identity_pt;

void page_tables_init() {
    memset(&pml4t,         0, sizeof(pml4t64_t));
    memset(&identity_pdpt, 0, sizeof(pdpt64_t));
    memset(&identity_pdt,  0, sizeof(pdt64_t));
    memset(&identity_pt,   0, sizeof(pt64_t));

    // identity map the first 2MB
    PML4T64_SET_ADDRESS(pml4t[0],        &identity_pdpt);
    PDPT64_SET_ADDRESS(identity_pdpt[0], &identity_pdt );
    PDT_SET_ADDRESS(identity_pdt[0],     &identity_pt  );

    pt64_map_2mb(&identity_pt, 0x00000000);
}

