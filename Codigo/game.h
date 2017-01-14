
#include <stdlib.h>
#include <stdio.h>
#include "world.h"



/*PENSEMOS FUNCIONES*/


/*Gives a clue to the space riddle if the player has all the space objects
  Else, tells the player that he cannot be helped
  Returns -1 if anything went wrong*/
int game_help(World *w);

/*Saves the game and shows message
  Returns¿?*/
int game_save(World *w);

int game_exit(World *w);

