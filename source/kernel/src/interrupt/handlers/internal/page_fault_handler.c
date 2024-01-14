#include <stdint.h>
#include <stdbool.h>

#include "defs.h"

#include "bios_console.h"

#include "sys/asm/hlt.h"

__SYSV_ABI __INTERRUPT_SUBROUTINE void page_fault_handler() {
    print_string("PAGE FAULT\nHANGING...\n");
    while (true) hlt();
}