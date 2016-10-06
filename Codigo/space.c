#include <stdio.h>
#include <stdlib.h>
#include "space.h"


#define sId(s) (s)->sId
#define neighbour(s) s->neighbour
#define sDesc(s) (s)->shortDesc
#define lDesc(s) (s)->longDesc
#define light(s) (s)->light
#define isLocked(s) (s)->isLocked
#define map(s) (s)->map
#define rows(s) (s)->rows
#define cols(s) (s)->cols

struct space_{
	int sId;
	int neighbour[8];
	char *shortDesc;
	char *longDesc;
	Bool light;
	Bool isLocked; 
	char ** map;
	int rows, cols;
}Space;

/*-----------------------Funciones sin terminar-----------------------*/



Bool space_isLocked(Space *s, int dir){
	Space * spaceToGo = NULL;
	if(!s||dir<0||dir>7) return FALSE;
	spaceToGo =
	return spaceToGo->isLocked;
}





/*------------------Funciones minigame------------------*/

int exitMgame(Space *s){
	return 0;
}

/*------------------Fuciones terminadas-----------------*/


Space * space_ini(){
	int i;
	Space *s;
	s = (Space *) malloc (sizeof(Space));
	if(!s)
		return NULL;
	sId(s) = -1;
	for(i = 0; i < 7; i++)
		neighbour(s)[i] = -1;
	shortDesc(s) = NULL;
	longDesc(s) = NULL;
	light(s) = FALSE;
	isLocked(s) = FALSE;
	map(s) = NULL;
	rows(s) = -1;
	cols(s) = -1;
	return s;

}

void space_free(Space *s){
	int i;
	if(!s)
		return;
	if(shortDesc(s))
		free (shortDesc(s));
	if(longDesc(s))
		free (longDesc(s));
	if(map(s)){
		for(i = 0; i < rows(s), i++){
			if(map(s)[i]) free map(s)[i];
		}
		free(map(s));
	}
}

int space_getId(Space *s){
	if(!s) return -1;
	return sId(s);
}

Status space_setId(Space *s, int sId){
	if(!s || sId<0) 
		return ERROR;
	sId(s) = sId;
	return OK;
}

int space_getNeighbour(Space *s, int n);{
	if(!s || n<0 || n>7)
		return -1;
	return neighbour[n](s)
}

Status space_setNeighbour(Space *s, int n, Space *neighbour){
	if(!s || n<0 || n>7 || !neighbour)
		return ERROR;
	neighbour[n](s) = sId(neighbour);
	return OK;
}

char *space_getSDesc(Space * s){
	char* description=NULL;
	if (!s) return NULL;
	description=strdup();
	return sDesc(s);
}

Status *space_setSDesc(Space * s, char *sdesc){
	if(!s || !sdesc)
		return ERROR;
	sDesc(s) = strdup(sdesc);
	return OK;
}

char *space_getLDesc(Space * s){
	if (!s) return NULL;
	return lDesc(s);
}

Status *space_setLDesc(Space * s, char *ldesc){
	if(!s || !ldesc)
		return ERROR;
	lDesc(s) = strdup(ldesc);
	return OK;
}

Status space_setLock(Space *s, Bool status){
	if(!s)
		return ERROR;
	if(status != isLocked(s))
		isLocked(s) = status;
	return OK;
}

char **space_getMap(Space *c){
	if(!c)
		return NULL;
	return map(c);
}

Status space_setMap(Space *c, char **map){
	int i, j;
	char **copy;
	if(!c || !map)
		return ERROR;
	/*Asumo que map tiene las dimensiones especificadas por cols, rows*/
	copy = (char **)malloc(rows(c) * sizeof(char*));
	if(!copy)
		return ERROR;
	for (i = 0; i<rows(c); i++){
		copy[i] = strdup(map[i]);
		if(!copy[i]){
			for (j = 0; j<i; j++)
				free(copy[j]);
			return ERROR;
		}	
	}
	map(c) = copy;
	return OK;
}

Bool space_canISee(Space *s){
	if(!s) return FALSE;
	return light(s);
}

Status space_setLight(space *s, Bool light){
	if(!s)
		return ERROR;
	light(s) = light;
	return OK;
}

int space_getNCols(Space *s){
	if(!s) return -1;
	return cols(s);
}

Status space_setNCols(Space *s, int ncols){
	if(!s || ncols<1)
		return ERROR;
	cols(s) = ncols;
	return OK;
}

int space_getNRows(Space *s){
	if(!s) return -1;
	return rows(s);
}

Status space_setNRows(Space *s, int nrows){
	if(!s || nrows<1)
		return ERROR;
	rows(s) = nrows;
	return OK;
}









