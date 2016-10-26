#include <stdio.h>
#include <stdlib.h>
#include "space.h"

void main(){
	FILE *f;
	Space *s;
	int i;
	char *buff1, *buff2;
	
	f = fopen("spacetest.txt", "r");
	s = spacefromfile(f);
	if(!s)
		printf("Algo salió mal");
	else{
		printf("%d\n", space_getId(s));
		for(i = 0; i<7; i++)
			printf("%d ", space_getNeighbour(s, i));
		printf("%d\n", space_getNeighbour(s, i));
		
		printf("%s\n%s\n%d\n%d\n%d %d\n", buff1 = space_getSDesc(s), buff2 = space_getLDesc(s), 
		      space_canISee(s), space_isLocked(s), space_getNRows(s),
		      space_getNCols(s));
		for(i = 0; i<space_getNRows(s); i++){
			printf("%s\n", space_getMap(s)[i]);
		}
		free(buff1);
		free(buff2);
		space_free(s);
	}

	s = spacefromfile(f);
	if(!s)
		printf("Algo salió mal");
	else{
		printf("%d\n", space_getId(s));
		for(i = 0; i<7; i++)
			printf("%d ", space_getNeighbour(s, i));
		printf("%d\n", space_getNeighbour(s, i));
		
		printf("%s\n%s\n%d\n%d\n%d %d\n", buff1 = space_getSDesc(s), buff2 = space_getLDesc(s), 
		      space_canISee(s), space_isLocked(s), space_getNRows(s),
		      space_getNCols(s));
		for(i = 0; i<space_getNRows(s); i++){
			printf("%s\n", space_getMap(s)[i]);
		}
		free(buff1);
		free(buff2);
		space_free(s);
	}
	fclose(f);
	return;
}
