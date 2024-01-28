#include <commands/exit.h>
#include <console/print.h>

__CDECL uint32_t command_exit(uint32_t argc, const char ** argv) {
    console_print("exit unimplemented :(\n");

    return 0;
}