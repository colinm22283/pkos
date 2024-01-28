#include <shell/input.h>

uint8_t shell_position = 0;
char shell_input_buffer[256];
bool shell_ready_to_execute = false;