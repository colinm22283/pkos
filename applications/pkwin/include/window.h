#pragma once

#include <stdint.h>

#include <display.h>

#define TITLE_MAX (100)

#define MAX_WINDOWS (1024)

typedef struct {
    uint32_t x, y;

    char title[TITLE_MAX];
} window_t;

static inline window_t * get_window(size_t index) {
    extern window_t * windows[MAX_WINDOWS];

    if (index == 0) return NULL;
    else return windows[index - 1];
}

void windows_init(void);

window_t * windows_add(char title[TITLE_MAX]);

void windows_draw(display_t * display);
