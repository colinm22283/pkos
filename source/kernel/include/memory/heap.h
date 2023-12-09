#pragma once

#include <stddef.h>
#include <stdint.h>

#include <defs.h>

__STDCALL void heap_init(void);
__STDCALL void * heap_alloc(uint32_t size);
__STDCALL int heap_free(void * mem);