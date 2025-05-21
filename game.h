#ifndef GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


#define CLEAR_SEQ "\x1b[2J\x1b[H"
#define BOARD_DIM 64
#define LIVE_CHAR '#'
#define REFRESH_RATE 20

#define UPDATE_COOLDOWN ((60 / REFRESH_RATE) * 1000)

#define ROW 0
#define COL 1
#define LIVE 1
#define DEAD 0



int printBoard();
void sleep_ms(int millis);
int countLiveNeighbors(int i, int j);
int lifeCycle();


#endif