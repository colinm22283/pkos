#pragma once

#include <driver/table/driver_table.h>

#include <defs.h>

typedef struct {
    uint64_t (* allocation_size)(void);
    bool (* load)(void * load_address, void * allocation, driver_table_t * driver_table);
} __PACKED driver_vector_table_t;
