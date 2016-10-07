#include <stdio.h>
#include <stdlib.h>
#include "space.h"
#include "types.h"



int main(int argc, char * argv){
	Space * s = NULL;
	int i;
	char * string;
	char ** pstring
	s=space_ini();
	
	if(space_setId(s, 125)==ERROR){
		printf("Fallo en setId");
	}

	if(space_getId(s)!=125){
		printf("Fallo en getId");
	}
	
	for(i=0;i<4;i++){
	if(space_setNeighbour(s, i, Space *neighbour)==ERROR)
		printf("Fallo en setNeighbour, i=%d", i);
	}

	for(i=0;i<4;i++){
		if(space_getNeighbour(s, i)!=i){
			printf("Fallo en getNeihbour, u=%d", i);
		}
	}

	if(space_setSDesc(s, "abc")==ERROR) 
		printf("Fallo en setSDesc");
	string =space_getLDesc(s);
	if(string!="abc")	 
		printf("Fallo en getSDesc");
	free(string);
	if(space_setLDesc(s, "abcd")==ERROR) 
		printf("Fallo en setLDesc");

	string =space_getLDesc(s);

	if(string!="abcd") 
		printf("Fallo en getLDesc");
	
	free(string);
	if(space_setLock(s, TRUE)==ERROR)
		printf("Fallo en setLock");

	if(space_isLocked(s)==FALSE)
		printf("Fallo en isLocked");

	if(space_setNRows(s, 2)==ERROR)
		printf("Fallo en setNRows");

	if(space_setNCols(s, 3)==ERROR)
		printf("Fallo en setNCols");

	if(space_getNRows(s)!=2)
		printf("Fallo en getNRows");

	if(space_getNCols(s)!=3)
		printf("Fallo en getNCols")
	if(space_setMap(s, {{'a', 'b', 'c'}, {'d', 'e', 'f'}})==ERROR)
		printf("Fallo en setMap");

	pstring=space_getMap(s);

	if(pstring!={{'a', 'b', 'c'}, {'d', 'e', 'f'}})
		printf("Fallo en getMap");
	
	free(pstring[1]);
	free(pstring[0]);
	free(pstring);

	

	return 0;

}