#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <pkldef.h>

__extern__ void _pkl_heap_init();
__extern__ void * _pkl_heap_alloc(size_t size);
__extern__ void _pkl_heap_free(void * memory);