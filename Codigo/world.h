#ifndef WORLD_H
#define WORLD_H
#include <stdlib.h>
#include "types.h"
#include "space.h"
#include "player.h"
#include "object.h"

typedef struct _World World;


/*Function: Initializes a World given a Player, an    */
/*array of objects, an array of spaces, number of objs*/
/*and number of spaces				      */
/*Parameters: explained above 			      */
/*Returns: a World with the given data		      */
/*COMMENT: THE ARRAY OF OBJECTS AND THE ARRAY OF SPACES*/
/*IS NOT COPIED AND WILL BE FREED IN WORLD FREE	      */
World *world_ini(Object **obj, Player *p, Space **space, int numobj, int numspaces);



/*Function: frees world and ALL its variables INCLUIDING  */
/*THE ARRAY OF SPACES AND THE ARRAY OF OBJECT WHEN CREATED*/
/*Parameters: Pointer to world				  */
/*Returns: -						  */
void world_free(World *);



/*Funcitions: Gives back a space given the spaceid*/
/*Parameters: World and int>0 which is the spaceid*/
/*Return: The pointer DIRECTLY to the space asked */
Space *World_getSpace(World *w, int sid);


/*Function:*/
/*Parameters:*/
/*Return: */
int world_getNumSpaces(World *w);

Object **World_getObjects(World *w);

int world_getNumObjects(World *w);

Player *World_getPlayer(World *w);

#endif
