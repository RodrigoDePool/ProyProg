
#include <stdlib.h>
#include <stdio.h>
#include "world.h"


typedef struct _Strings Strings;

/*Initializes and returns String struct from a file like this (# is the separator):

  RIGHT NOW IT INITIALIZES IT FROM A MACRO: STRPATH

 3 --nstrings
 I'm sorry, you need to have the three parts if you wanna have a clue!#
 
 Everything was successfuly saved.#
 
 Enter the solution to the riddle#
 
*/
String *string_ini(char *path);

/* Frees a given string and all its members*/
void string_free(String *s);

/*Returns the number of strings in a struct, or -1 in case of error*/
int string_getNumber(String *s);

/*Executes help if n = 0, save if n = 1, solve if n = 2
  
  Help: -1 when memory error, else 0 (even if you didnt have neough objects)
  Save: -1 if couldnt save, else 0
  Solve: 1 if won, -1 when error, 0 if wrong/ not enough objects
  */
int game_f(World *w, int n);

/*Given a world, returns how many minigames have been passed in the current level
  Returns -1 in case of error*/
int game_objInLevel(World* w);
