#include <cstdint>

extern "C" __attribute__((noreturn)) void _kernel_entry() {
    auto * console_mem = (uint16_t *) 0xB8000;

    console_mem[0] = 'B' | 0x0F00;
    console_mem[1] = 'O' | 0x0F00;
    console_mem[2] = 'O' | 0x0F00;
    console_mem[3] = 'T' | 0x0F00;
    console_mem[4] = '!' | 0x0F00;

    while (true);
}