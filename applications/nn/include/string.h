#pragma once

#include <stdint.h>

static inline bool streq(const char * a, const char * b) {
    while (true) {
        if (*a != *b) {
            return false;
        }
        else {
            if (*a == '\0') return true;
        }

        a++;
        b++;
    }
}

uint64_t strlen(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;
    return str_size;
}

void strcpy(char * dst, const char * src) {
    uint64_t i = 0;
    do {
        dst[i] = src[i];
        i++;
    }
    while (src[i] != '\0');
    dst[i] = src[i];
}

uint64_t strcmp(const char * a, const char * b) {
    uint64_t i;

    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        if (a[i] != b[i]) return a[i] - b[i];
    }

    return a[i] - b[i];
}