#include <stdint.h>

#include <console/console.h>
#include <console/newline.h>
#include <console/clear.h>
#include <console/print.h>

#include <shell/blinker.h>

#include <keyboard/getch.h>

#include <sys/asm/hlt.h>

void console_newline(void) {
    clear_blinker();

    console_output_ptr = console_newline_ptr;
    console_newline_ptr += CONSOLE_WIDTH;

    if (console_output_ptr >= CONSOLE_BASE_POINTER + CONSOLE_WIDTH * CONSOLE_HEIGHT - CONSOLE_WIDTH) {
        console_print("Press any key for next page...");

        keyboard_getch();

        console_output_ptr = CONSOLE_BASE_POINTER;
        console_newline_ptr = CONSOLE_BASE_POINTER + CONSOLE_WIDTH;
        console_clear();
    }

    update_blinker();
}