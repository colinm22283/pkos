#pragma once

#include <stdint.h>

typedef struct {
    int w, h;
    uint8_t pixels[191 * 62];
} image_t;

