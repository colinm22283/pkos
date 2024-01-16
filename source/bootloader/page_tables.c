#include <sys/paging/pml4t.h>
#include <sys/paging/pdpt.h>
#include <sys/paging/pdt.h>
#include <sys/paging/pt.h>

__SECTION(".page_tables") pml4t_t pml4t;
__SECTION(".page_tables") pdpt_t  pdpt;
__SECTION(".page_tables") pdt_t   pdt;
__SECTION(".page_tables") pt_t    pt;