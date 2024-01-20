#include <shell/keyboard_handler.h>

#include <console/put.h>

#include <sys/asm/in.h>

void shell_keyboard_handler() {
    char c = (char) inb(0x60);
    console_put('A');
}