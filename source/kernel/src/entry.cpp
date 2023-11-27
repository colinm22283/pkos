#include <cstdint>

class TestClass {
public:
    uint16_t * console_mem;

    explicit inline TestClass(uint16_t * _console_mem): console_mem(_console_mem) { }

    inline void print_boot() {
        console_mem[0] = 'B' | 0x0F00;
        console_mem[1] = 'O' | 0x0F00;
        console_mem[2] = 'O' | 0x0F00;
        console_mem[3] = 'T' | 0x0F00;
        console_mem[4] = '!' | 0x0F00;
    }
};

extern "C" __attribute__((noreturn)) void _kernel_entry() {
    TestClass test((uint16_t *) 0xB8000);

    test.print_boot();

    while (true);
}