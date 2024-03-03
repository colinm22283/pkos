#pragma once

#include <driver_table/disc_driver.h>
#include <driver_table/video_driver.h>

typedef struct {
    driver_table_disc_t disc;
    driver_table_video_t video;
} driver_table_t;

extern driver_table_t driver_table;