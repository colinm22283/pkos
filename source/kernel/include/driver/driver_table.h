#pragma once

#include "table_entries/disc_driver.h"
#include "table_entries/video_driver.h"

typedef struct {
    driver_table_disc_t disc;
    driver_table_video_t video;
} driver_table_t;

extern driver_table_t driver_table;