#ifndef SCREENSAVER_H
# define SCREENSAVER_H
#include <stdio.h>
#include "pico/stdlib.h"
#include "../params.h"

void screensaver_init(uint8_t (*screen)[SCREEN_WIDTH]);
void screensaver_draw(uint8_t (*screen)[SCREEN_WIDTH]);
void screensaver_step(uint8_t p1_input, uint8_t p2_input, uint8_t (*screen)[SCREEN_WIDTH]);

#endif