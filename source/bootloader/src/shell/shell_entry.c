#include <stdbool.h>

#include <defs.h>

#include <console/print.h>
#include <console/put.h>

#include <interrupt/init.h>

#include <sys/asm/hlt.h>

__NORETURN void shell_entry(void) {
    console_print("PK Bootloader V1.0\n");

    while (true) {
        console_print("PKBL> ");

        hlt();

        console_print("Interrupt Detected\n");
    }
}