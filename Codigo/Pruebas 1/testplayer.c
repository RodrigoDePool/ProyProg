#include <stdio.h>
#include "player.h"
#include <string.h>

int main(){
	Player *p = player_ini();
	char name[] = "TestingName";
	char *nameret;
	
	Player_setName(p, name);
	Player_setSpaceid(p, 1);
	Player_setCoordinateX(p, 2);
	Player_setCoordinateY(p, 3);
	nameret = Player_getName(p);
	if (strcmp(nameret, name) == 0)
		printf("set and get name: OK\n");
	if (Player_getSpaceid(p) == 1)
		printf("set and get spaceid: OK\n");
	if (Player_getCoordinateX(p) == 2)
		printf("set and get coordinate x: OK\n");
	if (Player_getCoordinateY(p) == 3)
		printf("set and get coordinate y: OK\n");
	player_free(p);
	return 1;
}

