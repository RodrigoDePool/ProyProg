#include "countdots.h"
#include <time.h>

/*
    Returns 0 if you won the round and 1 if you lost it
 */
int countRound(Interface *i)
{
}

int countDots(Interface *i, int hardMode)
{
    int  i, aux;
    char buff[100];
    srand(time(NULL) + clock());

    if (i == NULL)
        return -1;

    /*We clean the interface*/
    i_cleanMap(i);
    i_cleanDisplay(i);
    i_cleanCommand(i);

    /*Set instructions on display*/
    i_readFile(i, COUNT_INST, 3, 1, 2);
    /*Set lives on display*/
    sprintf(buff, "Lives left: %d", LIVES);
    i_drawStrMap(i, buff, 1, 1, 2);

    /*Set message on the screen*/
    i_readFile(i, COUNT_INFO, 10, 10, 1);
    _read_key();

    for (i = 0, aux = 0; i < ROUNDS && LIVES - aux < 1; i++)
    {
        aux = aux + countRound(i);

        /*We update lives*/
        sprintf(buff, "Lives left: %d", LIVES - aux);
        i_drawStrMap(i, buff, 1, 1, 2)
    }

    if (LIVES - aux < 1)
    {
        return 0;
    }
    return 1;
}