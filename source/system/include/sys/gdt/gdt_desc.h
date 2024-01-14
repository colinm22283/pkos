#pragma once

#include <defs.h>

typedef struct __PACKED {
    uint16_t size : 16;

    const void * pointer;
} gdt_descriptor_t;

#define DEFINE_GDT_DESCRIPTOR(gdt_table) { .pointer = &gdt_table, .size = sizeof(gdt_table) - 1, }
