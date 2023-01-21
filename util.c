#include "util.h"
#include <string.h>

uint8_t blank[SCREEN_HEIGHT][SCREEN_WIDTH];

void init_blank(){
  for (int i = 0; i < SCREEN_HEIGHT; i++){
      for (int j = 0; j < SCREEN_WIDTH; j++) {
        blank[i][j] = 0;
    }
  }
}

//Clock a single pin once
void pulse(int pin, int cycles) {
  gpio_put(pin, 1);
  busy_wait_at_least_cycles(cycles);
  gpio_put(pin, 0);
}

// Blank out shift registers
void reset_screen() {
  gpio_put(C_OE, 1);
  gpio_put(C_LE, 1);
  gpio_put(R_DAT, 0);
  gpio_put(C_DAT, 0);
  for (int y = 0; y < SCREEN_HEIGHT;y++){
    for (int x = 0;x < SCREEN_WIDTH;x++) {
       pulse(C_CLK, 3);
    }
    pulse(R_CLK, 3);
  }
  gpio_put(C_OE, 0);
  gpio_put(C_LE, 0);
}

void clear_screen(uint8_t (*screen)[SCREEN_WIDTH]) {
  memcpy(screen, blank, SCREEN_HEIGHT*SCREEN_WIDTH);
}