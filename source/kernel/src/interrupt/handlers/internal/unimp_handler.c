#include <stdbool.h>
#include <stdint.h>

#include "defs.h"

#include "bios_console.h"

#include "sys/asm/hlt.h"

__SYSV_ABI __INTERRUPT_SUBROUTINE void unimp_handler() {
    print_string("UNIMPLEMENTED HANDLER CALLED\nHANGING...\n");
    while (true) hlt();
}