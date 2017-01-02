#ifndef WORLD_H
#define WORLD_H
#include <stdlib.h>
#include "types.h"
#include "space.h"
#include "player.h"
#include "object.h"

typedef struct _World   World;

/*Function: Initializes a World		      */
/*Parameters: you can give the function a path and an interface if you want                */
/*Returns: a World with the given data		      */
/*NOTE IMPORTANT: you dont need to give the path and the interface now,
        you can just type NULL, NULL and introduce them later*/
/*Less important note: the path will be copied, you may free your string*/

World *world_ini(char * path, Interface * i);

/*Function: frees world and ALL its variables INCLUIDING  */
/*THE ARRAY OF SPACES AND THE ARRAY OF OBJECT WHEN CREATED*/
/*THE INTERFACE WILL BE FREED TOO*/
/*Parameters: Pointer to world				  */
/*Returns: -						  */
void world_free(World *);

int world_setInterface(World * w, Interface * i);

Interface * world_getInterface(World * w);

void world_setPath(World * w, char * path);

char * world_getPath(World * w)

/*WARNING: DANGEROUS FUNCTION, AVOID USING IT OR USE IT WISELY*/
/*Funcitions: Gives back an array of spaces           */
/*The spaces in the array are placed so that each Space's index is markedby its ID*/
/*So if you want to access to the Space with ID 3, it will have index 3 in this array*/
/*Parameters: World				      */
/*Return: The pointer DIRECTLY to the array of spaces */
/*DO NOT FREE THE SPACES                  */
Space **world_getSpaces(World *w);


Space *world_getSpace(World *w, int ID);

/*Function: Gives back the number of spaces of the World*/
/*Parameters: Pointer to World				*/
/*Return: integer with the num of spaces        */
int world_getNumSpaces(World *w);

int world_AddSpace(World * w, int ID);

/*WARNING: DANGEROUS FUNCTION, AVOID USING IT OR USE IT WISELY*/
/*Funcition: Gives back an array of objects of the world*/
/*Parameters: World *					*/
/*Return: The pointer DIRECTLY to the array of objects  */
/*DO NOT FREE THE OBJECTS			    */
Object **world_getObjects(World *w);

Object *world_getObject(World *w, int ID);

/*Function: Gives back the number of objects in the World */
/*Parameter: Pointer to World				   */
/*Return: integer with the number of objects		   */
int world_getNumObjects(World *w);

int world_objectPick(World * w, int ID);

int world_objectDrop(World * w, int ID);

void world_setPlRow(World * w, int row);

void world_setPlCol(World * w, int Col);

void world_setPlSpaceID(World * w, int ID);

int world_getPlSpaceID(World * w);

int world_getPlRow(World * w);

int world_getPlCol(World * w);


/*Return: Initializes a World from a file */
/*Parameter: path to the file you want to open*/
/*FORMAT:
PlSpaceId PlRow PlCol
NumberOfSpaces
SpaceId1
SpaceId2
...
NumberOfObjects
Object1
Object2
....
*/
/*Where Pl... are the actual situation of  the player
and objects are written in the object format*/

World *worldfromfile(char *file);

int world_saveToFile(World * w, char * path);

#endif
