#include "nes_input.h"
#include "util.h"

uint8_t get_player_input(int latch, int clock, int data){
  // Right A B Select Start Up Down Left
  int pulsel = 9;
  uint8_t sum = 0;
  pulse(latch, pulsel);
  sum += 128 * gpio_get(data);
  pulse(clock, pulsel);
  sum += 64 * gpio_get(data);
  pulse(clock, pulsel);
  sum += 32 * gpio_get(data);
  pulse(clock, pulsel);
  sum += 16 * gpio_get(data);
  pulse(clock, pulsel);
  sum += 8 * gpio_get(data);
  pulse(clock, pulsel);
  sum += 4 * gpio_get(data);
  pulse(clock, pulsel);
  sum += 2 * gpio_get(data);
  pulse(clock, pulsel);
  sum += gpio_get(data);
  return sum;
}

bool pressed_right(uint8_t input){
	if (!((128 & input)>0)){
		return true;
	}
	return false;
}
bool pressed_a(uint8_t input){
	if (!((64 & input)>0)){
		return true;
	}
	return false;
}
bool pressed_b(uint8_t input){
	if (!((32 & input)>0)){
		return true;
	}
	return false;
}
bool pressed_select(uint8_t input){
	if (!((16 & input)>0)){
		return true;
	}
	return false;
}
bool pressed_start(uint8_t input){
	if (!((8 & input)>0)){
		return true;
	}
	return false;
}
bool pressed_up(uint8_t input){
	if (!((4 & input)>0)){
		return true;
	}
	return false;
}
bool pressed_down(uint8_t input){
	if (!((2 & input)>0)){
		return true;
	}
	return false;
}
bool pressed_left(uint8_t input){
	if (!((1 & input)>0)){
		return true;
	}
	return false;
}