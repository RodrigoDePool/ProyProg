#include "player.h"
#include <stdio.h>

int main(){
	FILE *f;
	Player *p;
	char *name, nametest[20]="testname";
	f = fopen ("playertest.txt", "r");
	if (f == NULL) {
		printf("ERROR AL ABRIR ARCHIVO");
		return 0;
	}
	
	p = playerfromfile(f);
	name = Player_getName(p); 
	if (name == nametest)
		printf ("Name: OK");
	else printf ("ERROR NAME\n");
	if (Player_getSpaceid(p) == 1)
		printf ("Spaceid: OK");
	else printf ("ERROR SPACE\n");
	if (Player_getCoordinateX(p) == 2)
		printf ("X: OK");
	else printf ("ERROR X\n");
	if (Player_getCoordinateY(p) == 3)
		printf ("Y: OK");
	else printf ("ERROR Y\n");
	player_free(p);
	return 1;
}
