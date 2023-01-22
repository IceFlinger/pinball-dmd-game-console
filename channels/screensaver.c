#include "screensaver.h"
#include "../nes_input.h"

void screensaver_init(uint8_t (*screen)[SCREEN_WIDTH]){
  for (int i = 0; i < SCREEN_HEIGHT; i++){
      for (int j = 0; j < SCREEN_WIDTH; j++) {
        if (i > 8 && i < 24){
          screen[i][j] = j/8;
        } else {
          screen[i][j] = 0;
        }
    }
  }
}

void screensaver_draw(uint8_t (*screen)[SCREEN_WIDTH]){

}

void screensaver_step(uint8_t p1_input, uint8_t p2_input, uint8_t (*screen)[SCREEN_WIDTH]){
    if (pressed_b(p1_input)){
      for (int i = 0; i < SCREEN_HEIGHT; i++){
          for (int j = 0; j < SCREEN_WIDTH; j++) {
            screen[i][j]--;
          }
      }
    }
    if (pressed_a(p1_input)){
      uint8_t first_row[SCREEN_WIDTH];
      for (int j = 0; j < SCREEN_WIDTH; j++) {
        first_row[j] = screen[0][j];
      }
      for (int i = 0; i < SCREEN_HEIGHT-1; i++){
          for (int j = 0; j < SCREEN_WIDTH; j++) {
            screen[i][j] = screen[i+1][j];
          }
      }
      for (int j = 0; j < SCREEN_WIDTH; j++) {
            screen[SCREEN_HEIGHT-1][j] = first_row[j];
      }
      uint8_t first_col[SCREEN_HEIGHT];
      for (int i = 0; i < SCREEN_HEIGHT; i++) {
        first_col[i] = screen[i][0];
      }
      for (int i = 0; i < SCREEN_HEIGHT-1; i++){
          for (int j = 0; j < SCREEN_WIDTH; j++) {
            screen[i][j] = screen[i][j+1];
          }
      }
      for (int i = 0; i < SCREEN_HEIGHT; i++) {
            screen[i][SCREEN_WIDTH-1] = first_col[i];
      }
    }
}