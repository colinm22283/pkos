#include <console/color_lut.h>

#include <string/strcmp.h>

const char * console_color_str_lut[16] = {
    "BLACK",
    "BLUE",
    "GREEN",
    "CYAN",
    "RED",
    "MAGENTA",
    "BROWN",
    "LGRAY",
    "DGRAY",
    "LBLUE",
    "LGREEN",
    "LCYAN",
    "LRED",
    "LMAGENTA",
    "YELLOW",
    "WHITE",
};

uint8_t console_color_str_lookup(const char * str) {
    for (int i = 0; i < 16; i++) {
        const char * c = console_color_str_lut[i];

        int32_t result = strcmp(str, c);

        if (result == 0) return i;
    }

    return 0xFF;
}