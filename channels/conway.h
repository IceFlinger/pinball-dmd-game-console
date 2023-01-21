#ifndef CONWAY_H
# define CONWAY_H
#include <stdio.h>
#include "pico/stdlib.h"
#include "../params.h"

void conway_init(uint8_t (*screen)[SCREEN_WIDTH]);
void conway_draw(uint8_t (*screen)[SCREEN_WIDTH]);
void conway_step(uint8_t p1_input, uint8_t p2_input, uint8_t (*screen)[SCREEN_WIDTH]);

#endif