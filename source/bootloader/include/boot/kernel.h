#pragma once

#include <defs.h>

#define KERNEL_LBA_START    (64)
#define KERNEL_SECTORS      (128)

__NORETURN void kernel_entry(void);