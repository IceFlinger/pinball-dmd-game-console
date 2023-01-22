#ifndef SCREEN_H
# define SCREEN_H
#include <stdio.h>
#include "pico/stdlib.h"
#include "params.h"

extern uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

bool draw(struct repeating_timer *t);
#endif