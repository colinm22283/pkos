#pragma once

#include <defs.h>

#include <console/print.h>

#include <sys/halt.h>

__NORETURN void int_fatal_handler(void) {
    console_print_color("FATAL ERROR ENCOUNTERED\nHALTING\n", CONSOLE_COLOR(CONSOLE_COLOR_RED, CONSOLE_COLOR_BLACK));

    halt();
}