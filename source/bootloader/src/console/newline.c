#include <stdint.h>

#include <console/console.h>
#include <console/newline.h>
#include <console/clear.h>

void console_newline(void) {
    console_output_ptr = console_newline_ptr;
    console_newline_ptr += CONSOLE_WIDTH;

    if (console_output_ptr >= CONSOLE_BASE_POINTER + CONSOLE_WIDTH * CONSOLE_HEIGHT) {
        console_output_ptr = CONSOLE_BASE_POINTER;
        console_newline_ptr = CONSOLE_BASE_POINTER + CONSOLE_WIDTH;
        console_clear();
    }
}