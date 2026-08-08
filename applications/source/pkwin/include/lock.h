#pragma once

#include <stdatomic.h>

#define LOCK_INIT ATOMIC_FLAG_INIT

typedef atomic_flag lock_t;

static inline void acquire(lock_t * lock) {
    while (atomic_flag_test_and_set_explicit(lock, memory_order_acquire)) {
        __builtin_ia32_pause();
    }
}

static inline void release(lock_t * lock) {
    atomic_flag_clear_explicit(lock, memory_order_release);
}

