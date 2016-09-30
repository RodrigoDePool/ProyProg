#include "object.h"
#define name(o) (o)->name
#define desc(o) (o)->desc
#define spaceid(o) (o)->spaceid
#define id(o) (o)->id
#define has(o) (o)->has


typedef _Object{
	int id;/*All properties could be check from the object id*/
	char *name;
	Possession has;
	int spaceid;
	char *desc;
}

Object *object_ini(){
	Object *o;
	o=(Object *)malloc(sizeof(Object));
	if(o==NULL) return NULL;
	name(o)=NULL;
	desc(o)=NULL;
	spaceid(o)=-1;
	id(o)=-1;
	has(o)=0;	

	return o;

}

void object_free(Object *o){
	

}
