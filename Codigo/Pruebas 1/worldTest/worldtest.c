#include <stdio.h>
#include <stdlib.h>
#include "../../world.h"

void main(){
	Interface *i;
	World * w;
    _term_init();
    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
    i_drawAll(i);
    w=worldfromfile("world_ini.txt", i);
    world_saveToFile(w, "world_new.txt");
    world_free(w);
    i_free(i);
    _term_close();
    }