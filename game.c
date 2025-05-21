#include "game.h"

uint8_t board[BOARD_DIM][BOARD_DIM];
uint8_t deathRow[BOARD_DIM * BOARD_DIM][2];
uint8_t newborns [BOARD_DIM * BOARD_DIM][2];

int deathRowIdx = 0;
int newbornsIdx = 0;



int main()
{
    board[5][1] = LIVE;
    board[5][2] = LIVE;
    board[6][1] = LIVE;
    board[6][2] = LIVE;

    board[5][11] = LIVE;
    board[6][11] = LIVE;
    board[7][11] = LIVE;
    board[4][12] = LIVE;
    board[8][12] = LIVE;
    board[3][13] = LIVE;
    board[9][13] = LIVE;
    board[3][14] = LIVE;
    board[9][14] = LIVE;
    board[6][15] = LIVE;
    board[4][16] = LIVE;
    board[8][16] = LIVE;
    board[5][17] = LIVE;
    board[6][17] = LIVE;
    board[7][17] = LIVE;
    board[6][18] = LIVE;

    board[3][21] = LIVE;
    board[4][21] = LIVE;
    board[5][21] = LIVE;
    board[3][22] = LIVE;
    board[4][22] = LIVE;
    board[5][22] = LIVE;
    board[2][23] = LIVE;
    board[6][23] = LIVE;
    board[1][25] = LIVE;
    board[2][25] = LIVE;
    board[6][25] = LIVE;
    board[7][25] = LIVE;

    board[3][35] = LIVE;
    board[4][35] = LIVE;
    board[3][36] = LIVE;
    board[4][36] = LIVE;


    int gameOn = 1;
    while(gameOn)
    {
        printBoard();
        updateCells();
        sleep_ms(UPDATE_COOLDOWN);
        //printf(CLEAR_SEQ);
    }
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
