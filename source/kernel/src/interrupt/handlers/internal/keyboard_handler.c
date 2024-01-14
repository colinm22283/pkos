#include <stdint.h>
#include <stdbool.h>

#include "defs.h"

#include "bios_console.h"

#include "sys/asm/in.h"
#include "sys/asm/out.h"
#include "sys/ports.h"

__SYSV_ABI __INTERRUPT_SUBROUTINE void keyboard_handler() {
    uint8_t c = inb(PORT_KB_IN);
    outb(PORT_KB_OUT, c | 0x80);
    outb(PORT_KB_OUT, c);

    print_string("Got KB: ");
    print_char((char) c);
    print_char('\n');

    outb(PORT_PIC1_COMMAND, 0x20);
}