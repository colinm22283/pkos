#pragma once

#include <entry.h>

#include <memory/kernel.h>

static inline void * paging_kernel_virtual_to_physical(void * virtual_address, uint64_t kernel_physical_address) {
    return (void *) ((intptr_t) virtual_address + kernel_physical_address - KERNEL_START);
}

static inline void * paging_kernel_physical_to_virtual(void * physical_address, uint64_t kernel_physical_address) {
    return physical_address + KERNEL_START - kernel_physical_address;
}