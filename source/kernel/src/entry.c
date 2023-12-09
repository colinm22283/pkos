#include <stdint.h>
#include <stdbool.h>

#include <memory.h>
#include <bios_console.h>
#include <string.h>

__attribute__((noreturn)) void kernel_entry(void) {
    print_string("Boot Success!\n");

    heap_init();

    char * string = heap_alloc(20);

    memcpy(string, "Test string", 12);

    print_string(string);
    print_char('\n');

    print_string("Done!\n");

    while (true);
}