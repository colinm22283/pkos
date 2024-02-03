#include <commands/exit.h>
#include <console/print.h>
#include <console/clear.h>

#include <sys/halt.h>

__CDECL uint32_t command_exit(uint32_t argc, const char ** argv) {
    console_clear();
    console_print("Ready to power off.\n");

    halt();

//    return 0;
}