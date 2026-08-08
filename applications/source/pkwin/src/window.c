#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <state.h>
#include <window.h>
#include <config.h>
#include <font.h>

window_t * window_init(const char * name, int w, int h) {
    window_t * window = malloc(sizeof(window_t));

    window->title = malloc(strlen(name) + 1);
    strcpy(window->title, name);

    window->x = 10;
    window->y = 10;

    window->w = w;
    window->h = h;
    window->fb = malloc(window->w * window->h);

    for (int i = 0; i < window->w * window->h; i++) window->fb[i] = 20;

    return window;
}

void window_free(window_t * window) {
    free(window->fb);
    free(window);
}

void window_click(window_t * window, int x, int y) {
    int rx = x - window->x;
    int ry = y - window->y;

    if (rx >= 0 && rx < window->w && ry >= 0 && window->h) printf("CLICKED\n");
    else if (rx >= 0 && rx < window->w && ry >= -bar_height && ry < 0) {
        held_window = window;
    }
}

void window_draw_char(window_t * window, char c, int ix, int iy) {
    int ox = ((c - 32) % 32) * 6;
    int oy = ((c - 32) / 32) * 9;

    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 8; y++) {
            int sx = ix + x;
            int sy = iy + y;

            if (sx < 0 || sx >= window->w || sy < 0 || sy >= window->h) continue;

            if (font.pixels[(oy + y) * font.w + (ox + x)] != 16) {
                window->fb[sy * window->w + sx] = 16;
            }
        }
    }
}

void window_resize(window_t * window, int w, int h) {
    window->w = w;
    window->h = h;
    window->fb = realloc(window->fb, w * h);
}

