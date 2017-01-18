#ifndef WORLD_H
#define WORLD_H
#include <stdlib.h>
#include "types.h"
#include "space.h"
#include "interface.h"
/*#include "/Minigames/2048/2048.h"*/
/*#include "/Minigames/Calculo Rapido/"*/
/*#include "/Minigames/MiniMaze/MiniMaze.h"*/
/*#include "/Minigames/MiniPadel/miniPadel.h"*/
/*#include "/Minigames/MiniRPSLS/miniRPSLS.h"*/
/*#include "/Minigames/preguntas"*/
/*#include "/Minigames/snake/snake.h"*/
/*NOTE: if you change the next two defines you need to change their initialization functions in world.c*/
#define numMinigames        20
#define numLevels           4
#define SPACE_PATHS_FILE    "SpacePaths"
#define SOLUTIONS_PATH "Solutions"

/*The Spaces paths must be in a file with the SPACE_PATHS_FILE path*/

typedef struct _World   World;

/*Function: Initializes a World		      */
/*Parameters: you can give the function a path and an interface if you want                */
/*Returns: a World with the given data		      */
/*NOTE IMPORTANT: you dont need to give the path and the interface now,
        you can just type NULL, NULL and introduce them later*/
/*Less important note: the path will be copied, you may free your string*/

typedef int (*Minigame)(Interface * i);
typedef int (*Animation)(Interface * i);

typedef struct _Level
{
    char      * solution;
    Animation * initialAnimation;
    Animation * finalAnimation;
    /*Initial coords*/
    int       PlIniRow;
    int       PlIniCol;
    int       PlIniSpaceID;
}Level;


World *world_ini(char * path, Interface * i);

/*Function: frees world and ALL its variables */
/*THE INTERFACE WILL NOT BE FREED*/
/*Parameters: Pointer to world				  */
/*Returns: -						  */
void world_free(World *);

/*Function: it sets an interface and frees the previous one if there was one
 *
 ***Parameters: world and interface (already initialized)
 ***Returns: -1 if something went wrong and 0 if everything went right
 ***Revision: 6 Jan 2017
 */

int world_setInterface(World * w, Interface * i);

/*Function: it returns the interface ofthe world
 *
 ***Parameters: world
 ***Revision: 6 Jan 2017
 */

Interface * world_getInterface(World * w);

/*Function: sets a path to store the world (but it does not store it)
 *
 ***Parameters: world and path
 ***Returns: nothing
 ***Revision: 6 Jan 2017
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

/*Function: gets the Map of a spacewith an ID
   *Parameters: world and the ID
   *Returns: NULL if something went wrong or the Map  if OK
   *Revision: 6 Jan 2017
 */

char ** world_getSpaceMap(World * w, int SpaceID);

/*Function: Gives back the number of objects in the World */
/*Parameter: Pointer to World				   */
/*Return: integer with the number of objects		   */
int world_getNumObjects(World *w);

/*
    Function: Sets the value numObjects in the world
    Parameter: Pointer to world, integer
 */
void world_setNumObjects(World *w, int num);

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

/*Function: changes in the world structure the col androw in which the player is (only really usefull if you want to save or change map)
   *Parameters: world, Col adn row
   *Returns: nothing
   *Revision: 6 Jan 2017
 */
void world_setPlCoords(World * w, int row, int Col);

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
 */
/*Where Pl... are the actual situation of  the player
   and objects are written in the object format*/

World *worldfromfile(char *file, Interface * i);

/*
   *Function: Saves the world in a file of a given (OR NOT, KEEP READING) path
   *Parameters: the world and a path, if path was NULL the function would save it to the associated path in the world structure
   *Returs: 0 if everything went right, and -1 if something went wrong
 */
int world_saveToFile(World * w, char * path);

/*
   *Function: To know if the id corresponds to a minigame or a space
   *Parameters: the ID
   *Returs: 0 = Space ; 1 = Minigame ; -1 = ERROR
 */
int isItASpaceOrAMinigame(int ID);

/*
   *Function: gets a minigame given an ID
   *Parameters: the world and the ID
   *Returs: NULL = Error ; anyithing else will be the minigame pointer
 */
Minigame * world_getMinigame(World * w, int ID);

/*
   *Function: gets a level given a level number (ID)
   *Parameters: the world and the ID
   *Returs: NULL = Error ; anyithing else will be the level pointer
 */

Level * world_getLevel(World * w, int ID);

#endif
