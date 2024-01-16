#pragma once

#include <stdint.h>

#include <defs.h>

typedef struct __PACKED {
    uint16_t size : 16;
    const void * pointer;
} gdt_ptr_t;

#define DEFINE_GDT_POINTER(gdt_table) ((gdt_ptr_t) { .size = sizeof(gdt_table) - 1, .pointer = &(gdt_table), })
