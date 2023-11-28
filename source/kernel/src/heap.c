#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <heap.h>

extern struct _heap_limit_s _heap_base;
extern struct _heap_limit_s  _heap_top;

typedef struct {
    bool reserved;
    size_t block_size;
    size_t prev_size;
} heap_tag_t;

void _heap_init() {
}

void * _heap_alloc(size_t size) {
}

void _heap_free(void * mem) {
}