#include "world.h"
#define NDEBUG
#include <stdlib.h>
#include <assert.h>
#define spaces(w) (w)->spaces
#define numspaces(w) (w)->numspaces
#define obj(w) (w)->objects
#define numobj(w) (w)->numobjects
#define player(w) (w)->player

struct _World{
	Space **spaces;
	int numspaces;
	Object **objects;
	int numobjects;
	Player *player;
};

World *world_ini(Object **obj, Player *p, Space **space, int numobj, int numspaces){ 
	assert(obj != NULL);				   /*Since the player, the objects and the spaces are fixed*/
	assert(p != NULL);				   /*we can just initialize the values right here          */
	assert(space != NULL);
	World *w;					   
	
	w = (World *) malloc (sizeof(World));
	if (w == NULL) return NULL;
	
	obj(w) = obj;     /*We can just asign the pointers because we wont use the full array of objects or the*/
	player(w) = p;    /*full array of spaces anywhere else out of the world structure                      */
	spaces(w) = space;
	numobj(w) = numobj;
	numspaces(w) = numspaces;
	return w;
}
	
Space **World_getSpaces(World *w){
	assert(w != NULL);
	
	Space **s = (Spaces**) malloc(numspaces(w)*sizeof(Space));
	if (s == NULL) return NULL;
	
	s = spaces(w);
	
	return s;
}

int world_getNumSpaces(World *w){
	assert(w != NULL);
	
	return numspaces(w);
}

Object **World_getObjects(World *w){
	assert(w != NULL);
	
	Object **o = (Object**) malloc(numobj(w)*sizeof(Object));
	if (s == NULL) return NULL;
	
	o = obj(w);
	
	return o;
}

int world_getNumObjects(World *w){
	assert(w != NULL);
	
	return numobj(w);
}

Player *World_getPlayer(World *w){
	assert(w != NULL);
	
	Player *p = (Player*) malloc(sizeof(Player));
	
	p = player(w);
	
	return p;
}
	
