#pragma once

#include <memory/memory_map.h>

#include <sys/paging/pml4t.h>
#include <sys/paging/pdpt.h>
#include <sys/paging/pdt.h>
#include <sys/paging/pt.h>

extern primary_memory_region_t paging_alloc_region;

void paging_init();
