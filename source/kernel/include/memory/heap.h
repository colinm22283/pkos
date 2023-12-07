#pragma once

#include <stddef.h>
#include <stdint.h>

void heap_init();
void * heap_alloc(uint32_t size);
int heap_free(void * mem);