#include <shell/keyboard_handler.h>

#include <sys/asm/out.h>
#include <sys/ports.h>

void int_keyboard_handler() {
    shell_keyboard_handler();

    outb(PORT_PIC1_COMMAND, 0x20);
}