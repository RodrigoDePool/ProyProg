#ifndef SPACE_H
#define SPACE_H
#include "types.h"


typedef struct space_ Space;


/**************************************/
/*Ini/free and basic get/set functions*/
/**************************************/


/*Creates a new space, allocating memory, NULL in case of error*/
Space * space_ini();

/*Frees memory allocated for a space and its members*/
void space_free(Space *s);

/*Returns sId of s, -1 in  case of error*/
int space_getId(Space *s);

/*Sets sId of s, ERROR in case of error*/
Status space_setId(Space *s, int sId);

/*Returns sId of the chosen s neighbour (minigame case 4:7). -1 in case of error*/
int space_getNeighbour( Space *s, int n);

/*Sets sId of the chosen s neighbour (minigame case 4:7), ERROR in case of error*/
Status space_setNeighbour( Space *s, int n, Space *neighbour);

/*Returns short description of s, NULL in case of error*/
char *space_getSDesc(Space * s);

/*Sets short description of s, ERROR in case of error*/
Status *space_setSDesc(Space * s, char *sdesc);

/*Returns long description of s, NULL in case of error*/
char *space_getLDesc(Space * s);

/*Sets long description of s, ERROR in case of error*/
Status *space_setLDesc(Space * s, char *ldesc);

/*Returns 0 if the chosen s neigbour is unlocked, 1 if its locked*/
Bool space_isLocked(Space *s, int dir);

/*Returns char map of the specified space, NULL in case of error*/
char **space_getMap(Space *c);

/*Sets char map of the specified space, ERROR in case of error*/
Status space_setMap(Space *c, char **map);

/*Returns 0 if s is dark, 1 if not*/
Bool space_canISee(Space *s);

/*Sets s->light to TRUE/FALSE depending on "light" value. ERROR in case of error*/
Status space_setLight(Space *s, Bool light);

/*Returns number of columns of s map, -1 error*/
int space_getNCols(Space *s);

/*Sets number of columns of s map, ERROR error*/
Status space_setNCols(Space *s, int ncols);

/*Returns number of rows of s map, -1 error*/
int space_getNRows(Space *s);

/*Sets number of rows of s map, ERROR error*/
Status space_setNRows(Space *s, int nrows);

/**************************************/



/*Aqui no nos hace falta un player?*/
/*Returns sId of the space you have gone to, -1 in case of no space, -2 if locked*/
int space_go(Space *s, int dir);

/*Implementacion 8 vecinos, 4 ultimos minijuegos permite que un minijuego tenga vecinos (incluso minijuegos), que esten encendidos, 
  Tenemos que ver como tratar a los minijuegos (como structures diferentes, o que)
	Por ahora: para un minigame no podemos permitirle irse a sus vecinos (go in any directions) sino solo exit minigame*/

/*Takes the player back to the minigame "parent" space, returning parent sId, -1 in case of error*/
int exitMgame(Space *s);

/*Status tells us whether the user wants to lock or unlock door
 Returns 0 if succesfully (un)locked, -1 in case of no space, -2 if no key and 1 if it is already locked or unlocked*/
int unlock(Space *s, int dir, Bool status);


#endif
