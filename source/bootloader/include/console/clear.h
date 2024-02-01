#pragma once

#include <console/color.h>

__CDECL void console_clear_color(console_color_t color);

static inline void console_clear(void) {
    console_clear_color(CONSOLE_COLOR(CONSOLE_COLOR_WHITE, CONSOLE_COLOR_BLACK));
}