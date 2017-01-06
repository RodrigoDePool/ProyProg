#include <stdio.h>
#include <stdlib.h>
#include "world.h"

void main(){
	World *w;
	Space **s;
	Player *p;
	Object **o;
	int i,j;
	int numobj, numspaces;
	char **buff1, **buff2;
	w = worldfromfile("world.txt");
	if(!w)
		printf("Algo falló en worldfromfile()\n");
	else{
		/*Comienzo imprimiendo los spaces*/
		numspaces = world_getNumSpaces(w);
		printf("%d\n", numspaces);
		s =  World_getSpaces(w);
		for (i = 0; i < numspaces; i++){
			printf("%d\n", space_getId(s[i]));
			for(j = 0; j<7; j++)
				printf("%d ", space_getNeighbour(s[i], j));
			printf("%d\n", space_getNeighbour(s[i], j));
		
			printf("%s\n%s\n%d\n%d\n%d %d\n",buff1 = space_getSDesc(s[i]),
							 buff2 = space_getLDesc(s[i]),
						         space_canISee(s[i]),
						         space_isLocked(s[i]),
						         space_getNRows(s[i]),
						         space_getNCols(s[i]));
						         
			for(j = 0; j<space_getNRows(s[i]); j++){
				printf("%s\n", space_getMap(s[i])[j]);
			}
			free(buff1);
			free(buff2);	
			
		}
		
		/*Ya están impresos spaces, voy a por el player*/
		p = World_getPlayer(w);
		printf("%s\n%d\n%d %d\n", buff1 = Player_getName(p),
					  Player_getSpaceid(p),
					  Player_getCoordinateX(p),
					  Player_getCoordinateY(p));
		free(buff1);
		
		/*Ahora los objects*/
		numobj = world_getNumObjects(w);
		printf("%d\n", numobj);
		o = World_getObjects(w);
		for(i = 0; i < numobj; i++){
			printf("%d\n", object_return_id(o[i]));
			printf("%s\n", buff1 = object_return_name(o[i]));
			printf("%d\n", object_return_has(o[i]));
			printf("%d\n", object_return_spaceid(o[i]));
			printf("%s\n", buff2 = object_return_desc(o[i]));
			free(buff1);
			free(buff2);
		}
		
	}
	
	/*FALLO: NO LIBERA LOS SPACES NI LOS OBJECTS ¿?*/
	world_free(w);
	return;

}

