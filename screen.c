#include "screen.h"
#include "util.h"

int rowscan = 0;

uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];
int8_t errs[SCREEN_HEIGHT][SCREEN_WIDTH];

static inline uint8_t handle_pixel(uint8_t y, uint8_t x) {
    int err = errs[y][x];
    int c = (int)screen[y][x] + err;
    int output = (c > 7) ? 15 : 0;
    err = c - output;
    errs[y][x] = err;
    return !!output;
}

void clock_columns(){
  gpio_put(C_OE, 0);
  gpio_put(C_LE, 0);
  for (int x = SCREEN_WIDTH;x > 0;x--) {
    int pix =  handle_pixel(rowscan-1, x-1);
    gpio_put(C_DAT, pix);
    pulse(C_CLK, 3);
  }
  gpio_put(C_LE, 1);
  gpio_put(C_OE, 1);
}

bool draw(struct repeating_timer *t) {
  if (rowscan == 0){
    gpio_put(R_DAT, 1);
  }
  pulse(R_CLK, 3);
  gpio_put(R_DAT, 0);
  clock_columns();
  rowscan++;
  if (rowscan>32) {
    rowscan = 0;
  }
  return true;
}