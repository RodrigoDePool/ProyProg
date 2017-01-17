#include <stdio.h>
#include <stdlib.h>
#include "../../world.h"


	;

void main(){
	Interface *i;
	World * w;
    FILE * f;
    _term_init();

    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
    i_drawAll(i);
    w=worldfromfile("world_ini.txt", i);
    f=fopen("Debugging", "w");
    if(world_getInterface(w)!=i)
        fprintf(f, "Error getting the interface");
    
    world_saveToFile(w, "world_new.txt");
    world_free(w);
    i_free(i);
    _term_close();
    }