#ifndef UTIL_H
# define UTIL_H
#include <stdio.h>
#include "pico/stdlib.h"
#include "params.h"

void init_blank();
void pulse(int pin, int cycles);
void reset_screen();
void clear_screen(uint8_t (*screen)[SCREEN_WIDTH]);
#endif