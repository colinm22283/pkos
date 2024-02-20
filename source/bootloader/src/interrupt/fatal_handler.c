#include <defs.h>

#include <console/print.h>
#include <console/clear.h>

#include <sys/halt.h>

__NORETURN void int_fatal_handler(void) {
    console_clear_color(CONSOLE_COLOR(CONSOLE_COLOR_WHITE, CONSOLE_COLOR_BLUE));
    console_print("FATAL ERROR ENCOUNTERED\nHALTING\n");

    halt();
}