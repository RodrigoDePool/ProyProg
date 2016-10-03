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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
