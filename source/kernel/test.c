#include <stdbool.h>
#include <stdint.h>

__attribute__((noreturn)) void _kernel_entry() {
    uint16_t * console_mem = (uint16_t *) 0xB8000;

    console_mem[0] = 'B' | 0x0f00;
    console_mem[1] = 'O' | 0x0f00;
    console_mem[2] = 'O' | 0x0f00;
    console_mem[3] = 'T' | 0x0f00;

    while (true);
}