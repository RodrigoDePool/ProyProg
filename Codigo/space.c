#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
/*#define NDEBUG*/
#include <assert.h>


#define sId(s) (s)->sId
#define neighbour(s) s->neighbour
#define sDesc(s) (s)->shortDesc
#define lDesc(s) (s)->longDesc
#define light(s) (s)->light
#define isLocked(s) (s)->isLocked
#define map(s) (s)->map
#define rows(s) (s)->rows
#define cols(s) (s)->cols
#define MAX_L_DESC 1000
#define MAX_S_DESC 10

struct space_{
	int sId;
	int neighbour[8];
	char *shortDesc;
	char *longDesc;
	Bool light;
	Bool isLocked; 
	char ** map;
	int rows, cols;
};




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
	sDesc(s) = NULL;
	lDesc(s) = NULL;
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
	if(sDesc(s))
		free (sDesc(s));
	if(lDesc(s))
		free (lDesc(s));
	if(map(s)){
		for(i = 0; i < rows(s); i++){
			if(map(s)[i]) free (map(s)[i]);
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

int space_getNeighbour(Space *s, int n){
	if(!s || n<0 || n>7)
		return -1;
	return neighbour(s)[n];
}

Status space_setNeighbour(Space *s, int n, int neighbour){
	if(!s || n<0 || n>7 || !neighbour)
		return ERROR;
	if(neighbour(s)[n] == -1)
		neighbour(s)[n]	 = neighbour;
	return OK;
}

char *space_getSDesc(Space * s){
	char* description=NULL;
	if (!s) return NULL;
	description=strdup(sDesc(s));
	return description;
}

Status space_setSDesc(Space * s,char *sdesc){
	if(!s || !sdesc)
		return ERROR;
	if(!sDesc(s))
		 sDesc(s) = strdup(sdesc);
	return OK;
}

char *space_getLDesc(Space * s){
	if (!s) return NULL;
	return strdup(sDesc(s));
}

Status space_setLDesc(Space * s, char *ldesc){
	if(!s || !ldesc)
		return ERROR;
	if(!lDesc(s))
		lDesc(s) = strdup(ldesc);
	return OK;
}

Bool space_isLocked(Space *s){
	if(!s) return FALSE;
	return isLocked(s);
}

Status space_setLock(Space *s, Bool status){
	if(!s)
		return ERROR;
	if(status != isLocked(s))
		isLocked(s) = status;
	return OK;
}

char **space_getMap(Space *s){
	if(!s)
		return NULL;
	return map(s);
}

Status space_setMap(Space *s, char **map){
	if(!s || !map)
		return ERROR;
	/*Asumo que map tiene las dimensiones especificadas por cols, rows*/
	map(s) =  map;
	return OK;
}

Bool space_canISee(Space *s){
	if(!s) return FALSE;
	return light(s);
}

Status space_setLight(Space *s, Bool light){
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




char ** mapfromfile(FILE * f, int nrows, int ncols){
	assert(nrows>0);
	assert(ncols>0);
	asser(f!=NULL);
	char **map;
	int i,j;

	map=(char **)malloc(sizeof(char *)*nrows);
	if(map==NULL) return NULL;
	for(i=0;i<nrows;i++){
		map[i]=(char *)malloc(sizeof(char)*ncols);
		if(map[i]==NULL){/*lack of memory*/		
			for(j=i-1;j>=0;j--){
				free(map[j]);
			}
			free(map);
			return NULL;
		}
	}
	
	for(i=0;i<nrows;i++){
		fgets(map[i],ncols+1,f);		
	}

	return map;
}




