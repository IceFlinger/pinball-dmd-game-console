#include "game_example.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "../nes_input.h"
#include "../params.h"
#include "../util.h"

int test_x;
int test_y;
int test_size;

void game_example_init(uint8_t (*screen)[SCREEN_WIDTH]){
  test_x = 16;
  test_y = 16;
  test_size = 10;
};

void game_example_draw(uint8_t (*screen)[SCREEN_WIDTH]){
  clear_screen(screen);
  for (int i = test_y; i < test_y + test_size; i++){
      for (int j = test_x; j < test_x + test_size; j++) {
        screen[i][j] = C5;
      }
  }
};

void game_example_step(uint8_t p1_input, uint8_t p2_input, uint8_t (*screen)[SCREEN_WIDTH]){
    if (pressed_a(p1_input)){
      printf("%d, %d\r\n", test_x, test_y);
    }
    if (pressed_b(p1_input)){
      if (pressed_up(p1_input)){
        test_size++;
      }
      if (pressed_down(p1_input)){
        test_size--;
      }
    } else {
      if (pressed_up(p1_input)){
        if (test_y + test_size < SCREEN_HEIGHT){
          test_y++;
        }
      }
      if (pressed_down(p1_input)){
        if (test_y > 0){
          test_y--;
        }
      }
      if (pressed_left(p1_input)){
        if (test_x > 0){
          test_x--;
        }
      }
      if (pressed_right(p1_input)){
        if (test_x + test_size < SCREEN_WIDTH){
          test_x++;
        }
      }
    }
};