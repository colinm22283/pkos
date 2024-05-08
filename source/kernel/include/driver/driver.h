#pragma once

#include <stdbool.h>

typedef struct {

} driver_handle_t;

bool load_driver(driver_handle_t * handle, const char * path);