#include <console/print.h>
#include <console/console.h>
#include <console/newline.h>
#include <console/update.h>

#include <shell/blinker.h>

void console_print(const char * string) {
    clear_blinker();

    for (unsigned int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '\n') {
            console_newline();
        }
        else {
            console_buffer[CONSOLE_HEIGHT - 1][console_position].ch = string[i];
            console_position++;
        }
    }

    console_update();

    update_blinker();
}