#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <sys/paging/pml4t.h>

void paging_clear_identity_map();
void paging_create_table(pml4t_t * pml4t, void * physical_addr, uint64_t pages);
bool paging_alloc(uint64_t pages);