#ifndef SPACE_H
#define SPACE_H
#include "types.h"
#include <stdio.h>


typedef struct space_   Space;
/*Door struct*/
typedef struct door_
{
    int x;
    int y;
    int neighbour; /*Value of the space id the door leads to*/
    /*Coords you appear in the neighbour space*/
    int nx;
    int ny;
} Door;


/**************************************/
/*Ini/free and basic get/set functions*/
/**************************************/


/*Function: allocates memory for a space
   Returns: pointer to the new space; NULL in case of error
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
   Revision: 15 oct 2016*/
Status space_setId(Space *s, int sId);



/*Returns: COPY ofshort description of s, NULL in case of error
   Revision: 7 oct 2016*/
char *space_getSDesc(Space * s);

/*Function: Sets short description of s to a COPY of sdesc
   Returns: OK/ERROR
   Revision: 15 oct 2016*/
Status space_setSDesc(Space * s, char *sdesc);

/*Returns: COPY of long description of s, NULL in case of error
   Revision: 7 oct 2016*/
char *space_getLDesc(Space * s);

/*Function: Sets long description of s to a COPY of ldesc
   Returns: OK/ERROR
   Revision: 15 oct 2016*/
Status space_setLDesc(Space * s, char *ldesc);

/*Returns: 0 if s is unlocked, 1 if its locked*/
Bool space_isLocked(Space *s);

/*Function: locks/unlocks (depending on status) s if possible.
   status TRUE for isLocked(s)= TRUE
   Returns: OK succesfully (un)locked/already (un)locked, ERROR in case of error
   Revision 15 oct 2016:*/
Status space_setLock(Space *s, Bool status);

/*Returns: NOT A COPY OF THE MAP, DON'T FREE
   char map of the specified space, NULL in case of error
   Revision: 7 oct 2016*/
char **space_getMap(Space *s);

/*Function: Sets char map of s to the input map
    IT DOES NOT COPY THE MAP DON'T FREE map
   Returns: OK/ERROR
   Revision: 15 oct 2016*/
Status space_setMap(Space *s, char **map);

/*Returns: 0 if s is dark, 1 if not*/
Bool space_canISee(Space *s);

/*Function: Sets light(s) to TRUE/FALSE depending on "light" value
   Returns: OK/ERROR
   Revision: 15 oct 2016*/
Status space_setLight(Space *s, Bool light);

/*Returns: number of columns of s map, -1 error*/
int space_getNCols(Space *s);

/*Function: Sets number of columns of s map
   Returns: OK/ERROR
   Revision: 15 oct 2016*/
Status space_setNCols(Space *s, int ncols);

/*Returns: number of rows of s map, -1 error
   Revision: 7 oct 2016*/
int space_getNRows(Space *s);

/*Function: Sets number of rows of s map
   Returns: OK/ERROR
   Revision: 15 oct 2016*/
Status space_setNRows(Space *s, int nrows);

/*
    Function: Sets the number of doors of a space
    Return: OK/ERROR
    num>=0
 */
Status space_setNDoors(Space *s, int num);

/*
    Function:
    Return: returns the number of doors of an space or -1 if not intialized
 */
int space_getNDoors(Space *s);

/*
    Function: sets the n door of the space to the given x and y
            the door will lead to the sId (space id) specified
            , (nx,ny) are the coords you appear in the neighbour space
    NOTE: THE FIRST DOOR IS DOOR 0(ZERO)
    Return: OK/ERROR
    cases of error:
        x<0, y<0, n>=number of doors
 */
Status space_setDoor(Space *s, int n, int x, int y, int sId, int nx, int ny);

/*
    Function: checks if in the point (x,y) of the space there is a door
    Return:
        NULL if there is no door
        Door * with the info in case there is a space there
    NOTE: DO NOT FREE THE DOOR GIVEN
 */
Door *space_checkDoorPoint(Space *s, int x, int y);

/*
    Function: does the same as space_checkDoorPoint but instead of looking
            at the point given it looks at the points up,down,right and left
            of the given one
    Returns:
        NULL if there is no door
        Door * with the info in case there is a space there
        NOTE: DO NOT FREE THE DOOR GIVEN
 */
Door *space_checkDoorAPoint(Space *s, int x, int y);
/**************************************/




/*Status tells us whether the user wants to lock or unlock door
   Returns 0 if succesfully (un)locked, -1 in case of no space, 1 if it is already locked or unlocked
   Revision: 7 oct 2016*/
int space_unlock(Space *s, int dir, Bool status);

/*Returns: initializes and sets space from the file

   FORMAT:

    ID
    Number of doors
    <x coord of door> <y coord of door> <sID of destiny> <destiny x> <destiny y>
    <x coord of door> <y coord of door> <sID of destiny> <destiny x> <destiny y>
    ...
    <x coord of door> <y coord of door> <sID of destiny> <destiny x> <destiny y>
    <Short desc>
    <Long desc>
    <Light>
    <Lock>
    <path to file with map that should look like this:

      <NRows> <NCols>
          <map itself>
   >
   Revision: 26 dic 2016
 */

Space * spacefromfile(FILE * f);

/*Returns: initializes and sets map from the file
   Parameters: Pointer to file must be in the first character of the
   map.
   ncols>0
   nrows>0
   Revision: 13 oct 2016
 */
char ** mapfromfile(FILE * f, int nrows, int ncols);

#endif
