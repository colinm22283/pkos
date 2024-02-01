#include <commands/clear.h>

#include <console/print.h>
#include <console/clear.h>
#include <console/color_lut.h>

__CDECL uint32_t command_clear(uint32_t argc, const char ** argv) {
    uint8_t fg_color = CONSOLE_COLOR_WHITE, bg_color = CONSOLE_COLOR_BLACK;

    if (argc > 3) {
        console_print("Too many arguments. (max: 2)");
        return 1;
    }

    if (argc == 3) {
        bg_color = console_color_str_lookup(argv[2]);

        if (bg_color == 0xFF) return 2;
    }

    if (argc >= 2) {
        fg_color = console_color_str_lookup(argv[1]);

        if (fg_color == 0xFF) return 3;
    }

    console_clear_color(CONSOLE_COLOR(fg_color, bg_color));

    return 0;
}