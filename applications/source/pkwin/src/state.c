#include <stdlib.h>

#include <state.h>

lock_t window_lock = LOCK_INIT;

size_t window_count;
window_t ** windows;

window_t * held_window = NULL;
window_t * focus_window = NULL;

void state_init(void) {
    window_count = 0;
    windows = malloc(1);
}

