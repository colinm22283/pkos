#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    bool (* start)(void);
    bool (* stop)(void);

    uint16_t (* device_count)(void);
    bool (* select_device)(uint16_t);
    const char * (* get_error_string)(void);

    bool (* read)(uint32_t lba, uint16_t sector_count, void * dest);
} driver_table_disc_t;