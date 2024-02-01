#include <stdbool.h>

#include <defs.h>

#include <console/print.h>
#include <console/put.h>
#include <console/newline.h>
#include <console/print_hex.h>
#include <console/clear.h>

#include <shell/input.h>
#include <shell/execute.h>
#include <shell/command_tree.h>

#include <sys/wait_for_interrupt.h>

__NORETURN void shell_entry(void) {
    shell_command_tree_init();

    console_clear();
    console_print("PK Bootloader V1.0\n");

    while (true) {
        console_print("PKBL> ");

        while (!shell_ready_to_execute) wait_for_interrupt();
        shell_ready_to_execute = false;

        console_newline();
        uint32_t result = shell_execute(shell_input_buffer);
        if (result == 0xFFFFFFFF) {
            console_print("Command not found\n");
        }
        else if (result > 0) {
            console_print("Command exited with code 0x");
            console_print_hex(result);
            console_newline();
        }
    }
}