#pragma once

#include <stdint.h>

void draw_bitmap(void * allocation, const void * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void draw_bitmap_transparent(void * allocation, const void * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h);