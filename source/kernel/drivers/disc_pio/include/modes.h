#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <driver/table/video_driver.h>

uint32_t mode_count(void * allocation);
const driver_table_video_mode_t * get_modes(void * allocation);
bool set_mode(void * allocation, uint32_t mode_index);
const driver_table_video_mode_t * get_mode(void * allocation);
bool set_color(void * allocation, const void * color);