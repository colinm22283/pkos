#include <commands/boot.h>

#include <console/print.h>
#include <console/clear.h>

#include <boot/sequence.h>

__CDECL uint32_t command_boot(__UNUSED uint32_t argc, __UNUSED const char ** argv) {
    console_clear();
    console_print("Beginning boot sequence...\n");

    return boot_sequence_start();
}