#pragma once

#include <stdbool.h>

enum {
    DRIVER_TABLE_VIDEO_MODE_COLOR_MODE_MONO,
    DRIVER_TABLE_VIDEO_MODE_COLOR_MODE_2_COLOR,
    DRIVER_TABLE_VIDEO_MODE_COLOR_MODE_4_COLOR,
    DRIVER_TABLE_VIDEO_MODE_COLOR_MODE_16_COLOR,
    DRIVER_TABLE_VIDEO_MODE_COLOR_MODE_256_COLOR,
};

typedef struct {
    uint32_t width, height;
    uint16_t color_mode;
} driver_table_video_mode_t;

typedef struct {
    void * allocation;

    bool (* unload)(void * _allocation, void * driver_table);

    uint32_t (* mode_count)(void * allocation);
    const driver_table_video_mode_t * (* get_modes)(void * allocation);
    bool (* set_mode)(void * allocation, uint32_t mode_index);
    const driver_table_video_mode_t * (* get_mode)(void * allocation);

    bool (* set_color)(void * allocation, const void * color);
    void (* draw_pixel)(void * allocation, uint32_t x, uint32_t y);
    void (* draw_rect)(void * allocation, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    void (* fill_rect)(void * allocation, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    void (* draw_image)(void * allocation, const void * image, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    void (* draw_bitmap)(void * allocation, const void * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    void (* draw_bitmap_transparent)(void * allocation, const void * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
} driver_table_video_t;