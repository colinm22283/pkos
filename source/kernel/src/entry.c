#include <stdbool.h>
#include <stdint.h>

#include <heap.h>
#include <bios_console.h>

__attribute__((noreturn)) void _kernel_entry() {
    _heap_init();

    print_string("Boot Success!\nTest: ");
    print_uint32(43523532);

    while (true);
}