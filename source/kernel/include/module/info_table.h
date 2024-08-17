#pragma once

#include <stdbool.h>
#include <stdint.h>

#define DEFINE_MODULE_INFO_TABLE(_name)                          \
    __SECTION(".entry_table") module_info_table_t info_table = { \
        .init = init,                                            \
        .free = free,                                            \
        .name = _name                                            \
    }

#define MODULE_NAME_MAX_LENGTH (256)

typedef struct module_info_table_s {
    bool (* init)(struct module_info_table_s * info_table);
    bool (* free)(struct module_info_table_s * info_table);
    void * module_data;
    char name[MODULE_NAME_MAX_LENGTH];
} module_info_table_t;