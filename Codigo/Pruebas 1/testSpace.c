#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "types.h"



int main(int argc, char ** argv){
	Space * s = NULL;
	int i;
	char * string;
	char ** pstring1;
	char * pstring2[2];
	s=space_ini();
	
	if(space_setId(s, 125)==ERROR){
		printf("Fallo en setId");
	}

	if(space_getId(s)!=125){
		printf("Fallo en getId");
	}
	
	for(i=0;i<4;i++){
	if(space_setNeighbour(s, i, i)==ERROR)
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
	if(strcmp(string, "abc")!=0)	 
		printf("Fallo en getSDesc");
	free(string);
	if(space_setLDesc(s, "abcd")==ERROR) 
		printf("Fallo en setLDesc");

	string =space_getLDesc(s);

	if(strcmp(string, "abcd")!=0) 
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
		printf("Fallo en getNCols");
	pstring2[0]="abc";
	pstring2[1]="def";
	if(space_setMap(s, pstring2)==ERROR)
		printf("Fallo en setMap");



	pstring1=space_getMap(s);

	if(strcmp(pstring1[0], "abc")!=0);
		printf("Fallo en getMap");
	
	if(strcmp(pstring1[1], "def")!=0);
		printf("Fallo en getMap");

	free(pstring1[1]);
	free(pstring1[0]);
	free(pstring1);

	if(space_setLight(s, TRUE)==ERROR)
		printf("Fallo en setLight");
	if(space_canISee(s)!=TRUE)
		printf("Fallo en getLight");

	space_free(s);

	return 0;

}