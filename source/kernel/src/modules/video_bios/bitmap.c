#include <modules/video_bios/bitmap.h>
#include <modules/video_bios/main.h>

void draw_bitmap(void * _allocation, const void * _bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    allocation_t * allocation = _allocation;
    const uint8_t * bitmap = _bitmap;

    uint8_t color = allocation->current_color;

    uint32_t div_width = w / 8;

    uint32_t video_width = allocation->driver_modes[0].width;

    for (uint32_t _x = 0, __x = 0; _x < w; _x += 8, __x++) {
        for (uint32_t _y = 0; _y < h; _y++) {
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 0)] = (bitmap[_y * div_width + __x] >> 7) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 1)] = (bitmap[_y * div_width + __x] >> 6) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 2)] = (bitmap[_y * div_width + __x] >> 5) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 3)] = (bitmap[_y * div_width + __x] >> 4) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 4)] = (bitmap[_y * div_width + __x] >> 3) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 5)] = (bitmap[_y * div_width + __x] >> 2) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 6)] = (bitmap[_y * div_width + __x] >> 1) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 7)] = (bitmap[_y * div_width + __x] >> 0) & 1 ? color : 0;
        }
    }
}
void draw_bitmap_transparent(void * _allocation, const void * _bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    allocation_t * allocation = _allocation;
    const uint8_t * bitmap = _bitmap;

    uint8_t color = allocation->current_color;

    uint32_t div_width = w / 8;

    uint32_t video_width = allocation->driver_modes[0].width;

    for (uint32_t _x = 0, __x = 0; _x < w; _x += 8, __x++) {
        for (uint32_t _y = 0; _y < h; _y++) {
            if ((bitmap[_y * div_width + __x] >> 7) & 1) VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 0)] = color;
            if ((bitmap[_y * div_width + __x] >> 6) & 1) VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 1)] = color;
            if ((bitmap[_y * div_width + __x] >> 5) & 1) VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 2)] = color;
            if ((bitmap[_y * div_width + __x] >> 4) & 1) VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 3)] = color;
            if ((bitmap[_y * div_width + __x] >> 3) & 1) VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 4)] = color;
            if ((bitmap[_y * div_width + __x] >> 2) & 1) VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 5)] = color;
            if ((bitmap[_y * div_width + __x] >> 1) & 1) VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 6)] = color;
            if ((bitmap[_y * div_width + __x] >> 0) & 1) VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 7)] = color;
        }
    }
}