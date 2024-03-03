#pragma once

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
    bool (* start)(void);
    bool (* stop)(void);

    uint32_t (* mode_count)(void);
    driver_table_video_mode_t * (* get_modes)(void);
    bool (* set_mode)(uint32_t mode_index);
    driver_table_video_mode_t * (* get_mode)(void);

    bool (* set_color)(void * color);
    void (* draw_pixel)(uint32_t x, uint32_t y);
    void (* draw_image)(const void * image, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    void (* draw_bitmap)(const uint8_t * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
    void (* draw_bitmap_transparent)(const uint8_t * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
} driver_table_video_t;