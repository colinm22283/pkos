#pragma once

#include <stdbool.h>

extern volatile bool keyboard_awaiting_key;
extern char keyboard_pressed_key;

void keyboard_key_down_handler(char key);
void keyboard_key_up_handler(char key);