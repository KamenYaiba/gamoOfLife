#ifndef GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


#define CLEAR_SEQ "\e[1;1H\e[2J"
#define FRAME_LEN 20
#define FRAME_WID 50
#define LIVE_CHAR '#'
#define REFRESH_RATE 10

#define UPDATE_COOLDOWN (1000 / REFRESH_RATE)

#define ROW 0
#define COL 1
#define LIVE 1
#define DEAD 0

#define IJ_TO_PIXEL_NUM(i, j) (i * (FRAME_WID+1) + j)


int printBoard();
void sleep_ms(int millis);
int updateCells();
int countLiveNeighbors(int i, int j);
int lifeCycle();
int gosperGliderGun_20x50();
int setup();


#endif