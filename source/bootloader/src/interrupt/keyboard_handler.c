#include <stdbool.h>

#include <interrupt/keyboard_lut.h>

#include <shell/keyboard_handler.h>

#include <sys/asm/out.h>
#include <sys/asm/in.h>
#include <sys/ports.h>

void int_keyboard_handler() {
    unsigned char raw_char = (unsigned char) inb(0x60);

    bool released = raw_char >= 0x80;

    if (released) raw_char -= 0x80;

    char ascii_char = keyboard_lut[raw_char];

    if (ascii_char == 9) {

    }
    else {
        if (!released) shell_keyboard_key_down_handler(ascii_char);
    }

    outb(PORT_PIC1_COMMAND, 0x20);
}