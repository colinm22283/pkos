#include <console/console.h>
#include <console/put.h>
#include <console/update.h>

#include <shell/blinker.h>

void console_put(char c) {
    clear_blinker();

    console_buffer[CONSOLE_HEIGHT - 1][console_position].ch = c;
    console_position++;

    update_blinker();

    console_update();
}