#include <stdint.h>

#include <keyboard/keyboard.h>
#include <keyboard/keycode.h>

volatile bool keyboard_awaiting_key = false;
keycode_t keyboard_pressed_key = 0;

void keyboard_key_down_handler(keycode_t key) {
    if (keyboard_awaiting_key) {
        keyboard_pressed_key = key;
        keyboard_awaiting_key = false;
    }
}
void keyboard_key_up_handler(keycode_t) { }