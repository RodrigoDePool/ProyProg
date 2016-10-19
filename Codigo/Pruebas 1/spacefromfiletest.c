#include <stdio.h>
#include "space.h"

void main(char **file){
	FILE *f;
	Space *s;
	int i;
	
	f = fopen(file, "r");
	s = spacefromfile(f);
	if(!s)
		printf("Algo salió mal");
	else
		printf("%d\n", space_getId(s));
		for(i = 0; i<7; i++)
			printf("%d ", space_getNeighbour(s, i);
		printf("%d\n", space_getNeighbour(s, i);
		
		printf("%s\n%s\n%d\n%d\n%d %d\n", space_getSDesc(s), space_getLDesc(s), 
		      space_canISee(s), space_isLocked(s), space_getNRows(s); 
		      space_getNCols(s));
		for(i = 0; i<nrows; i++){
			printf("%s\n", space_getMap(s)[i]);
		}
	space_free(s);
	fclose(f);
	return;
}

