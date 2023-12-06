#pragma once

#include <stddef.h>

void _heap_init();
void * _heap_alloc(uint32_t size);
int _heap_free(void * mem);