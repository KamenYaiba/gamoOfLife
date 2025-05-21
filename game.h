#ifndef GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define CLEAR_SEQ "\x1b[2J\x1b[H"
#define BOARD_DIM 64
#define LIVE_CHAR '#'
#define REFRESH_RATE 20

#define UPDATE_COOLDOWN ((60 / REFRESH_RATE) * 1000)


int printBoard();
void sleep_ms(int millis);


#endif