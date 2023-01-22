#include "conway.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "../nes_input.h"
#include "../params.h"
#include "../util.h"
#include "hardware/adc.h"
#include <string.h>

#define ROWS 32
#define COLUMNS 128/8
#define GRID_HEIGHT 32
#define GRID_WIDTH 16

uint8_t grid[GRID_HEIGHT][GRID_WIDTH];
bool step;

//Game of Life helpers
uint8_t new_row_block(uint8_t center, uint8_t n[8]) {
  uint8_t newbl = 0b00000000;
  uint8_t count = 0;
  //First pixel neighbors
  count = count + (0b00000001 & n[0]);
  count = count + (0b00000001 & n[1] >> 7);
  count = count + (0b00000001 & n[1] >> 6);
  count = count + (0b00000001 & n[3]);
  count = count + (0b00000001 & center >> 6);
  count = count + (0b00000001 & n[5]);
  count = count + (0b00000001 & n[6] >> 7);
  count = count + (0b00000001 & n[6] >> 6);
  if (count == 3) {
    //birth or survive
    newbl = newbl + 0b10000000;
  } else if (count != 2) {
    //die (newbl bit already 0)
  } else {
    //survive
    newbl = newbl + (0b10000000 & center);
  }
  //Middle pixel neighbors
  for (uint8_t j = 0; j < 6; j++) {
    count = 0;
      count = count + (0b00000001 & n[1] >> (7-j));
      count = count + (0b00000001 & n[1] >> (6-j));
      count = count + (0b00000001 & n[1] >> (5-j));
      count = count + (0b00000001 & center >> (7-j));
      count = count + (0b00000001 & center >> (5-j));
      count = count + (0b00000001 & n[6] >> (7-j));
      count = count + (0b00000001 & n[6] >> (6-j));
      count = count + (0b00000001 & n[6] >> (5-j));
      if (count == 3) {
        //birth or survive
        newbl = newbl + (0b00000001 << (6-j));
      } else if (count != 2) {
        //die (newbl bit already 0)
      } else {
        //survive
        newbl = newbl + (center & (0b00000001 << (6-j)));
      }
  }
  count = 0;
  //Final pixel neighbors
  count = count + (0b00000001 & n[1]);
  count = count + (0b00000001 & n[1] >> 1);
  count = count + (0b00000001 & n[2] >> 7);
  count = count + (0b00000001 & center >> 1);
  count = count + (0b00000001 & n[4] >> 7);
  count = count + (0b00000001 & n[6] >> 1);
  count = count + (0b00000001 & n[6]);
  count = count + (0b00000001 & n[7] >> 7);
  if (count == 3) {
    //birth or survive
    newbl = newbl + 0b00000001;
  } else if (count != 2) {
    //die (newbl bit already 0)
  } else {
    //survive
    newbl = newbl + (0b00000001 & center);
  }
  return newbl;
}

uint8_t mod(uint8_t a, uint8_t b)
{
    uint8_t r = a % b;
    return r < 0 ? r + b : r;
}

void conway_init(uint8_t (*screen)[SCREEN_WIDTH]){
	adc_init();
  step = true;
	adc_select_input(4);
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLUMNS; j++) {
      if (!(i == 4)){
        grid[i][j] = adc_read();
      }
		}
	}
}

void conway_draw(uint8_t (*screen)[SCREEN_WIDTH]){
  //skip drawing here because its more efficient to draw to screen during step func loops
}

void conway_step(uint8_t p1_input, uint8_t p2_input, uint8_t (*screen)[SCREEN_WIDTH]){
  if (!pressed_a(p1_input)){
    step = false;
    bool fdisp[GRID_HEIGHT][GRID_WIDTH*8];
    for (uint8_t y = 0; y < GRID_HEIGHT; y++) {
      for (uint8_t x = 0; x < GRID_WIDTH; x++) {
      uint8_t neighbors[8] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000};
      //Retriving neighbors...
      neighbors[0] = grid[mod(y-1,GRID_HEIGHT)][mod(x-1,GRID_WIDTH)];
      neighbors[1] = grid[mod(y-1,GRID_HEIGHT)][mod(x,GRID_WIDTH)];
      neighbors[2] = grid[mod(y-1,GRID_HEIGHT)][mod(x+1,GRID_WIDTH)];
      neighbors[3] = grid[mod(y,GRID_HEIGHT)][mod(x-1,GRID_WIDTH)];
      neighbors[4] = grid[mod(y,GRID_HEIGHT)][mod(x+1,GRID_WIDTH)];
      neighbors[5] = grid[mod(y+1,GRID_HEIGHT)][mod(x-1,GRID_WIDTH)];
      neighbors[6] = grid[mod(y+1,GRID_HEIGHT)][mod(x,GRID_WIDTH)];
      neighbors[7] = grid[mod(y+1,GRID_HEIGHT)][mod(x+1,GRID_WIDTH)];
      uint8_t newbl = new_row_block(grid[y][x], neighbors);
        for (uint8_t p = 0; p < 8; p++) {
          if (((newbl >> 7-p)&0b00000001) == 0b00000001) {    
          fdisp[y][(x*8)+p] = true;
          } else {
          fdisp[y][(x*8)+p] = false;
          }
        }
      }
    }
    clear_screen(screen);
    for (uint8_t y = 0; y < GRID_HEIGHT; y++) {
      for (uint8_t x = 0; x < GRID_WIDTH; x++) {
        uint8_t newbl = 0b00000000;
        for (uint8_t p = 0; p < 8; p++) {
          if (fdisp[y][(x*8)+p]) {
            newbl = newbl + (0b10000000 >> p);
            screen[y][(x*8)+p] = C15;
          }
        }
        grid[y][x] = newbl;
      }
    }
  }
}