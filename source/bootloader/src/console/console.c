#include <console/console.h>

console_char_t * console_output_ptr = CONSOLE_BASE_POINTER;
console_char_t * console_newline_ptr = CONSOLE_BASE_POINTER + CONSOLE_WIDTH;