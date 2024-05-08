#pragma once

#include "../../../../../../../../../opt/cross64/lib/gcc/x86_64-elf/14.0.1/include/stdint.h"
#include "../../../../../../../../../opt/cross64/lib/gcc/x86_64-elf/14.0.1/include/stdbool.h"

typedef struct {
    void * allocation;

    bool (* start)(void);
    bool (* stop)(void);

    uint16_t (* device_count)(void);
    bool (* select_device)(uint16_t);
    const char * (* get_error_string)(void);

    bool (* read)(uint32_t lba, uint16_t sector_count, void * dst);
    bool (* write)(uint32_t lba, uint16_t sector_count, void * src);
} driver_table_disc_t;