#include <commands/version.h>

#include <console/print.h>

#include <version.h>

__CDECL uint32_t command_version(uint32_t argc, const char ** argv) {
    console_print("PK Bootloader V" VERSION_STRING "\n");

    return 0;
}