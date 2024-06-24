#pragma once

#include <stdbool.h>

typedef struct {
    bool (* init)(void * allocation_root);
    bool (* free)(void);
} module_entry_table_t;