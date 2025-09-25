#pragma once

#include <stdint.h>
#include <stdbool.h>

#define HEAP_INITIAL_SIZE (0x10000)

typedef struct {
    bool next_reserved;
    uint64_t prev_size;
    uint64_t next_size;
} heap_tag_t;

extern uint64_t alloc_size;

extern char heap_data[HEAP_INITIAL_SIZE];

extern heap_tag_t * head_tag;
extern heap_tag_t * tail_tag;

void heap_init(void);

void * heap_alloc(uint64_t size_bytes);
void heap_free(void * alloc);
void * heap_realloc(void * alloc, uint64_t size_bytes);