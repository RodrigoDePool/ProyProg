#include "animations.h"
#include "../interface.h"
#include <unistd.h>

int main(){
	Interface *i;
  _term_init();
  i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
 
  i_readFile(i, "../Maps/CorridorLeft.map", 0, 0, 1);
  i_drawAll(i);
  
  i_drawPl(i, 18, 11);
  One2Two_animation(i);
  sleep(1);

  i_drawPl(i, 8, 81);
  Two2Three_animation(i);
  sleep(1);
  
  i_drawPl(i, 27, 43);
  Three_animation_LucyFight(i);
  sleep(1);
  
  Three2Four_animation(i);
  sleep(1);

  Four_animation_call1 (i);
  sleep(1);

  Four_animation_call2 (i);
  sleep(1);

  Four_animation_call3 (i);
  sleep(1);

  i_free(i);
  _term_close();
  return 1;
}
