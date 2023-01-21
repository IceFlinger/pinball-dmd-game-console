#ifndef GAME_EXAMPLE_H
# define GAME_EXAMPLE_H
#include <stdio.h>
#include "pico/stdlib.h"
#include "../params.h"

void game_example_init(uint8_t (*screen)[SCREEN_WIDTH]);
void game_example_draw(uint8_t (*screen)[SCREEN_WIDTH]);
void game_example_step(uint8_t p1_input, uint8_t p2_input, uint8_t (*screen)[SCREEN_WIDTH]);

#endif