#pragma once

#include <stdbool.h>

#include <keyboard/keycode.h>

extern volatile bool keyboard_awaiting_key;
extern keycode_t keyboard_pressed_key;

void keyboard_key_down_handler(keycode_t key);
void keyboard_key_up_handler(keycode_t key);