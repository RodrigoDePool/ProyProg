#ifndef WORLD_H
#define WORLD_H
#include <stdlib.h>
#include "types.h"
#include "space.h"
#include "object.h"
#include "interface.h"

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

/*Function: it sets an interface and frees the previous one if there was one
*
*Parameters: world and interface (already initialized)
*Returns: -1 if something went wrong and 0 if everything went right
*Revision: 6 Jan 2017
*/

int world_setInterface(World * w, Interface * i);

/*Function: it returns the interface ofthe world
*
*Parameters: world
*Revision: 6 Jan 2017
*/

Interface * world_getInterface(World * w);

/*Function: sets a path to store the world (but it does not store it)
*
*Parameters: world and path
*Returns: nothing
*Revision: 6 Jan 2017
*/

void world_setPath(World * w, char * path);

/*Function: gets the path associated with the world storage
*Parameters: world
*Returns: the path
*Revision: 6 Jan 2017
*/


char * world_getPath(World * w);

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

/*Function: adds a space to the array of spaces in the world's structure given an ID
*Parameters: world and the ID
*Returns: -1 if error and the number of spaces in the array if everything went right
*Revision: 6 Jan 2017
*/

int world_AddSpace(World * w, int ID);

/*WARNING: DANGEROUS FUNCTION, AVOID USING IT OR USE IT WISELY*/
/*Funcition: Gives back an array of objects of the world*/
/*Parameters: World *					*/
/*Return: The pointer DIRECTLY to the array of objects  */
/*DO NOT FREE THE OBJECTS			    */
Object **world_getObjects(World *w);

/*Function: gets an object from the array given the ID of it, with the object you can check if the player has it for example
*Parameters: world and id
*Returns: object
*Revision: 6 Jan 2017
*/

Object *world_getObject(World *w, int ID);

/*Function: Gives back the number of objects in the World */
/*Parameter: Pointer to World				   */
/*Return: integer with the number of objects		   */
int world_getNumObjects(World *w);

/*Function: executates the function pick (object.h) to an object
*Parameters: world and id of the object
*Returns: -1 if something went wrong and the number of objects if everything went ok
*Revision: 6 Jan 2017
*/
int world_objectPick(World * w, int ID);

/*Function: executates the function drop (object.h) to an object
*Parameters: world and id of the object
*Returns: -1 if something went wrong and the number of objects if everything went ok
*Revision: 6 Jan 2017
*/
int world_objectDrop(World * w, int ID);

/*Function: changes in the world structure the row in which the player is (only really usefull if you want to save or change map)
*Parameters: world and row
*Returns: nothing
*Revision: 6 Jan 2017
*/
void world_setPlRow(World * w, int row);

/*Function: changes in the world structure the col in which the player is (only really usefull if you want to save or change map)
*Parameters: world and Col
*Returns: nothing
*Revision: 6 Jan 2017
*/
void world_setPlCol(World * w, int Col);


/*Function: changes inthe world structure the SpaceID in which the player is (only really usefull if you want to save or change map)
*Parameters: world and SpaceID
*Returns: nothing
*Revision: 6 Jan 2017
*/
void world_setPlSpaceID(World * w, int ID);

/*Function: gets from the world structure the SpaceID in which the player is (only really usefull if you want to save or change map)
*Parameters: world
*Returns: SpaceID
*Revision: 6 Jan 2017
*/
int world_getPlSpaceID(World * w);

/*Function: gets from the world structure the row in which the player is (only really usefull if you want to save or change map)
*Parameters: world
*Returns: row
*Revision: 6 Jan 2017
*/
int world_getPlRow(World * w);

/*Function: gets from the world structure the col in which the player is (only really usefull if you want to save or change map)
*Parameters: world
*Returns: col
*Revision: 6 Jan 2017
*/
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

/*
*Function: Saves the world in a file of a given (OR NOT) path
*Parameters: the world and a path, if path was NULL the function would save it to the associated path in the world structure
*Returs: 0 if everything went right, and -1 if something went wrong
*/
int world_saveToFile(World * w, char * path);

#endif
