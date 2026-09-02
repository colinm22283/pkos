#pragma once

#include <stdint.h>

typedef struct {
    char * title;

    int id;
    int sock_fd;

    int x, y, w, h;

    uint8_t * fb;
} window_t;

window_t * window_init(const char * name, int w, int h, int sock_fd, int id);
void window_free(window_t * window);

void window_click(window_t * window, int x, int y);
void window_press(window_t * window, uint16_t code);

void window_draw_char(window_t * window, char c, int ix, int iy);

void window_resize(window_t * window, int w, int h);

