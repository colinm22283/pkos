#include <shell/keyboard_handler.h>

#include <shell/input.h>

#include <console/put.h>
#include <console/backspace.h>

#include <sys/asm/in.h>

void shell_keyboard_key_down_handler(char c) {
    if (!shell_ready_to_execute) {
        if (c == 8) {
            if (shell_backspace()) console_backspace();
        }
        else if (c == '\n') {
            shell_read_command();
        }
        else {
            if (shell_input_char(c)) console_put(c);
        }
    }
}