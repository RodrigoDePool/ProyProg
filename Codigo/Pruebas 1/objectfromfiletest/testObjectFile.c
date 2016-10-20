#include <stdio.h>
#include <stdlib.h>
#include "object.h"

int main(int argc, char** argv){
	FILE * f;
	char c;
	char *name;
	char * desc;
	f=fopen("toRead", "r");
	Object * o =objectfromfile(f);
	name= object_return_name(o);
	desc=object_return_desc(o);
	printf("\nId: %d\nName: %s\nHas: %d\nSpaceId: %d\nDesc: %s a", 
		object_return_id(o), name, object_return_has(o),
		object_return_spaceid(o), desc);
	printf("\n-----Tendría que ser:\nId: 12\nName: nombreee\nHas: 0\nSpaceId: 200\nDesc: Esta es una descripcion del objeto");
	fscanf(f, "%c\n", &c);
	if(c!='c')
		printf("Mal el caracter");
	fclose(f);
	object_free(o);
	free(name);
	free(desc);
	return 0;
}