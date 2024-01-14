#include <defs.h>

#include <sys/gdt/gdt64.h>
#include <sys/gdt/gdt_desc.h>
#include <sys/tss/tss64.h>

__SECTION(".bootloader_gdt64")
const struct __PACKED {
    gdt64_entry_t null;
    gdt64_entry_t code;
    gdt64_entry_t data;
    gdt64_entry_t tss;
} gdt64 = {
    .null = GDT64_NULL_ENTRY,
    .code = {
        .base_upper = 0,
        .base_lower = 0,
        .limit_upper = 0xF,
        .limit_lower = 0xFFFF,
        .flags =
        GDT_FLAGS_GRANULARITY |
        GDT_FLAGS_LONG_MODE,
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
        GDT_FLAGS_GRANULARITY |
        GDT_FLAGS_LONG_MODE,
        .access =
        GDT_ACCESS_PRESENT |
        GDT_ACCESS_PRIVILEGE_LEVEL(0) |
        GDT_ACCESS_TYPE |
        GDT_ACCESS_READ_WRITE,
    },
    .tss = {
        .base_lower = 0,
        .base_upper = 0,
        .limit_lower = sizeof(tss64_t),
        .limit_upper = 0,
        .access = 0x89,
        .flags = 0,
    },
};
__SECTION(".bootloader_gdt64_descriptor") const gdt_descriptor_t gdt64_descriptor = DEFINE_GDT_DESCRIPTOR(gdt64);