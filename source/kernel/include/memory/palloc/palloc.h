#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct palloc_tag_s {
    struct palloc_tag_s * prev;
    struct palloc_tag_s * next;
    uint8_t allocated;
} palloc_tag_t;

extern palloc_tag_t * palloc_head_tag;
extern palloc_tag_t * palloc_tail_tag;

void palloc_init();
