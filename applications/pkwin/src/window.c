#include <stddef.h>

#include <window.h>

window_t * windows[MAX_WINDOWS];

void windows_init(void) {
    for (size_t i = 0; i < MAX_WINDOWS; i++) {
        windows[i] = NULL;
    }
}

window_t * windows_add(char title[100]) {
    return NULL;
}

void windows_draw(void) {

}
