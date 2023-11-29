#include <stdint.h>

#include <bios_console.h>

#define CONSOLE_BASE ((uint16_t *) 0xB8000)
#define CONSOLE_WIDTH (40)
#define CONSOLE_HEIGHT (25)

uint16_t * console_loc = CONSOLE_BASE;
uint16_t * console_next_loc = CONSOLE_BASE + CONSOLE_WIDTH;

void print_char(char c) {
    if (c == '\n') {
        console_loc = console_next_loc;
        console_next_loc += CONSOLE_WIDTH;
    }
    else *(((uint8_t *) console_loc++)) = c;
}

void print_string(const char * c) {
    while (*c != '\0') print_char(*(c++));
}

void print_uint32(uint32_t num) {
    uint8_t num_len = 0;
    for (uint32_t x = num; x > 0; x /= 10) num_len++;
    console_loc += num_len;
    while (num > 0) {
        *((uint8_t *) --console_loc) = '0' + (num % 10);
        num /= 10;
    }
}

void print_int32(int32_t num) {
    print_char('-');
    print_uint32((uint32_t) num);
}