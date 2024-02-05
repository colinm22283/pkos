#pragma once

#include <stdint.h>

#include <defs.h>

typedef struct {
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
} __PACKED pdpt64_entry_t;

typedef pdpt64_entry_t __ALIGNED(4096) pdpt64_t[512];

#define PDPT64_SET_ADDRESS(pdpt_entry, _address) do { pdpt_entry.address = ((intptr_t) _address) >> 12; } while (0)
#define NULL_PDPT64_ENTRY ((pdpt64_entry_t) { .present = 0, .read_write = 0, .user_super = 0, .cache_disable = 0, .accessed = 0, ._available2 = 0, ._reserved = 0, ._available1 = 0, .address = 0, ._available0 = 0, .execute_disable = 0, })