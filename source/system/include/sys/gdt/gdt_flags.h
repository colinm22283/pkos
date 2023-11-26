#pragma once

enum {
    GDT_ACCESS_PRESENT    = 0b10000000,
    GDT_ACCESS_PRIVILEGE  = 0b01100000,
    GDT_ACCESS_TYPE       = 0b00010000,
    GDT_ACCESS_EXECUTABLE = 0b00001000,
    GDT_ACCESS_DIRECTION  = 0b00000100,
    GDT_ACCESS_READ_WRITE = 0b00000010,
    GDT_ACCESS_ACCESSED   = 0b00000001,
};
#define GDT_ACCESS_PRIVILEGE_LEVEL(level) ((level << 5) & GDT_ACCESS_PRIVILEGE)

enum {
    GDT_FLAGS_GRANULARITY = 0b1000,
    GDT_FLAGS_SIZE        = 0b0100,
    GDT_FLAGS_LONG_MODE   = 0b0010,
};
