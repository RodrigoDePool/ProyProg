#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "../../interface.h"
#include "snake.h"
#include <unistd.h>

int main()
{
  int sol;
  char      c;
  Interface *i;
  _term_init();
  i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
  do
  {
    sol = snake(i);

    if (sol == WIN)
    {
    i_drawStrMap(i, "You won", 1, 1, 3);
    }

    else
    {
      i_drawStrMap(i, "You lost", 1, 1, 3);
    }
    sleep(1);
    i_cleanMap(i);
    i_drawStrMap(i, "Quieres volver a jugar ?(s/n):", 2, 1, 3);
    do
    {
      c = _read_key();
    } while (c != 's' && c != 'S' && c != 'n' && c != 'N');
  } while (c == 's' || c == 'S');
  i_free(i);
  _term_close();
  return 1;
}
