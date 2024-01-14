#include <stdbool.h>
#include <stdint.h>

#include "defs.h"

#include "sys/asm/hlt.h"

#include "interrupt/interrupts.h"

#include "interrupt/system/print.h"

#include "memory/heap.h"

__SYSV_ABI __INTERRUPT_SUBROUTINE uint64_t system_interrupt_handler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx) {
    switch (rdi) {
        case 0:
            sysint_print((char *) rsi);
            return 0;

        case 1:
            return (uint64_t) NULL;
            //return (uint64_t) sys_heap_alloc((uint32_t) rsi);

        case 2:
            return (uint64_t) NULL;
            //return (uint64_t) sys_heap_free((void *) rsi);

        default:
            return 0;
    }
}