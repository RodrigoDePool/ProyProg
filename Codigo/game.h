
#include <stdlib.h>
#include <stdio.h>
#include "world.h"


typedef struct _Strings Strings;
/* Strings file structure
 3 #nstrings
 I'm sorry, you need to have the three parts if you wanna have a clue!|
 Everything was successfuly saved.|
 Enter the solution to the riddle|

*/

/*PENSEMOS FUNCIONES*/

/*Executes help if n = 0, save if n = 1, solve if n = 2
  Returns -1 in case of error (memory error, couldnt be saved...)
  or 0 if nothing went wrong*/
int game_f(World *w, int n);
