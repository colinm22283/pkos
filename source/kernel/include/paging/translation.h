#pragma once

#include <entry.h>

static inline void * paging_kernel_virtual_to_physical(void * virtual_address) {
    return (void *) ((intptr_t) virtual_address + 0x100000 - 0xC0000000);
}

static inline void * paging_kernel_physical_to_virtual(void * physical_address) {
    return physical_address + 0xC0000000 - 0x100000;
}