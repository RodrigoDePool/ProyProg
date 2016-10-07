#ifndef SPACE_H
#define SPACE_H
#include "types.h"


typedef struct space_ Space;


/**************************************/
/*Ini/free and basic get/set functions*/
/**************************************/


/*Function: allocates memory for a space
  Returns: pointer to the space; NULL in case of error
  Revision: 7 oct 2016*/
Space * space_ini();

/*Frees memory allocated for a space (s) and its members
  Revision: 7 oct 2016*/
void space_free(Space *s);

/*Returns: sId of s, -1 in  case of error
Revision: 7 oct 2016*/
int space_getId(Space *s);

/*Function: Sets s->sId to sId
  Returns: OK/ERROR
  Revision: 7 oct 2016*/
Status space_setId(Space *s, int sId);

/*Returns: sId of the chosen s neighbour (minigame case 4:7). -1 in case of error
  Revision: 7 oct 2016*/
int space_getNeighbour(Space *s, int n);

/*Function: Sets sId of the chosen s neighbour (minigame case 4:7)
  Returns: OK/ERROR 
  Revision: 7 oct 2016*/
Status space_setNeighbour( Space *s, int n, int neighbour);

/*Returns: short description of s, NULL in case of error
  Revision: 7 oct 2016*/
char *space_getSDesc(Space * s);

/*Function: Sets short description of s
  Returns: OK/ERROR 
  Revision: 7 oct 2016*/
Status space_setSDesc(Space * s, char *sdesc);

/*Returns: long description of s, NULL in case of error
Revision: 7 oct 2016*/
char *space_getLDesc(Space * s);

/*Function: Sets long description of s to a COPY of ldesc
  Returns: OK/ERROR 
  Revision: 7 oct 2016*/
Status space_setLDesc(Space * s, char *ldesc);

/*Returns: 0 if s is unlocked, 1 if its locked*/
Bool space_isLocked(Space *s);

/*Function: locks/unlocks (depending on status) s if possible.
  status TRUE for isLocked(s)= TRUE 
  Returns: OK succesfully (un)locked/already (un)locked, ERROR in case of error
  Revision 7 oct 2016:*/
Status space_setLock(Space *s, Bool status);

/*Returns: char map of the specified space, NULL in case of error
  Revision: 7 oct 2016*/
char **space_getMap(Space *s);

/*Function: Sets char map of s to the file map
  Returns: OK/ERROR 
  Revision: 7 oct 2016*/
Status space_setMap(Space *s, char **map);

/*Returns: 0 if s is dark, 1 if not*/
Bool space_canISee(Space *s);

/*Function: Sets light(s) to TRUE/FALSE depending on "light" value
  Returns: OK/ERROR
  Revision: 7 oct 2016*/
Status space_setLight(Space *s, Bool light);

/*Returns: number of columns of s map, -1 error*/
int space_getNCols(Space *s);

/*Function: Sets number of columns of s map
  Returns: OK/ERROR */
Status space_setNCols(Space *s, int ncols);

/*Returns: number of rows of s map, -1 error
  Revision: 7 oct 2016*/
int space_getNRows(Space *s);

/*Function: Sets number of rows of s map
  Returns: OK/ERROR 
  Revision: 7 oct 2016*/
Status space_setNRows(Space *s, int nrows);

/**************************************/




/*Status tells us whether the user wants to lock or unlock door
 Returns 0 if succesfully (un)locked, -1 in case of no space, 1 if it is already locked or unlocked
 Revision: 7 oct 2016*/
int space_unlock(Space *s, int dir, Bool status);


#endif
