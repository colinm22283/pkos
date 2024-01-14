#include <stdint.h>
#include <stdbool.h>

#include "defs.h"

#include "bios_console.h"

#include "sys/ports.h"

#include "sys/asm/out.h"

__SYSV_ABI __INTERRUPT_SUBROUTINE void null_pic1_handler() {
    print_string("NULL PIC1 HANDLER CALLED\n");

    outb(PORT_PIC1_COMMAND, 0x20);
}

__SYSV_ABI __INTERRUPT_SUBROUTINE void null_pic2_handler() {
    print_string("NULL PIC2 HANDLER CALLED\n");

    outb(PORT_PIC1_COMMAND, 0x20);
    outb(PORT_PIC2_COMMAND, 0x20);
}