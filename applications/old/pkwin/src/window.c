#include <stddef.h>

#include <window.h>
#include <heap.h>

window_t * windows[MAX_WINDOWS];

void windows_init(void) {
    for (size_t i = 0; i < MAX_WINDOWS; i++) {
        windows[i] = NULL;
    }
}

window_t * windows_add(char title[TITLE_MAX]) {
    window_t * window = NULL;
    for (size_t i = 0; i < MAX_WINDOWS; i++) {
        if (windows[i] == NULL) window = windows[i] = heap_alloc(sizeof(window_t));
    }
    if (window == NULL) return NULL;

    window->x = ((uint64_t) window) % 100;
    window->y = ((uint64_t) window / 1000) % 100;

    for (size_t i = 0; i < 100; i++) {
        window->title[i] = title[i];

        if (title[i] == '\0') break;
    }

    return NULL;
}

void windows_draw(display_t * display) {
    for (size_t i = 0; i < MAX_WINDOWS; i++) {
        window_t * window = windows[i];

        if (window != NULL) {
            write(stdout, "window\n", 7);

            for (size_t x = 0; x < 30; x++) {
                for (size_t y = 0; y < 30; y++) {
                    ((uint8_t *) display->fb)[y * display->width + x] = 0x4;
                }
            }
        }
    }
}
