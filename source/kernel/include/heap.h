#pragma once

#include <stddef.h>

void _heap_init();
void * _heap_alloc(size_t size);
void _heap_free(void * mem);