#pragma once

#include <stdint.h>

#include <defs.h>

typedef struct {
    uint8_t  execute_disable :  1;
    uint8_t  protection_key  :  4;
    uint16_t available0      :  7;
    uint64_t address12       : 40;
    uint8_t  available1      :  4;
    uint8_t  page_size       :  1;
    uint8_t  available2      :  1;
    uint8_t  accessed        :  1;
    uint8_t  cache_disabled  :  1;
    uint8_t  write_through   :  1;
    uint8_t  user_supervisor :  1;
    uint8_t  read_write      :  1;
    uint8_t  present         :  1;
} __PACKED pt64_entry_t;

typedef pt64_entry_t __ALIGNED(4096) pt64_t[512];