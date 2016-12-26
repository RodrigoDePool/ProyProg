#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lineread.h"
#include "interface.h"

#define MAXBUF 1000

/*
mainGame file
the mainGame should be structured in parts: animations and levels
It will be read secuentially

-To start a new level:

	L
	Name of the space [(Coord y of door 1, Coord x of door 1, Space or 
	minigame number, Start Coord y in the new space, Start Coord x in the new space) 
	(Coord y of ...)...] EOL Name of another space [(...)] EOL ... EOL ends EOL

	#To write something on the command line:
	C Whatever

	#To write something on the display:
	D Whatever


-To start a new animation:
	A

NOTE 1: the space numbers are assinged in order of addition
NOTE 2: the lines are read with fgetll, you might want to read it's documentation


*/
int main(){
	FILE * f;
	char buffer[MAXBUF];
	f=fopen("DATA/mainGame", "r");
	while(1){
		if(feof(f)){
			break;
		}
	strcpy(buffer,fgetll(f));	
		switch(buffer[0]){
			case L:

				break;
			case A:

				break;
			default:
			break;
		}
	}
	
}