#include <stdint.h>

#include <page_tables.h>

__SECTION(".page_tables") pml4t64_t pml4t;
__SECTION(".page_tables") pdpt64_t  pdpt;
__SECTION(".page_tables") pdt64_t   pdt;
__SECTION(".page_tables") pt64_t    pt;

void page_tables_init() {
}