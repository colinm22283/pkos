#include <commands/boot.h>

#include <console/print.h>

__CDECL uint32_t command_boot(uint32_t argc, const char ** argv) {
    console_print("Beginning boot sequence...\n");

    return 1;
}