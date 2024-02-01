#include "defs.h"

#include "sys/gdt/gdt32.h"
#include "sys/gdt/gdt_ptr.h"

__SECTION(".gdt32") const struct __PACKED {
    gdt32_entry_t null;
    gdt32_entry_t code;
    gdt32_entry_t data;
} gdt32 = {
    .null = GDT32_NULL_ENTRY,
    .code = {
        .base_upper = 0,
        .base_lower = 0,
        .limit_upper = 0xF,
        .limit_lower = 0xFFFF,
        .flags =
        GDT_FLAGS_SIZE |
        GDT_FLAGS_GRANULARITY,
        .access =
        GDT_ACCESS_PRESENT |
        GDT_ACCESS_PRIVILEGE_LEVEL(0) |
        GDT_ACCESS_TYPE |
        GDT_ACCESS_EXECUTABLE |
        GDT_ACCESS_READ_WRITE,
    },
    .data = {
        .base_upper = 0,
        .base_lower = 0,
        .limit_upper = 0xF,
        .limit_lower = 0xFFFF,
        .flags =
        GDT_FLAGS_SIZE |
        GDT_FLAGS_GRANULARITY,
        .access =
        GDT_ACCESS_PRESENT |
        GDT_ACCESS_PRIVILEGE_LEVEL(0) |
        GDT_ACCESS_TYPE |
        GDT_ACCESS_READ_WRITE,
    },
};

__SECTION(".gdt32_ptr") const gdt_ptr_t gdt32_ptr = DEFINE_GDT_POINTER(gdt32);