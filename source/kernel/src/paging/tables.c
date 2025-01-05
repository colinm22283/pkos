#include <paging/tables.h>

pml4t64_t paging_kernel_pml4t;
pdpt64_t  paging_kernel_pdpt;
pdt64_t   paging_kernel_pdt;
pt64_t    paging_kernel_pt;

pdt64_t   paging_identity_pdt;
pt64_t    paging_identity_pt;

pt64_t    paging_table_space_pt;