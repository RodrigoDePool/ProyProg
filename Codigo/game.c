
#define NDEBUG
#include <assert.h>
#include "game.h"

int game_help(World *w){
	assert(w);
	Interface *in = world_getInterface(w);
	if(!in) return -1;
}


int game_save(World *w);
