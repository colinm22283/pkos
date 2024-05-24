#include <stdbool.h>

#include <console/console.h>

#include <shell/input.h>

bool blinker = false;
console_char_t * last_location;

void clear_blinker() {
    if (!blinker) {
        last_location->ch = ' ';
        blinker = true;
    }
}

void update_blinker() {
    if (!shell_ready_to_execute) {
        if (blinker) {
            last_location = console_output_ptr;
            console_output_ptr->ch = (char) 0xDB;
        }
        else last_location->ch = ' ';

        blinker = !blinker;
    }
};