#include "countdots.h"
#include <time.h>
#include <unistd.h>
#define CENTERX    30
#define CENTERY    5
/*
    linear search
    -1 if error
    0 if the number is in the array
    1 if the number is not there
 */
int blin(int *buff, int num, int size)
{
    int i;
    if (buff == NULL)
        return -1;
    if (size < 1)
        return 1;
    for (i = 0; i < size; i++)
    {
        if (buff[i] == num)
            return 0;
    }
    return 1;
}

/*
    Receives the number that identifies a position and gives back the x position
    in the grid
 */
int gridXpos(int num)
{
    if (num % 3 == 1)
        return 0;
    if (num % 3 == 2)
        return 20;
    return 40;
}
/*
    Receives the number that identifies a position and gives back the y position
    in the grid
 */
int gridYpos(int num)
{
    if (num < 4)
        return 0;
    if (3 < num && num < 7)
        return 10;
    return 20;
}

/*
    Creates a random grid of points in the map oon the interface, for that
    it uses:
   +------+--------+-------+
 |   1  |    2   |   3   |
 |      |        |       |
 ||||||||||||||||||||||||||||||+------+--------+-------+
 |  4   |   5    |   6   |
 |      |        |       |
 ||||||||||||||||||||||||||||||+------+--------+-------+
 |   7  |   8    |   9   |
 |      |        |       |
 ||||||||||||||||||||||||||||||+------+--------+-------+

        Pointer to interface

        A flag (full) 1 if the array has the position of the dots to draw
        and 0 if the array has the position of the blanks spots of the grid

        An array of integers with its size. This array contains information
        about which positions should be filled with dots.
 */
void createRandomGrid(Interface *i, int *buff, int size, int full)
{
    int j;
    int draw; /*1 if you must draw and 0 if you musnt*/
    int r, x, y;

    if (i == NULL || buff == NULL || size < 0)
        return;

    for (j = 1; j < 10; j++)
    {
        /*if the array has the positions you must draw*/
        if (full == 1)
        {
            /*if the array has the position you must draw it*/
            if (blin(buff, j, size) == 0)
                draw = 1;
            else
                draw = 0;
        }
        else /*if the array has the position of the blank spots*/
        {
            if (blin(buff, j, size) == 0)
                draw = 0;
            else
                draw = 1;
        }

        if (draw == 1)
        {
            x = gridXpos(j);
            y = gridYpos(j);
            r = rand() % 3;
            /*small dot*/
            if (r == 0)
                i_readFile(i, SMALL_DOT, CENTERY + y, CENTERX + x, 1);
            /*medium dot*/
            else if (r == 1)
                i_readFile(i, MEDIUM_DOT, CENTERY + y, CENTERX + x, 1);
            else
                i_readFile(i, BIG_DOT, CENTERY + y, CENTERX + x, 1);
        }
    }
}


/*
    Returns 0 if you won the round and 1 if you lost it
 */
int countRound(Interface *i)
{
    int  full, empty, buff[10], aux, j, num;
    int  flag; /*0 for filling empty spaces 1 for filling spaces*/
    int  ans;
    char c;

    for (aux = 0; aux < 10; aux++)
    {
        buff[aux] = -1;
    }

    /*full is the amount of dots we are gonna have this round on the board*/
    /*if its bigger than 4 its easier to know we are gonna have 9-full */
    /*empty spaces*/

    full = rand() % 10;
    if (full > 4)
    {
        flag  = 0;
        empty = 9 - full;
        aux   = empty;
    }
    else
    {
        flag = 1;
        aux  = full;
    }

    /*we generate a list with aux numbers*/
    /*all numbers must be random from 1 to 9 and there must be no repetition*/
    for (j = 0; j < aux; j++)
    {
        do
        {
            num = rand() % 9 + 1;
        } while (blin(buff, num, j) == 0);
        buff[j] = num;
    }

    /*Create a random grid of points of size 30*60 and display it on interface */
    createRandomGrid(i, buff, aux, flag);
    usleep(TIME_MSECONDS * 1000);
    i_cleanMap(i);
    i_readFile(i, ROUNDINFO, 4, 4, 1);
    do
    {
        c   = _read_key();
        ans = c - '0';
    } while (ans > 9 && ans < 0);
    i_cleanMap(i);
    if (ans == full)
        return 0;
    return 1;
}

int countDots(Interface *i, int hardMode)
{
    int  j, aux, aux2;
    int  lif;
    char buff[100];
    srand(time(NULL) + clock());
    /*if the game does not fit the screen*/
    if (ROWS / 3.0 < 10 || COLS / 3.0 < 20)
    {
        return -1;
    }
    if (i == NULL)
        return -1;
    if (hardMode == 0)
    {
        lif = LIFES;
    }
    else
    {
        lif = 1;
    }
    /*We clean the interface*/
    i_cleanMap(i);
    i_cleanDisplay(i);
    i_cleanCommand(i);

    /*Set instructions on display*/
    i_readFile(i, COUNT_INST, 3, 1, 2);
    /*Set lifes on display*/
    sprintf(buff, "Lifes left: %d", lif);
    i_drawStrMap(i, buff, 1, 1, 2);

    /*Set message on the screen*/
    i_readFile(i, COUNT_INFO, 10, 10, 1);
    _read_key();
    i_cleanMap(i);

    for (j = 0, aux = 0; j < ROUNDS && lif - aux > 0; j++)
    {
        aux2 = countRound(i);
        if (aux2 == 0)
        {
            i_readFile(i, CORRECT, 3, 3, 1);
        }
        else
        {
            i_readFile(i, FAIL, 3, 3, 1);
        }
        aux = aux + aux2;
        /*We update lifes*/
        sprintf(buff, "Lifes left: %d", lif - aux);
        i_drawStrMap(i, buff, 1, 1, 2);
        /*sleep so the player can see the result of the round*/
        sleep(ROUNDTIME);
        i_cleanMap(i);
    }

    if (lif - aux > 0)
    {
        return 1;
    }
    return 0;
}

int easyCountDots(Interface *i)
{
    return countDots(i, 0);
}

int hardCountDots(Interface *i)
{
    return countDots(i, 1);
}

