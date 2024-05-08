#pragma once

#include <defs.h>

#include <driver/table/video_driver.h>

#define MODE_COUNT (1)
#define VIDEO_MEMORY ((uint8_t *) 0xA0000)

typedef struct {
    driver_table_video_mode_t driver_modes[MODE_COUNT];
    uint8_t current_color;
} allocation_t;