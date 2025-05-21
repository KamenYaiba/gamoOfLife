#include "game.h"

uint8_t board[BOARD_DIM][BOARD_DIM];
uint8_t deathRow[BOARD_DIM * BOARD_DIM][2];
uint8_t newborns [BOARD_DIM * BOARD_DIM][2];

int deathRowIdx = 0;
int newbornsIdx = 0;



int main()
{
    
}


int updateCells()
{
    int liveNeighbors = 0;
    int changed = 0;
    for(int i = 0; i < BOARD_DIM; i++)
    {
        for(int j = 0; j < BOARD_DIM; j++)
        {
            liveNeighbors = countLiveNeighbors(i, j);
            if((liveNeighbors < 2 || liveNeighbors > 3) && !board[i][j])
            {
                changed = 1;
                deathRow[deathRowIdx][ROW] = i;
                deathRow[deathRowIdx++][COL] = j;
            }
            else if(liveNeighbors == 3 && board[i][j])
            {
                changed = 1;
                newborns[deathRowIdx][ROW] = i;
                newborns[deathRowIdx++][COL] = j;
            }
        }
    }

    if(changed)
        lifeCycle();

    return changed;
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

int lifeCycle()
{
    for(int i = 0; i < deathRowIdx; i ++)
    {
        int r = deathRow[i][ROW];
        int c = deathRow[i][COL];

        board[r][c] = DEAD;
    }

    for(int i = 0; i < newbornsIdx; i ++)
    {
        int r = newborns[i][ROW];
        int c = newborns[i][COL];

        board[r][c] = LIVE;
    }
}



int printBoard()
{
    printf(CLEAR_SEQ);
    for(int i = 0; i < BOARD_DIM; i++)
    {
        for(int j = 0; j < BOARD_DIM; j++)
            printf("%c", board[i][j]? LIVE_CHAR: ' ');
    }
}





//inspired by rafaelglikis on github
void sleep_ms(int millis)
{
    #ifdef _WIN32
        Sleep(millis);
    #else
        usleep(millis * 1000);
    #endif
}
