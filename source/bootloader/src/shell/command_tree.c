#include <shell/command_tree.h>

#include <commands/echo.h>
#include <commands/exit.h>
#include <commands/boot.h>
#include <commands/clear.h>

#define SHELL_COMMAND_TREE_ENTRY_NULL ((shell_command_tree_t) { .command_ptr = NULL, .next_char = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, }, })

shell_command_tree_t shell_command_tree_e;
shell_command_tree_t shell_command_tree_ec;
shell_command_tree_t shell_command_tree_ech;
shell_command_tree_t shell_command_tree_echo;
shell_command_tree_t shell_command_tree_ex;
shell_command_tree_t shell_command_tree_exi;
shell_command_tree_t shell_command_tree_exit;

shell_command_tree_t shell_command_tree_b;
shell_command_tree_t shell_command_tree_bo;
shell_command_tree_t shell_command_tree_boo;
shell_command_tree_t shell_command_tree_boot;

shell_command_tree_t shell_command_tree_c;
shell_command_tree_t shell_command_tree_cl;
shell_command_tree_t shell_command_tree_cle;
shell_command_tree_t shell_command_tree_clea;
shell_command_tree_t shell_command_tree_clear;

shell_command_tree_t * shell_command_tree_root[26];

void shell_command_tree_init() {
    for (int i = 0; i < 26; i++) shell_command_tree_root[i] = NULL;
    shell_command_tree_e = SHELL_COMMAND_TREE_ENTRY_NULL;
    shell_command_tree_ec = SHELL_COMMAND_TREE_ENTRY_NULL;
    shell_command_tree_ech = SHELL_COMMAND_TREE_ENTRY_NULL;

    shell_command_tree_root['E' - 'A'] = &shell_command_tree_e;
    shell_command_tree_e.next_char['C' - 'A'] = &shell_command_tree_ec;
    shell_command_tree_ec.next_char['H' - 'A'] = &shell_command_tree_ech;
    shell_command_tree_ech.next_char['O' - 'A'] = &shell_command_tree_echo;
    shell_command_tree_echo.command_ptr = command_echo;
    shell_command_tree_e.next_char['X' - 'A'] = &shell_command_tree_ex;
    shell_command_tree_ex.next_char['I' - 'A'] = &shell_command_tree_exi;
    shell_command_tree_exi.next_char['T' - 'A'] = &shell_command_tree_exit;
    shell_command_tree_exit.command_ptr = command_exit;

    shell_command_tree_root['B' - 'A'] = &shell_command_tree_b;
    shell_command_tree_b.next_char['O' - 'A'] = &shell_command_tree_bo;
    shell_command_tree_bo.next_char['O' - 'A'] = &shell_command_tree_boo;
    shell_command_tree_boo.next_char['T' - 'A'] = &shell_command_tree_boot;
    shell_command_tree_boot.command_ptr = command_boot;

    shell_command_tree_root['C' - 'A'] = &shell_command_tree_c;
    shell_command_tree_c.next_char['L' - 'A'] = &shell_command_tree_cl;
    shell_command_tree_cl.next_char['E' - 'A'] = &shell_command_tree_cle;
    shell_command_tree_cle.next_char['A' - 'A'] = &shell_command_tree_clea;
    shell_command_tree_clea.next_char['R' - 'A'] = &shell_command_tree_clear;
    shell_command_tree_clear.command_ptr = command_clear;
}