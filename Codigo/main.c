#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lineread.h"
#include "interface.h"
#include "space.h"

#define MAXBUF 1000


/*
mainGame file
the mainGame should be structured in parts: animations and levels
It will be read secuentially

-To start a new level:

	L
	number of spaces
	"path to the level dir"
	#To write something on the command line:
	C Whatever

	#To write something on the display:
	D Whatever


-To start a new animation:
	A

NOTE 1: the space numbers are assinged in order of addition
			So if you add Space1 and Space2 it ID's should be 0 and 1
NOTE 2: the lines are read with fgetll, you might want to read it's documentation


*/
int main(){
	FILE * f;
	FILE * spaceFile;
	char buffer[MAXBUF], path[MAXBUF];
	int nSpaces, level = 0;
	int j;
	Space ** spaces;

	_term_init();
    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);

	f=fopen("DATA/mainGame", "r");
	
	while(1){
		if(feof(f)){
			break;
		}

		strcpy(buffer,fgetll(f));	
		switch(buffer[0]){
			/*Level*/
			case L:
				strcpy(buffer, fgetll(f));
				nSpaces = atoi(buffer);

				spaces = (Space **)malloc(sizeof(Space *) * nSpaces);
				for(j=0;j<nSpaces;j++){
					strcpy(buffer, fgetll(f));
					sprintf(path, "DATA/Levels/%d/%s.space", level, buffer);
					spaceFile = fopen(path, "r");
					spaces[j] = spacefromfile(f);

				}
				level++;
				for(j=0;j<nSpaces;j++){
					space_free(spaces[j]);
				}
				free(spaces);
				break;

			/*Animation*/
			case A:

				break;

			default:
				break;
		}
	}
	i_free(i);
    _term_close();
	fclose(f);
	return 0;
}