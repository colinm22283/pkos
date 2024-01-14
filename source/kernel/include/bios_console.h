#pragma once

typedef enum {
    BC_BLACK = 0,
    BC_BLUE,
    BC_GREEN,
    BC_CYAN,
    BC_RED,
    BC_MAGENTA,
    BC_BROWN,
    BC_LIGHT_GRAY,
    BC_DARK_GRAY,
    BC_LIGHT_BLUE,
    BC_LIGHT_GREEN,
    BC_LIGHT_CYAN,
    BC_LIGHT_RED,
    BC_LIGHT_MAGENTA,
    BC_YELLOW,
    BC_WHITE
} bios_color_t;

#define BIOS_COLOR(foreground, background) ((foreground) | ((background) << 4))

void print_char(char c);
void print_char_color(char c, uint8_t color);
void print_string(const char * c);
void print_string_color(const char * c, uint8_t color);
void print_uint64(uint64_t num);
void print_int64(int64_t num);
void print_uint32(uint32_t num);
void print_int32(int32_t num);
void print_uint8(uint8_t num);
void print_int8(int8_t num);