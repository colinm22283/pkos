#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "defs.h"

__SYSV_ABI void sys_heap_init(uint64_t size);
[[nodiscard]] __SYSV_ABI void * sys_heap_alloc(uint64_t size);
__SYSV_ABI bool sys_heap_free(void * mem);