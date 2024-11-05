#pragma once

#include <stddef.h>

extern char _allocation_space_start;
extern char _allocation_space_end;
extern char _allocation_space_size;

#define ALLOCATION_SPACE_START ((void *) &_allocation_space_start)
#define ALLOCATION_SPACE_SIZE  ((size_t) &_allocation_space_size)
