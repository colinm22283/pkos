#include <driver/video_bios.h>

#define MODE_COUNT (1)
const driver_table_video_mode_t driver_modes[MODE_COUNT] = {
    {
        .width = 320,
        .height = 200,
        .color_mode = DRIVER_TABLE_VIDEO_MODE_COLOR_MODE_256_COLOR,
    },
};

uint8_t current_color = 0;
static uint8_t * const video_memory = (uint8_t *) 0xA0000;

uint32_t mode_count() {
    return MODE_COUNT;
}
const driver_table_video_mode_t * get_modes() {
    return driver_modes;
}
bool set_mode(uint32_t mode_index) {
    if (mode_index >= MODE_COUNT) return false;

    return true;
}
const driver_table_video_mode_t * get_mode() {
    return &driver_modes[0];
}

bool set_color(void * color) {
    current_color = *(uint8_t *) color;

    return true;
}
void draw_pixel(uint32_t x, uint32_t y) {
    video_memory[y * driver_modes[0].width + x] = current_color;
}
void draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    uint8_t * top_memory = video_memory + x + (y * driver_modes[0].width);
    uint8_t * bottom_memory = video_memory + x + (y * driver_modes[0].width) + ((h - 1) * driver_modes[0].width);
    uint8_t * left_memory = video_memory + x + ((y + 1) * driver_modes[0].width);
    uint8_t * right_memory = video_memory + x + ((y + 1) * driver_modes[0].width) + w - 1;

    for (uint32_t i = 0; i < w; i++) {
        *top_memory = current_color;
        *bottom_memory = current_color;
        top_memory++;
        bottom_memory++;
    }
    for (uint32_t i = 2; i < h; i++) {
        *left_memory = current_color;
        *right_memory = current_color;
        left_memory += driver_modes[0].width;
        right_memory += driver_modes[0].width;
    }
}
void fill_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    uint8_t * video_ptr = video_memory + x + (y * driver_modes[0].width);
    for (uint32_t _y = 0; _y < h; _y++) {
        for (uint32_t _x = 0; _x < w; _x++) {
            *(video_ptr++) = current_color;
        }
        video_ptr += driver_modes[0].width - w;
    }
}
void draw_image(const void * _image, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    const uint8_t * image = _image;
    for (uint32_t _x = 0; _x < w; _x++) {
        for (uint32_t _y = 0; _y < h; _y++) {
            video_memory[(y + _y) * driver_modes[0].width + (x + _x)] = image[_y * w + _x];
        }
    }
}
void draw_bitmap(const uint8_t * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    uint8_t color = current_color;

    uint32_t div_width = w >> 3;

    for (uint32_t _x = 0, __x = 0; _x < w; _x += 8, __x++) {
        for (uint32_t _y = 0; _y < h; _y++) {
            video_memory[(y + _y) * driver_modes[0].width + (x + _x + 0)] = (bitmap[_y * div_width + __x] >> 7) & 1 ? color : 0;
            video_memory[(y + _y) * driver_modes[0].width + (x + _x + 1)] = (bitmap[_y * div_width + __x] >> 6) & 1 ? color : 0;
            video_memory[(y + _y) * driver_modes[0].width + (x + _x + 2)] = (bitmap[_y * div_width + __x] >> 5) & 1 ? color : 0;
            video_memory[(y + _y) * driver_modes[0].width + (x + _x + 3)] = (bitmap[_y * div_width + __x] >> 4) & 1 ? color : 0;
            video_memory[(y + _y) * driver_modes[0].width + (x + _x + 4)] = (bitmap[_y * div_width + __x] >> 3) & 1 ? color : 0;
            video_memory[(y + _y) * driver_modes[0].width + (x + _x + 5)] = (bitmap[_y * div_width + __x] >> 2) & 1 ? color : 0;
            video_memory[(y + _y) * driver_modes[0].width + (x + _x + 6)] = (bitmap[_y * div_width + __x] >> 1) & 1 ? color : 0;
            video_memory[(y + _y) * driver_modes[0].width + (x + _x + 7)] = (bitmap[_y * div_width + __x] >> 0) & 1 ? color : 0;
        }
    }
}
void draw_bitmap_transparent(const uint8_t * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    uint8_t color = current_color;

    uint32_t div_width = w >> 3;

    for (uint32_t _x = 0, __x = 0; _x < w; _x += 8, __x++) {
        for (uint32_t _y = 0; _y < h; _y++) {
            if ((bitmap[_y * div_width + __x] >> 7) & 1) video_memory[(y + _y) * driver_modes[0].width + (x + _x + 0)] = color;
            if ((bitmap[_y * div_width + __x] >> 6) & 1) video_memory[(y + _y) * driver_modes[0].width + (x + _x + 1)] = color;
            if ((bitmap[_y * div_width + __x] >> 5) & 1) video_memory[(y + _y) * driver_modes[0].width + (x + _x + 2)] = color;
            if ((bitmap[_y * div_width + __x] >> 4) & 1) video_memory[(y + _y) * driver_modes[0].width + (x + _x + 3)] = color;
            if ((bitmap[_y * div_width + __x] >> 3) & 1) video_memory[(y + _y) * driver_modes[0].width + (x + _x + 4)] = color;
            if ((bitmap[_y * div_width + __x] >> 2) & 1) video_memory[(y + _y) * driver_modes[0].width + (x + _x + 5)] = color;
            if ((bitmap[_y * div_width + __x] >> 1) & 1) video_memory[(y + _y) * driver_modes[0].width + (x + _x + 6)] = color;
            if ((bitmap[_y * div_width + __x] >> 0) & 1) video_memory[(y + _y) * driver_modes[0].width + (x + _x + 7)] = color;
        }
    }
}

bool video_bios_start() { return true; }
bool video_bios_stop() { return true; }

void driver_video_bios_load(driver_table_t * dt) {
    dt->video.start = video_bios_start;
    dt->video.stop  = video_bios_stop;

    dt->video.mode_count = mode_count;
    dt->video.get_modes  = get_modes;
    dt->video.set_mode   = set_mode;
    dt->video.get_mode   = get_mode;

    dt->video.set_color               = set_color;
    dt->video.draw_pixel              = draw_pixel;
    dt->video.draw_rect               = draw_rect;
    dt->video.fill_rect               = fill_rect;
    dt->video.draw_image              = draw_image;
    dt->video.draw_bitmap             = draw_bitmap;
    dt->video.draw_bitmap_transparent = draw_bitmap_transparent;
}