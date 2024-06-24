#include <modules/video_bios/image.h>
#include <modules/video_bios/main.h>

void draw_image(void * _allocaton, const void * _image, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    allocation_t * allocation = _allocaton;

    uint32_t video_width = allocation->driver_modes[0].width;

    const uint8_t * image = _image;
    for (uint32_t _x = 0; _x < w; _x++) {
        for (uint32_t _y = 0; _y < h; _y++) {
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x)] = image[_y * w + _x];
        }
    }
}