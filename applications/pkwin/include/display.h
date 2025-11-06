#pragma once

#include <stddef.h>

#include <pkos.h>

typedef struct {
    fd_t fb_fd;
    void * fb;

    size_t width, height;
} display_t;

void display_init(display_t * display, const char * fb_path, size_t width, size_t height);
void display_free(display_t * display);

void display_draw(display_t * display);
