#ifndef PARAMS_H
# define PARAMS_H

#define C_CLK 11 // Column shift register clock
#define C_DAT 10 // Column shift register data
#define C_LE 12 // Column shift register latch
#define C_OE 15 // Column shift register output enable
#define R_CLK 13 // Row shift register clock
#define R_DAT 14 // Row shift register data

#define SELECT_1 6 // 1st bit mode selector pin
#define SELECT_2 7 // 2nd bit mode selector pin
#define SELECT_4 8 // 3rd bit mode selector pin
#define SELECT_8 9 // 4th bit mode selector pin

#define P1_L 22 // Player 1 Latch
#define P1_C 21 // Player 1 Clock
#define P1_D 26 // Player 1 Data
#define P2_L 17 // Player 2 Latch
#define P2_C 16 // Player 2 Clock
#define P2_D 18 // Player 2 Data

#define SCREEN_WIDTH 128 // Matrix display width, in pixels
#define SCREEN_HEIGHT 32 // Matrix display height, in pixels

#define COLOR_FULL 15
#define COLOR_OFF 0
#define C15 15
#define C14 14
#define C13 13
#define C12 12
#define C11 11
#define C10 10
#define C9 9
#define C8 8
#define C7 7
#define C6 6
#define C5 5
#define C4 4
#define C3 3
#define C2 2
#define C1 1
#define C0 0

#endif
