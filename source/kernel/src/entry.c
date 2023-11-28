#include <stdbool.h>
#include <stdint.h>

#include <heap.h>

uint8_t * console_loc = (uint8_t *) 0xB8000;

static inline void print_char(char c) {
    *(console_loc++) = c;
    console_loc++;
}

__attribute__((noreturn)) void _kernel_entry() {
    _heap_init();

    print_char('B');
    print_char('o');
    print_char('o');
    print_char('t');

    while (true);
}