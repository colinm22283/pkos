#pragma once

#include <stdint.h>

#include <defs.h>

typedef struct __PACKED {
    uint8_t  execute_disable :  1;
    uint16_t _available0     : 11;
    uint64_t address         : 40;
    uint8_t  _available1     :  4;
    uint8_t  _reserved       :  1;
    uint8_t  _available2     :  1;
    uint8_t  accessed        :  1;
    uint8_t  cache_disable   :  1;
    uint8_t  write_through   :  1;
    uint8_t  user_super      :  1;
    uint8_t  read_write      :  1;
    uint8_t  present         :  1;
} pml4t_entry_t;

typedef __ALIGNED(0x1000) pml4t_entry_t pml4t_t[512];