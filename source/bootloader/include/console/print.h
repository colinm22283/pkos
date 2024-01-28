#pragma once

#include <stdint.h>

#include <defs.h>

#include <console/color.h>

__CDECL void console_print(const char * string);
__CDECL void console_print_color(const char * string, console_color_t color);