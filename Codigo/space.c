#include <stdio.h>
#include <stdlib.h>
#include "space.h"

struct space_{
	int sId;
	int neighbour[8];
	char *shortDesc;
	char *longDesc;
	Bool light;
	Bool isLocked; 
	/*cambio importante: aquello que hablamos de que si una habitacion estaba cerrada, lo estaba entraras desde donde 
	entraras. En vez de un array de isLocked con cada una de las posibles direcciones, 
	ahora es una propiedad de la propia habitacion (tal vez deberiamos consultarlo con el resto)
	Esto repercute en (y lo cierto es que complica un poco, aunque sigo pensando qut tal vez sea lo mas eficiente) 
	la implementacion de: isLocked y unlock*/
	char ** map;
	int rows, cols;
}Space;

/*-----------------------Funciones sin terminar-----------------------*/

int unlock(Space *s, int dir, Bool status){
	Space * spaceToUnlock = NULL;
	if(!s||dir<0||dir>7) return -1;
	spaceToUnlock = /*funcion que devuelva un puntero al space on Id s->neighbor[dir]*/
	if(!spaceToUnlock) return -1
	if(spaceToUnlock->isLocked==status) return 1;
	if(/*player no tiene la llave*/) return -2;
	spaceToUnlock->isLocked;
	return 0;
}



Space * spaceIni(){

}

void spaceFree(Space *s){

}

Bool isLocked(Space *s, int dir){
	Space * spaceToGo = NULL;
	if(!s||dir<0||dir>7) return FALSE;
	spaceToGo = /*funcion que dado un spaceId devuelva un  puntero a ese space, esta funcion debe de estar en el world creo*/
	return spaceToGo->isLocked;
}

char **whatIsInMap(Space *c, int *s){

	/*LUCIA ¿para que sirve la s?*/
}


/*------------------Funciones minigame------------------*/

int exitMgame(Space *s){
	return 0;
}

/*------------------Fuciones terminadas-----------------*/

char *sDesc(Space * s){
	if (!s) return NULL;
	return s->shortDesc;
}

char *lDesc(Space * s){
	if (!s) return NULL;
	return s->lDesc;
}

int go(Space *s, int dir){
	if (!s||sir<0||dir>7) return -1;
	if (isLocked(s, dir)==TRUE) return -2;
	return s->neighbour[dir];
}



Bool canISee(Space *s){
	if(!s) return FALSE;
	return s->light;
}

int nCols(Space *s){
	if(!s) return -1;
	return s->rows;
}

int nRows(Space *s){
	if(!s) return -1;
	return s->rows;
}

int spaceId(Space *s){
	if(!s) return -1;
	return s->sId;
}



