#pragma once

#include <defs.h>

#include <sys/paging/pml4t.h>
#include <sys/paging/pdpt.h>
#include <sys/paging/pdt.h>
#include <sys/paging/pt.h>

typedef union {
    pml4t64_t pml4t;
    pdpt64_t pdpt;
    pdt64_t pdt;
    pt64_t pt;
} page_table_entry_t;

extern pml4t64_t paging_kernel_pml4t;
extern pdpt64_t  paging_kernel_pdpt;
extern pdt64_t   paging_kernel_pdt;
extern pt64_t    paging_kernel_pt;

extern pdt64_t   paging_identity_pdt;
extern pt64_t    paging_identity_pt;