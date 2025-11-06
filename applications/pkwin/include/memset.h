#pragma once

#include <stdint.h>

static inline void memset(char * dst, char src, uint64_t size) {
    for (uint64_t i = 0; i < size; i++) dst[i] = src;
}