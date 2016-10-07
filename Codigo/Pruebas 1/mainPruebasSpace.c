#include <stdio.h>
#include <stdlib.h>
#include "space.h"
#include "types.h"

Status PruebaS(Space * s){
	int i;
	char * c;
	i=space_getId(s)
	if(i==-1)return ERROR;
	printf("\nsId: %d", i);

}

int main(int argc, char * argv){
	Space * s = NULL;
	int i;
	s=space_ini();
	if(space_setId(s, 125)==ERROR){
		printf("Fallo en setId");
	};
	for(i=0;i<4;i++){
	if(space_setNeighbour(s, i, Space *neighbour)==ERROR)
		printf("Fallo en setNeighbour, i=%d", i);
}
	printf("\nTest: \n
			sId: 125");
	if(PruebaS(s)==OK);
		printf("Test OK");
	else printf("TEST MAL DESASTRE");

	return 0;

}