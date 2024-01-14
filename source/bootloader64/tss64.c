#include <sys/tss/tss64.h>

#include <defs.h>

__SECTION(".bootloader64_tss") tss64_t tss64 = {
    .rsp0 = 0xFFFFFFFF,
    .iopb = 0xF,
};