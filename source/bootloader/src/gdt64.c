#include <gdt64.h>

__SECTION(".gdt64") gdt64_t gdt64;

__SECTION(".gdt64_ptr") gdt_ptr_t gdt64_ptr;

void gdt64_init() {
    gdt64 = (gdt64_t) {
        .null = GDT64_NULL_ENTRY,
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

    gdt64_ptr = DEFINE_GDT_POINTER(gdt64);
}