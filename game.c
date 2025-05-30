#include "game.h"

uint8_t board[FRAME_LEN][FRAME_WID];
uint8_t deathRow[FRAME_LEN * FRAME_WID][2];
uint8_t newborns[FRAME_LEN * FRAME_WID][2];
int deathRowIdx = 0;
int newbornsIdx = 0;
char *frameBuff;



int main()
{
    int frameBuffSize = (FRAME_WID + 1) * FRAME_LEN;
    frameBuff = malloc(frameBuffSize);
    frameBuff[frameBuffSize - 1] = '\0';

    gosperGliderGun_20x50();
    setup();
    int gameOn = 1;
    while(gameOn)
    {
        printBoard();
        if(!updateCells())
            gameOn = 0;
        sleep_ms(250);
        printf(CLEAR_SEQ);
    }
    printf("done ^^\n");
}




int updateCells()
{
    int liveNeighbors = 0;
    int changed = 0;
    for(int i = 0; i < FRAME_LEN; i++)
    {
        for(int j = 0; j < FRAME_WID; j++)
        {
            liveNeighbors = countLiveNeighbors(i, j);
            if((liveNeighbors < 2 || liveNeighbors > 3) && board[i][j])
            {
                changed = 1;
                deathRow[deathRowIdx][ROW] = i;
                deathRow[deathRowIdx++][COL] = j;
            }
            else if(liveNeighbors == 3 && !board[i][j])
            {
                changed = 1;
                newborns[newbornsIdx][ROW] = i;
                newborns[newbornsIdx++][COL] = j;
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
    if(i<FRAME_LEN-1 && board[i+1][j]) counter++;
    if(j>0 && board[i][j-1]) counter++;
    if(j<FRAME_WID-1 && board[i][j+1]) counter++;

    if(i>0 && j>0 && board[i-1][j-1]) counter++;
    if(i<FRAME_LEN-1 && j<FRAME_WID-1 && board[i+1][j+1]) counter++;
    if(i<FRAME_LEN-1 && j>0 && board[i+1][j-1]) counter++;
    if(i>0 && j<FRAME_WID-1 && board[i-1][j+1]) counter++;

    return counter;
}


int setup()
{
    for(int i = 0; i < FRAME_LEN; i++)
    {
        for(int j = 0; j < FRAME_WID; j++)
        {
            if(board[i][j])
                frameBuff[IJ_TO_PIXEL_NUM(i, j)] = LIVE_CHAR;
            else
                frameBuff[IJ_TO_PIXEL_NUM(i, j)] = ' ';
        }
    }
    for(int i = 0; i < FRAME_LEN-1; i++)
        frameBuff[(FRAME_WID + 1) * i + FRAME_WID] = '\n';

    return 0;
}


int lifeCycle()
{
    for(int i = 0; i < deathRowIdx; i++)
    {
        int r = deathRow[i][ROW];
        int c = deathRow[i][COL];

        board[r][c] = DEAD;
        frameBuff[IJ_TO_PIXEL_NUM(r, c)] = ' ';
        //printf("r%d c%d killed\n", r, c);
    }

    for(int i = 0; i < newbornsIdx; i++)
    {
        int r = newborns[i][ROW];
        int c = newborns[i][COL];

        board[r][c] = LIVE;
        //printf("r%d c%d born\n", r, c);
        frameBuff[IJ_TO_PIXEL_NUM(r, c)] = LIVE_CHAR;
    }

    deathRowIdx = 0;
    newbornsIdx = 0;

    return 0;
}


int printBoard()
{
    printf(frameBuff);
    return 0;
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


int gosperGliderGun_20x50()
{
    board[5][1] = LIVE;
    board[5][2] = LIVE; board[6][1] = LIVE; board[6][2] = LIVE;
    board[3][13] = LIVE; board[3][14] = LIVE; board[4][12] = LIVE;
    board[5][11] = LIVE; board[6][11] = LIVE; board[7][11] = LIVE;
    board[6][15] = LIVE; board[6][17] = LIVE; board[8][12] = LIVE;
    board[6][18] = LIVE; board[5][17] = LIVE; board[9][13] = LIVE;
    board[7][17] = LIVE; board[8][16] = LIVE; board[9][14] = LIVE;
    board[4][12] = LIVE; board[3][21] = LIVE; board[3][22] = LIVE;
    board[4][21] = LIVE; board[4][22] = LIVE; board[5][21] = LIVE;
    board[5][22] = LIVE; board[6][23] = LIVE; board[2][23] = LIVE;
    board[2][25] = LIVE; board[1][25] = LIVE; board[6][25] = LIVE;
    board[7][25] = LIVE; board[3][35] = LIVE; board[4][35] = LIVE;
    board[3][36] = LIVE; board[4][36] = LIVE; board[4][16] = LIVE;

    return 0;
}
