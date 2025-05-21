#include "game.h"

uint8_t board[BOARD_DIM][BOARD_DIM];


int main()
{

}


int updateCells()
{
    for(int i = 0; i < BOARD_DIM; i++)
    {
        for(int j = 0; j < BOARD_DIM; j++)
        {
            if()
        }
    }
}



int countLiveNeighbors(int i, int j)
{
    int counter = 0;

    if(i>0 && board[i-1][j]) counter++;
    if(i<BOARD_DIM-1 && board[i+1][j]) counter++;
    if(j>0 && board[i][j-1]) counter++;
    if(j<BOARD_DIM-1 && board[i][j+1]) counter++;

    if(i>0 && j>0 && board[i-1][j-1]) counter++;
    if(i<BOARD_DIM-1 && j<BOARD_DIM-1 && board[i+1][j+1]) counter++;
    if(i<BOARD_DIM-1 && j>0 && board[i+1][j-1]) counter++;
    if(i>0 && j<BOARD_DIM-1 && board[i-1][j+1]) counter++;

    return counter;
}



int printBoard()
{
    printf(CLEAR_SEQ);
    for(int i = 0; i < BOARD_DIM; i++)
    {
        for(int j = 0; j < BOARD_DIM; j++)
            printf(board[i][j]? LIVE_CHAR: " ");
    }
}





//inspired by rafaelglikis on github
void sleep_ms(int millis)
{
    #ifdef _WIN32
        #include <windows.h>
        Sleep(millis);
    #elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
        #include <unistd.h>
        sleep(millis / 1000);
    #else
        usleep(millis);
    #endif
}
