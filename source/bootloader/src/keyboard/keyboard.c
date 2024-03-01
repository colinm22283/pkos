#include <stdint.h>

#include <keyboard/keyboard.h>

volatile bool keyboard_awaiting_key = false;
char keyboard_pressed_key = 0;

void keyboard_key_down_handler(char key) {
    if (keyboard_awaiting_key) {
        keyboard_pressed_key = key;
        keyboard_awaiting_key = false;
    }
}
void keyboard_key_up_handler(char) { }