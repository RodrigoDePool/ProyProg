#include "player.h"

int main(){
	FILE *f;
	Player *p;
	char name[20], nametest[20]="testname";
	f = fopen ("playertest.txt", "r");
	if (f == NULL) {
		printf("ERROR AL ABRIR ARCHIVO");
		return 0;
	}
	
	p = player_fromFile(f);
	name = Player_getName(p); 
	if (name == nametest)
		printf ("Name: OK");
	if (Player_getSpaceid(p) == 1)
		printf ("Spaceid: OK");
	if (Player_getCoordinateX(p) == 2)
		printf ("X: OK");
	if (Player_getCoordinateY(p) == 3)
		printf ("Y: OK");
	player_free(p);
	return 1;
}
