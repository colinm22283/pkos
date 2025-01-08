#pragma once

#include <sys/paging/pml4t.h>
#include <sys/paging/pdpt.h>
#include <sys/paging/pdt.h>
#include <sys/paging/pt.h>

#define PAGING_TEMP_PT_VADDR ((void *) 0xD0000000)

extern pml4t64_t paging_kernel_pml4t;
extern pdpt64_t  paging_kernel_pdpt;
extern pdt64_t   paging_kernel_pdt;
extern pt64_t    paging_kernel_pt;

extern pdt64_t   paging_identity_pdt;
extern pt64_t    paging_identity_pt;

extern pdpt64_t  paging_bitmap_pdpt;

extern pt64_t    paging_temp_pt;