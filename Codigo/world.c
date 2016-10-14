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



Space **World_getSpaces(World *w){
	assert(w != NULL);
	return spaces(w);
}



int world_getNumSpaces(World *w){
	assert(w != NULL);
	return numspaces(w);
}




Object **World_getObjects(World *w){
	assert(w != NULL);
	return obj(w);
}




int world_getNumObjects(World *w){
	assert(w != NULL);
	return numobj(w);
}




Player *World_getPlayer(World *w){
	assert(w != NULL);
	return player(w);
}


World *worldfromfile(char *file){
	assert(file!=NULL);
	FILE *f;
	int i,j;
	int numspaces;
	Space **spaces;
	Player *player;
		
	f=fopen(file,"r");
	if(f==NULL) return NULL;
	fscanf("%d\n",&numspaces);
	spaces=(Space **)malloc(sizeof(Space *)*numspaces);
	if(spaces==NULL) return NULL;

	for(i=0;i<numspaces;i++){
		spaces[i]=spacefromfile(f);
		if(spaces[i]==NULL){
			for(j=i;j>=0;j--){
				space_free(spaces[j]);			
			}
			free(spaces);
			return NULL;
		}
	}
	
	player=player_fromFile(f);
	/*Falta terminarlo!!!*/

}


	
