#ifndef NES_INPUT_H
# define NES_INPUT_H
#include <stdio.h>
#include "pico/stdlib.h"

uint8_t get_player_input(int latch, int clock, int data);

bool pressed_a(uint8_t input);
bool pressed_b(uint8_t input);
bool pressed_start(uint8_t input);
bool pressed_select(uint8_t input);
bool pressed_up(uint8_t input);
bool pressed_down(uint8_t input);
bool pressed_left(uint8_t input);
bool pressed_right(uint8_t input);
#endif