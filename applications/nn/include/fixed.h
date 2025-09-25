#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <print.h>

#define DECIMAL_LOC (10)

static inline void print_fixed(int64_t _num, uint64_t decimals);

static inline int64_t to_fixed(int64_t num) {
    return num << DECIMAL_LOC;
}

static inline int64_t fixed_mul(int64_t a, int64_t b) {
    bool invert = false;

    if (a < 0) {
        a = -a;
        invert = !invert;
    }

    if (b < 0) {
        b = -b;
        invert = !invert;
    }

    uint64_t temp = a * b / (1 << DECIMAL_LOC);

    if (invert) return -(int64_t) temp;
    else return temp;
}

static inline int64_t fixed_div(int64_t a, int64_t b) {
    bool invert = false;

    if (a < 0) {
        a = -a;
        invert = !invert;
    }

    if (b < 0) {
        b = -b;
        invert = !invert;
    }

    uint64_t temp = (a * (1 << DECIMAL_LOC)) / b;

    if (invert) return -(int64_t) temp;
    else return temp;
}

static inline void print_fixed(int64_t _num, uint64_t decimals) {
    int64_t num;
    if (_num < 0) {
        print("-");
        num = -_num;
    }
    else {
        num = _num;
    }

    int64_t integer = num >> DECIMAL_LOC;

    print_sdec(integer);
    print(".");

    int64_t mask = 0;
    int64_t exp = 1;
    for (uint64_t i = 0; i < DECIMAL_LOC; i++) {
        mask <<= 1;
        mask |= 1;

        exp *= 10;
    }

    int64_t masked = num & mask;

    int64_t decimal = masked * exp / (1 << DECIMAL_LOC);

    print_dec_extend(decimal, DECIMAL_LOC - 1, decimals);
}
