#include <console/print_hex.h>
#include <console/update.h>
#include <console/put.h>
#include <console/console.h>

#include <shell/blinker.h>

char hex_lut[16] = "0123456789ABCDEF";

void console_print_hex(uint32_t num) {
    clear_blinker();

    if (num == 0) {
        console_put('0');
    }
    else {
        char num_buf[8];

        uint8_t i;
        for (i = 0; num != 0; i++) {
            num_buf[i] = hex_lut[num % 16];

            num /= 16;
        }

        while (i > 1 && num_buf[i - 1] == '0') {
            i--;
        }

        do {
            i--;

            console_buffer[CONSOLE_HEIGHT - 1][console_position].ch = num_buf[i];
            console_position++;
        } while (i > 0);
    }

    update_blinker();

    console_update();
}