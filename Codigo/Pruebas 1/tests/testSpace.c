#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "types.h"



int main(int argc, char ** argv){
	Space * s = NULL;
	int i;
	char * string=NULL;
	char ** pstring1=NULL;
	char ** pstring2=NULL;
	s=space_ini();
	
	if(space_setId(s, 125)==ERROR){
		printf("\nFallo en setId");
	}

	if(space_getId(s)!=125){
		printf("\nFallo en getId");
	}
	
	for(i=0;i<4;i++){
	if(space_setNeighbour(s, i, i)==ERROR)
		printf("\nFallo en setNeighbour, i=%d", i);
	}

	for(i=0;i<4;i++){
		if(space_getNeighbour(s, i)!=i){
			printf("\nFallo en getNeihbour, u=%d", i);
		}
	}

	if(space_setSDesc(s, "abc")==ERROR) 
		printf("\nFallo en setSDesc");
	string =space_getSDesc(s);
	if(strcmp(string, "abc")!=0)	 
		printf("\nFallo en getSDesc");
	free(string);
	if(space_setLDesc(s, "abcd")==ERROR) 
		printf("\nFallo en setLDesc");

	string =space_getLDesc(s);

	if(strcmp(string, "abcd")!=0) 
		printf("\nFallo en getLDesc");
	
	free(string);
	if(space_setLock(s, TRUE)==ERROR)
		printf("\nFallo en setLock");

	if(space_isLocked(s)==FALSE)
		printf("\nFallo en isLocked");

	if(space_setNRows(s, 2)==ERROR)
		printf("\nFallo en setNRows");

	if(space_setNCols(s, 3)==ERROR)
		printf("\nFallo en setNCols");

	if(space_getNRows(s)!=2)
		printf("\nFallo en getNRows");

	if(space_getNCols(s)!=3)
		printf("\nFallo en getNCols");
	pstring2=(char**)malloc(sizeof(char*)*2);
	pstring2[0]=NULL;
	pstring2[1]=NULL;
	pstring2[0]=(char*)malloc(sizeof(char)*4);
	pstring2[1]=(char*)malloc(sizeof(char)*4);

	pstring2[0][0]='a';
	pstring2[0][1]='b';
	pstring2[0][2]='c';
	pstring2[0][3]='\0';
	pstring2[1][0]='d';
	pstring2[1][1]='e';
	pstring2[1][2]='f';
	pstring2[1][3]='\0';
	if(space_setMap(s, pstring2)==ERROR)
		printf("\nFallo en setMap");



	pstring1=space_getMap(s);

	if(!(pstring1[0][0]=='a'&&
	pstring1[0][1]=='b'&&
	pstring1[0][2]=='c' &&
	pstring1[0][3]=='\0' &&
	pstring1[1][0]=='d' &&
	pstring1[1][0]=='d'&&
	pstring1[1][1]=='e'&&
	pstring1[1][2]=='f'&&
	pstring1[1][3]=='\0'))
		printf("Fallo en getMap");

	if(space_setLight(s, TRUE)==ERROR)
		printf("\nFallo en setLight");
	if(space_canISee(s)!=TRUE)
		printf("\nFallo en getLight");
	printf("\nSi no hay errores OK");
	space_free(s);

	return 0;

}