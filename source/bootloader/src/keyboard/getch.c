#include <stdbool.h>

#include <keyboard/getch.h>
#include <keyboard/keyboard.h>

char keyboard_getch() {
    keyboard_awaiting_key = true;
    while (keyboard_awaiting_key) { }
    return keyboard_pressed_key;
}