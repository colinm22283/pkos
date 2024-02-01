#pragma once

#include <sys/paging/pml4t.h>
#include <sys/paging/pdpt.h>
#include <sys/paging/pdt.h>
#include <sys/paging/pt.h>

extern __SECTION(".page_tables") pml4t64_t pml4t;
extern __SECTION(".page_tables") pdpt64_t  pdpt;
extern __SECTION(".page_tables") pdt64_t   pdt;
extern __SECTION(".page_tables") pt64_t    pt;

void page_tables_init();