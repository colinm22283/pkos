#pragma once

typedef struct __attribute__((packed)) {
    uint16_t size : 16;
    union __attribute__((packed)) {
        uint32_t u32 : 32;
        uint64_t u64 : 64;
        const void * pointer;
    } offset;
} gdt_descriptor_t;

#define DEFINE_GDT_DESCRIPTOR(gdt_table) { .offset.pointer = &gdt_table, .size = sizeof(gdt_table) - 1, }
