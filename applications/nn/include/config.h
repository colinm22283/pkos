#pragma once

#include <fixed.h>

extern int64_t learning_rate;

static inline void config_init(void) {
    learning_rate = to_fixed(1) / 10;
}
