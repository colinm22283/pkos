#pragma once

#include <stdint.h>

#include <pkos.h>
#include <error_number.h>

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

static inline void print_dec(uint64_t num) {
    char data[21];

    uint64_t start = 20;

    for (int i = 20; i >= 0; i--) {
        uint64_t val = num % 10;

        char c = (char) ('0' + val);

        if (c != '0') start = i;

        data[i] = c;
        num /= 10;
    }

    data[21] = '\0';

    print(data + start);
}

static inline void print_sdec(int64_t _num) {
    uint64_t num;
    if (_num < 0) {
        print("-");
        num = -_num;
    }
    else {
        num = _num;
    }

    char data[21];

    uint64_t start = 20;

    for (int i = 20; i >= 0; i--) {
        uint64_t val = num % 10;

        char c = (char) ('0' + val);

        if (c != '0') start = i;

        data[i] = c;
        num /= 10;
    }

    data[21] = '\0';

    print(data + start);
}

static inline void print_dec_extend(uint64_t num, uint64_t size, uint64_t decimals) {
    char data[22];

    if (num == 0) {
        print("0");
        return;
    }

    uint64_t start = 20 - size;

    for (int i = 20; i >= 0; i--) {
        uint64_t val = num % 10;

        char c = (char) ('0' + val);

        data[i] = c;
        num /= 10;
    }

    data[start + decimals] = '\0';

    print(data + start);
}

static inline void print_hex(uint64_t num) {
    char data[17];

    for (int i = 15; i >= 0; i--) {
        uint64_t val = num % 16;

        char c;
        if (val < 10) c = (char) ('0' + val);
        else c = (char) ('A' + val - 10);

        data[i] = c;
        num /= 16;
    }

    data[16] = '\0';

    print(data);
}
