#ifndef SCREEN_H
# define SCREEN_H
#include <stdio.h>
#include "pico/stdlib.h"
#include "params.h"

#define GLDP_LENGTH 15
#define GLDP_COUNT 6

extern uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

// Tested which PWM sequences had the least flickering
const static unsigned char gldp[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
        0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1,
        0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

bool draw(struct repeating_timer *t);
#endif