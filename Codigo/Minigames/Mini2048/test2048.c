#include "2048.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    Interface *i;
    int       won;

    _term_init();
    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
    if (!i)
        return -1;
    i_drawAll(i);
    won = mini2048(i, "./data/numbers.txt", 4);
    sleep(2);
    i_free(i);
    _term_close();
    return won;
}
