#pragma once

#include <window.h>
#include <lock.h>

extern lock_t window_lock;

extern size_t window_count;
extern window_t ** windows;

extern window_t * held_window;

void state_init(void);

