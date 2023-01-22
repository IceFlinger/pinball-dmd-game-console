#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include <string.h>
#include "params.h"
#include "nes_input.h"
#include "util.h"
#include "screen.h"
#include "channels/game_example.h"
#include "channels/screensaver.h"
#include "channels/conway.h"

struct repeating_timer timer;

bool mode_switched = true;
int selection = 0;

const long defaultanimationInterval = 40000;

typedef void (*InitFunc)(uint8_t (*screen)[SCREEN_WIDTH]);
typedef void (*DrawFunc)(uint8_t (*screen)[SCREEN_WIDTH]);
typedef void (*StepFunc)(uint8_t p1_input, uint8_t p2_input, uint8_t (*screen)[SCREEN_WIDTH]);

void gameloop(InitFunc game_init, DrawFunc game_draw, StepFunc game_step, int animationInterval) {
  reset_screen();
  clear_screen(screen);
  game_init(screen);
  while(1){
    if (mode_switched) {
      return;
    }
    uint8_t p1_input = get_player_input(P1_L, P1_C, P1_D);
    uint8_t p2_input = get_player_input(P2_L, P2_C, P2_D);
    game_step(p1_input, p2_input, screen);
    game_draw(screen);
    busy_wait_us(animationInterval);
  }
}

void nothing() {
  reset_screen();
  clear_screen(screen);
  while(1){
    if (mode_switched) {
      return;
    }
    busy_wait_us(defaultanimationInterval);
  }
}

int get_selection() {
  int selection = !gpio_get(SELECT_1);
  selection += (!gpio_get(SELECT_2)*2);
  selection += (!gpio_get(SELECT_4)*4);
  selection += (!gpio_get(SELECT_8)*8);
  return selection;
}

void select_mode(int selection) {
  printf("Channel: %d\r\n", selection);
  mode_switched = false;
  switch(selection) {
    case 0:
      nothing();
      break;
    case 1:
      nothing();
      break;
    case 2:
      nothing();
      break;
    case 3:
      nothing();
      break;
    case 4:
      nothing();
      break;
    case 5:
      nothing();
      break;
    case 6:
      nothing();
      break;
    case 7:
      nothing();
      break;
    case 8:
      nothing();
      break;
    case 9:
      nothing();
      break;
    case 10:
      nothing();
      break;
    case 11:
      nothing();
      break;
    case 12:
      nothing();
      break;
    case 13:
      gameloop(conway_init, conway_draw, conway_step, 0);
      break;
    case 14:
      gameloop(game_example_init, game_example_draw, game_example_step, defaultanimationInterval);
      break;
    case 15:
      gameloop(screensaver_init, screensaver_draw, screensaver_step, defaultanimationInterval);
      break;
  }
}

void selector_callback(uint gpio, uint32_t events) {
  mode_switched = true;
}

void selector_init(){
    multicore_fifo_push_blocking(0xc001);
 
    uint32_t g = multicore_fifo_pop_blocking();
 
    if (g != 0xc001)
        printf("Logic Core 1 Problem\r\n");
    else
        printf("Logic Core 1 Ready\r\n");
 
    while(1){
      select_mode(get_selection());
    }
}

int main()
{
  stdio_init_all();

  // DMD pins
  gpio_init(C_CLK);
  gpio_init(C_DAT);
  gpio_init(C_OE);
  gpio_init(C_LE);
  gpio_init(R_CLK);
  gpio_init(R_DAT);

  gpio_set_dir(C_CLK, 1);
  gpio_set_dir(C_DAT, 1);
  gpio_set_dir(C_OE, 1);
  gpio_set_dir(C_LE, 1);
  gpio_set_dir(R_CLK, 1);
  gpio_set_dir(R_DAT, 1);

  gpio_put(C_CLK, 0);
  gpio_put(C_DAT, 0);
  gpio_put(C_OE, 0);
  gpio_put(C_LE, 0);
  gpio_put(R_CLK, 0);
  gpio_put(R_DAT, 0);

  // Channel Selector Pins
  gpio_init(SELECT_1);
  gpio_init(SELECT_2);
  gpio_init(SELECT_4);
  gpio_init(SELECT_8);

  gpio_set_dir(SELECT_1, 0);
  gpio_set_dir(SELECT_2, 0);
  gpio_set_dir(SELECT_4, 0);
  gpio_set_dir(SELECT_8, 0);

  gpio_pull_up(SELECT_1);
  gpio_pull_up(SELECT_2);
  gpio_pull_up(SELECT_4);
  gpio_pull_up(SELECT_8);

  gpio_set_irq_enabled_with_callback(SELECT_1, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &selector_callback);
  gpio_set_irq_enabled_with_callback(SELECT_2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &selector_callback);
  gpio_set_irq_enabled_with_callback(SELECT_4, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &selector_callback);
  gpio_set_irq_enabled_with_callback(SELECT_8, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &selector_callback);

  // Controller plug pins
  gpio_init(P1_C);
  gpio_init(P1_D);
  gpio_init(P1_L);
  gpio_init(P2_C);
  gpio_init(P2_D);
  gpio_init(P2_L);

  gpio_set_dir(P1_C, 1);
  gpio_set_dir(P1_D, 0);
  gpio_set_dir(P1_L, 1);
  gpio_set_dir(P2_C, 1);
  gpio_set_dir(P2_D, 0);
  gpio_set_dir(P2_L, 1);

  gpio_put(P1_C, 0);
  gpio_put(P1_L, 0);
  gpio_put(P2_C, 0);
  gpio_put(P2_L, 0);

  gpio_pull_up(P1_D);
  gpio_pull_up(P2_D);


  reset_screen();
  init_blank();
  clear_screen(screen);
  printf("Starting...\r\n");
  multicore_launch_core1(selector_init);

  // Wait for it to start up

  uint32_t g = multicore_fifo_pop_blocking();

  if (g != 0xc001)
      printf("Scanline Core 0 Problem\r\n");
  else {
      multicore_fifo_push_blocking(0xc001);
      printf("Scanline Core 0 Ready\r\n");
  }
  add_repeating_timer_us(-90, draw, NULL, &timer);
  while(1){
    busy_wait_us(1);
  }

  return 0;
}
