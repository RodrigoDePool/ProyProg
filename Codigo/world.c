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
	World *w;
	assert(obj != NULL);
	assert(p != NULL);				   
	assert(space != NULL);
						   
	
	w = (World *) malloc (sizeof(World));
	if (w == NULL) return NULL;
	
	obj(w) = obj;     
	player(w) = p;    
	spaces(w) = space;
	numobj(w) = numobj;
	numspaces(w) = numspaces;
	return w;
}


	
void world_free(World *w){
	int i;	
	assert(w!=NULL);
	for(i=0; i<numobj(w);i++)
		object_free(obj(w)[i]);
	for(i=0; i<numspaces(w);i++)
		space_free(spaces(w)[i]);
	player_free(player(w));
	free(w);
	return;
}



Space *World_getSpaces(World *w, int sid){
	assert(w != NULL);
	return spaces(w)[sid];
}



int world_getNumSpaces(World *w){
	assert(w != NULL);
	return numspaces(w);
}




Object *World_getObjects(World *w, int oid){
	assert(w != NULL);
	return obj(w)[oid];
}




int world_getNumObjects(World *w){
	assert(w != NULL);
	return numobj(w);
}




Player *World_getPlayer(World *w){
	assert(w != NULL);
	return player(w);
}




	
