#pragma once

#include <stdint.h>

#include <defs.h>

#include <sys/paging/pt.h>

typedef struct {
    uint8_t  present         :  1;
    uint8_t  read_write      :  1;
    uint8_t  user_super      :  1;
    uint8_t  write_through   :  1;
    uint8_t  cache_disable   :  1;
    uint8_t  accessed        :  1;
    uint8_t  _available2     :  1;
    uint8_t  _reserved       :  1;
    uint8_t  _available1     :  4;
    uint64_t address         : 40;
    uint16_t _available0     : 11;
    uint8_t  execute_disable :  1;
} __PACKED pdt64_entry_t;

typedef pdt64_entry_t __ALIGNED(4096) pdt64_t[512];

#define PDT64_SET_ADDRESS(pdt_entry, _address) do { pdt_entry.address = ((intptr_t) _address) >> 12; } while (0)
#define PDT64_GET_ADDRESS(pdt_entry) ((pt64_t *)(((intptr_t) (pdt_entry).address) << 12))
#define NULL_PDT64_ENTRY ((pdt64_entry_t) { .present = 0, .read_write = 0, .user_super = 0, .cache_disable = 0, .accessed = 0, ._available2 = 0, ._reserved = 0, ._available1 = 0, .address = 0, ._available0 = 0, .execute_disable = 0, })

static inline pdt64_entry_t * pdt64_map_address(pdt64_t * pdt, pt64_t * pt, uint64_t virtual_address) {
    PDT64_SET_ADDRESS((*pdt)[virtual_address % 0x40000000 / 0x200000], pt);
    return &(*pdt)[virtual_address % 0x40000000 / 0x200000];
}
