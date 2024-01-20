#include <stdint.h>

#include <console/console.h>
#include <console/newline.h>

void console_newline(void) {
    console_output_ptr = console_newline_ptr;
    console_newline_ptr += CONSOLE_WIDTH;
}