#include <modules/video_bios/rect.h>

#include <modules/video_bios/main.h>

#include <sys/asm/hlt.h>

void draw_rect(void * _allocation, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    allocation_t * allocation = _allocation;

    uint8_t * top_memory = VIDEO_MEMORY + x + (y * allocation->driver_modes[0].width);
    uint8_t * bottom_memory = VIDEO_MEMORY + x + (y * allocation->driver_modes[0].width) + ((h - 1) * allocation->driver_modes[0].width);
    uint8_t * left_memory = VIDEO_MEMORY + x + ((y + 1) * allocation->driver_modes[0].width);
    uint8_t * right_memory = VIDEO_MEMORY + x + ((y + 1) * allocation->driver_modes[0].width) + w - 1;

    for (uint32_t i = 0; i < w; i++) {
        *top_memory = allocation->current_color;
        *bottom_memory = allocation->current_color;
        top_memory++;
        bottom_memory++;
    }
    for (uint32_t i = 2; i < h; i++) {
        *left_memory = allocation->current_color;
        *right_memory = allocation->current_color;
        left_memory += allocation->driver_modes[0].width;
        right_memory += allocation->driver_modes[0].width;
    }
}

void fill_rect(void * _allocation, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    allocation_t * allocation = _allocation;

    uint8_t * video_ptr = VIDEO_MEMORY + x + (y * allocation->driver_modes[0].width);

    for (uint32_t _y = 0; _y < h; _y++) {
        for (uint32_t _x = 0; _x < w; _x++) {
            *(video_ptr++) = allocation->current_color;
        }
        video_ptr += allocation->driver_modes[0].width - w;
    }
}