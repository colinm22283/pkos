#include <paging/tables.h>
#include <paging/paging.h>

void paging_clear_identity_map() {
    kernel_pml4t[0].present = 0;
}

void paging_create_table(pml4t_t * pml4t, void * physical_addr, uint64_t pages) {

}

bool paging_alloc(uint64_t pages) {

}