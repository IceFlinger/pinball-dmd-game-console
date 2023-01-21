#include "screen.h"
#include "util.h"

int rowscan = 0;
uint32_t framecount = 0;

uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

static inline uint8_t handle_pixel(uint8_t color) {
    return gldp[(color/(256/GLDP_COUNT)) * GLDP_LENGTH + framecount];
}

void clock_columns(){
  gpio_put(C_OE, 0);
  gpio_put(C_LE, 0);
  for (int x = SCREEN_WIDTH;x > 0;x--) {
    gpio_put(C_DAT, handle_pixel(screen[rowscan-1][x-1]));
    pulse(C_CLK, 3);
  }
  gpio_put(C_LE, 1);
  gpio_put(C_OE, 1);
}

bool draw(struct repeating_timer *t) {
  //Drawing
  if (rowscan == 0){
    gpio_put(R_DAT, 1);
  }
  pulse(R_CLK, 3);
  gpio_put(R_DAT, 0);
  clock_columns();
  rowscan++;
  if (rowscan>32) {
    rowscan = 0;
    framecount++;
    if (framecount == GLDP_LENGTH) {
      framecount = 0;
    }
  }
  return true;
}