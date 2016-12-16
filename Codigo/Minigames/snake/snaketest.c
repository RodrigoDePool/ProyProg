#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "../../interface.h"
#include "snake.h"

int main()
{
    int sol;
    char      c;
    Interface *i;
    _term_init();
    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
    i_drawAll(i);
sleep(5);        
    sol = snake(i);

        if (sol == WIN)
        {
            i_drawStrMap(i, "Ganador", 1, 1, 3);
        }
        else
        {
            i_drawStrMap(i, "Loser", 1, 1, 3);
        }
	sleep(10);
    i_free(i);
    _term_close();
    return 1;
}
