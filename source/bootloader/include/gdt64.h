#pragma once

#include <sys/gdt/gdt64.h>
#include <sys/gdt/gdt_ptr.h>

typedef struct __PACKED {
    gdt64_entry_t null;
    gdt64_entry_t code;
    gdt64_entry_t data;
} gdt64_t;

extern __SECTION(".gdt64") gdt64_t gdt64;

extern __SECTION(".gdt64_ptr") gdt_ptr_t gdt64_ptr;

void gdt64_init();