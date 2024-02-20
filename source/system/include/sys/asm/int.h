#pragma once

#include <stdint.h>

static inline void asm_int(uint8_t code) {
    asm volatile ("int %0" :: "m" (code));
}