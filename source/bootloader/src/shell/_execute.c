#include <stdint.h>
#include <stdbool.h>

#include <shell/execute.h>
#include <shell/command_tree.h>

static inline bool is_valid_cmd_char(char c) {
    return c >= 'a' && c < 'z';
}

uint32_t shell_execute(const char * command) {
    if (!is_valid_cmd_char(command[0])) return SHELL_EXECUTE_COMMAND_NOT_FOUND;

    shell_command_tree_entry_t * current_entry = shell_command_tree_root[command[0] - 'a'];

    for (uint32_t i = 0; command[i] != '\0'; i++) {

    }

    return SHELL_EXECUTE_COMMAND_NOT_FOUND;
}