#include <stdint.h>

#include <defs.h>

#include <sys/halt.h>

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
    char * console_buffer = (char *) 0xB8000;

    *(console_buffer + 0) = 'B';
    *(console_buffer + 2) = 'O';
    *(console_buffer + 4) = 'O';
    *(console_buffer + 6) = 'T';

    halt();
}