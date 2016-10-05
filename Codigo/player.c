#include "player.h"
#define NDEBUG
#include <assert.h>
#include <string.h>
#define name(p) (p)->name
#define spaceid(p) (p)->spaceid
#define x(p) (p)->coordx
#define y(p) (p)->coordy

struct _Player{
	char *name;
	int spaceid;
	int coordx;
	int coordy;
};

Player *player_ini(){
	Player *p;
	
	p = (player*) malloc(sizeof(Player));
	if(p == NULL) return NULL;
	
	name(p) = NULL;
	spaceid(p) = 0;
	x(p) = 0;
	y(p) = 0;
	
	return p;
}

void player_free(Player *p){
	assert (p != NULL);
	
	if (name(p) != NULL) free(name(p));
	
	free(p);
}

Status *Player_setName(Player *p, char *name){
	assert (p != NULL);
	assert (name != NULL);
	
	if (name(p) != NULL) free(name(p));
	
	name(p)=(char *)malloc(sizeof(char)*(1+strlen(name)));
	if(name(p)==NULL) return ERROR;
	
	name(o)=strcpy(name(o),name);
	
	return OK;
}

Char *Player_getName(Player *p){
	assert (p != NULL);
	assert (name(p) != NULL);
	
	return name(p);
}

Status *Player_setSpaceid(Player *p, int id){
	assert (p != NULL);
	assert (id > 0); /*Just greater or grater or equal?*/
	
	spaceid(p) = id;
	
	return OK;
}

int Player_getSpaceid(Player *p){
	assert (p != NULL);
	
	return spaceid(p);
}

Status *Player_setCoordinateX(Player *p, int x){
	assert (p != NULL);
	assert (x > 0); /*Just greater or greater or equal?*/
	
	x(p) = x;
	
	return OK;
}

int Player_getCoordinateX(Player *p){
	assert (p != NULL);
	
	return x(p);
}

Status *Player_setCoordinateY(Player *p, int y){
	assert (p != NULL);
	assert (y > 0); /*Just greater or greater or equal?*/
	y(p) = y;
	return OK;
}

int Player_getCoordinateY(Player *p){
	assert (p != NULL);
	return y(p);
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
