#include <stdio.h>
#include <stdlib.h>
#include "space.h"

#define sId(s) (s)->sId
#define neighbour[(i)](s) (s)->(neigbour[(i]))
#define shortDesc(s) (s)->shortDesc
#define longDesc(s) (s)->longDesc
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
	/*Habitacion cerrada desde todas las direcciones, deberiamos consultarlo con el resto
	Complica un poco, la implementacion de: isLocked y unlock*/
	char ** map;
	int rows, cols;
}Space;

/*-----------------------Funciones sin terminar-----------------------*/

Space * space_ini(){

}

void space_free(Space *s){

}


Bool space_isLocked(Space *s, int dir){
	Space * spaceToGo = NULL;
	if(!s||dir<0||dir>7) return FALSE;
	spaceToGo = /*funcion que dado un spaceId devuelva un  puntero a ese space, esta funcion debe de estar en el world creo*/
	/*Juan, esa funcion no es el get_Neigbour? <-- Si la implementamos para que devuelva un space* en vez de int*/
	return spaceToGo->isLocked;
}

int space_go(Space *s, int dir){
	if (!s||dir<0||dir>7) return -1;
	if (isLocked(s, dir)==TRUE) return -2;
	return s->neighbour[dir];
}

int unlock(Space *s, int dir, Bool status){

}


/*------------------Funciones minigame------------------*/

int exitMgame(Space *s){
	return 0;
}

/*------------------Fuciones terminadas-----------------*/

int space_getId(Space *s){
	if(!s) return -1;
	return sId(s);
}

Status space_setId(Space *s, int sId){
	if(!s || sId<0) /*Asumí que tiene que ser no negativo*/
		return ERROR;
	sId(s) = sId;
	return OK;
}

int space_getNeighbour( Space *s, int n);{
	if(!s || n<0 || n>7)
		return -1;
	return neighbour[n](s)
}

Status space_setNeighbour( Space *s, int n, Space *neighbour){
	if(!s || n<0 || n>7 || !neighbour)
		return ERROR;
	neighbour[n](s) = sId(neighbour);
	return OK;
}

char *space_getSDesc(Space * s){
	if (!s) return NULL;
	return shortDesc(s);
}

Status *space_setSDesc(Space * s, char *sdesc){
	if(!s || !sdesc)
		return ERROR;
	shortDesc(s) = sdesc;
	return OK;
}

char *space_getLDesc(Space * s){
	if (!s) return NULL;
	return lDesc(s);
}

Status *space_setLDesc(Space * s, char *ldesc){
	if(!s || !ldesc)
		return ERROR;
	longDesc(s) = ldesc;
	return OK;
}

char **space_getMap(Space *c){
	if(!c)
		return NULL;
	return map(c);

}

Status space_setMap(Space *c, char **map){
	if(!c || !map)
		return ERROR;
	map(c) = map;
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
/*He sacado space_go de aqui porque creo que necesitamos player.h y aclarar que ahce exactamente la funcion*/











