#include <stdio.h>
#include "object.h"
#include <string.h>

int main(){
	Object *o = object_ini();
	char name[] = "TestingName";
	char desc[] = "TestingDesc";
	char *nameret, *descret;
	
	object_set_name(o, name);
	object_set_desc(o, desc);
	object_set_spaceid(o, 1);
	object_set_id(o, 2);
	object_pick(o);
	nameret = object_return_name(o);
	descret = object_return_desc(o);
	if (strcmp(nameret, name) == 0)
		printf("set and return name: OK\n");
	if (strcmp(descret, desc) == 0)
		printf("set and return desc: OK\n");
	if (object_return_spaceid(o) == 1)
		printf("set and return spaceid: OK\n");
	if (object_return_id(o) == 2)
		printf("set and return id: OK\n");
	if (object_return_has(o) == TRUE)
		printf("pick and return has: OK\n");
	object_drop(o);
	if (object_return_has(o) == FALSE)
		printf("drop: OK\n");
	object_free(o);
	return 1;
}

