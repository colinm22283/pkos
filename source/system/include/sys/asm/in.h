#pragma once

#include <stdint.h>

static inline char inb(uint16_t port) {
    char ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "Nd" (port) : "memory");
    return ret;
}