#pragma once

#include <driver/table/driver_table.h>

extern driver_table_t driver_table;

#define VIDEO_ALLOC (driver_table.video.allocation)

static inline uint32_t driver_video_mode_count() { return driver_table.video.mode_count(driver_table.video.allocation); }
static inline const driver_table_video_mode_t * driver_video_get_modes() { return driver_table.video.get_modes(driver_table.video.allocation); }
static inline bool driver_video_set_mode(uint32_t mode_index) { return driver_table.video.set_mode(driver_table.video.allocation, mode_index); }
static inline const driver_table_video_mode_t * driver_video_get_mode() { return driver_table.video.get_mode(driver_table.video.allocation); }

static inline bool driver_video_set_color(const void * color) { return driver_table.video.set_color(VIDEO_ALLOC, color); }
static inline void driver_video_draw_pixel(uint32_t x, uint32_t y) { return driver_table.video.draw_pixel(VIDEO_ALLOC, x, y); }
static inline void driver_video_draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h) { return driver_table.video.draw_rect(VIDEO_ALLOC, x, y, w, h); }
static inline void driver_video_fill_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h) { return driver_table.video.fill_rect(VIDEO_ALLOC, x, y, w, h); }
static inline void driver_video_draw_image(const void * image, uint32_t x, uint32_t y, uint32_t w, uint32_t h) { return driver_table.video.draw_image(VIDEO_ALLOC, image, x, y, w, h); }
static inline void driver_video_draw_bitmap(const void * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h) { return driver_table.video.draw_bitmap(VIDEO_ALLOC, bitmap, x, y, w, h); }
static inline void driver_video_draw_bitmap_transparent(const void * bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h) { return driver_table.video.draw_bitmap_transparent(VIDEO_ALLOC, bitmap, x, y, w, h); }

#define DISC_ALLOC (driver_table.disc.allocation)