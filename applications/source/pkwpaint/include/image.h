#pragma once

#include <stdint.h>

typedef struct {
    int w, h;
    uint8_t pixels[640 * 480];
} image_t;

