#include <display.h>

void display_init(display_t * display, const char * fb_path, size_t width, size_t height) {
    display->fb_fd = open(fb_path, OPEN_READ | OPEN_WRITE);
    display->fb = map(display->fb_fd, NULL, width * height, 0, MAP_WRITE);

    display->width = width;
    display->height = height;
}

void display_free(display_t * display) {
    close(display->fb_fd);
}

void display_draw(display_t * display) {
    uint8_t * fb = (uint8_t *) display->fb;

    for (size_t i = 0; i < display->width * display->height; i++) {
        fb[i] = 0x3;
    }
}
