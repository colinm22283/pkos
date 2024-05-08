#pragma once

#include "disc_driver.h"
#include "video_driver.h"

typedef struct {
    driver_table_disc_t disc;
    driver_table_video_t video;
} driver_table_t;