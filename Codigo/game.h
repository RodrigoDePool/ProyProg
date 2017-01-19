
#include <stdlib.h>
#include <stdio.h>
#include "world.h"
#include "string.h"

/*Executes help if n = 0, save if n = 1, solve if n = 2
  
  Help: -1 when memory error, else 0 (even if you didnt have neough objects)
  Save: -1 if couldnt save, else 0
  Solve: 1 if won, -1 when error, 0 if wrong/ not enough objects
  */
int game_f(World *w, int n);

/*Given a world, returns how many minigames have been passed in the current level
  Returns -1 in case of error*/
int game_objInLevel(World* w);


/* Riddle starts at row 2, 
   Description at row 16*/
/* Returns 0 or -1 in case of error*/
	
int game_drawDisplay(World *w);
