#include <modules/video_bios/pixel.h>
#include <modules/video_bios/main.h>

void draw_pixel(void * _allocation, uint32_t x, uint32_t y) {
    allocation_t * allocation = _allocation;

    VIDEO_MEMORY[y * allocation->driver_modes[0].width + x] = allocation->current_color;
}