#include "object.h"
#define NDEBUG
#include <assert.h>
#include <string.h>
#define name(o) ((o)->name)
#define desc(o) ((o)->desc)
#define spaceid(o) ((o)->spaceid)
#define id(o) ((o)->id)
#define has(o) ((o)->has)
#define NAME_MAX 30
#define DESC_MAX 1000

struct _Object{
	int id;/*All properties could be check from the object id*/
	char *name;
	Bool has;
	int spaceid;
	char *desc;
};



Object *object_ini(){
	Object *o;
	o=(Object *)malloc(sizeof(Object));
	if(o==NULL) return NULL;
	name(o)=NULL;
	desc(o)=NULL;
	spaceid(o)=-1;
	id(o)=-1;
	has(o)=FALSE;	

	return o;
}



void object_free(Object *o){
	assert(o!=NULL);
	if(name(o)!=NULL){
		free(name(o));
	}	
	if(desc(o)!=NULL){
		free(desc(o));
	}

	free(o);
	return;
}

Status object_setId(Object *o, int oid){
	assert(o!=NULL);
	assert(oid>0);
	id(o)=oid;
	return OK;
}

Status object_setName(Object *o, char *name){
	assert(o!=NULL);
	assert(name!=NULL);

	if(name(o)!=NULL)/*if there was a name before*/
		free(name(o));

	name(o)=(char *)malloc(sizeof(char)*(1+strlen(name)));
	if(name(o)==NULL){
		return ERROR;
	}

	name(o)=strcpy(name(o),name);
	return OK;
}



Status object_setDesc(Object *o, char *desc){
	assert(o!=NULL);
	assert(desc!=NULL);

	if(desc(o)!=NULL)
		free(desc(o));

	desc(o)=(char *)malloc(sizeof(char)*(strlen(desc)+1));
	if(desc(o)==NULL){
		return ERROR;
	}

	desc(o)=strcpy(desc(o),desc);
	return OK;
}



Status object_setSpaceid(Object *o, int spaceid){
	assert(o!=NULL);
	assert(spaceid>-1);

	spaceid(o)=spaceid;
	return OK;
}



Status object_Pick(Object *o){
	assert(o!=NULL);
	has(o)=TRUE;
	return OK;
}



Status object_Drop(Object *o){
	assert(o!=NULL);
	has(o)=FALSE;
	return OK;
}



char *object_getName(Object *o){
	char *name;
	assert(o!=NULL);
	if(name(o)==NULL)
		return NULL;
	name=(char *)malloc(sizeof(char)*(1+strlen(name(o))));
	if(name==NULL)
		return NULL;
	name=strcpy(name, name(o));
	return name;
}




char *object_getDesc(Object *o){
	char *desc;
	assert(o!=NULL);
	if(desc(o)==NULL)
		return NULL;
	desc=(char *)malloc(sizeof(char)*(1+strlen(desc(o))));
	if(desc==NULL)
		return NULL;
	desc=strcpy(desc, desc(o));
	return desc;
}



int object_getSpaceid(Object *o){
	assert(o!=NULL);
	return spaceid(o);
}




int object_getId(Object *o){
	assert(o!=NULL);
	return id(o);
}


Bool object_getHas(Object *o){
	assert(o!=NULL);
	return has(o);
}


Object *objectfromfile(FILE *f){
	assert(f!=NULL);
	Object *o;

	o=object_ini();
	if(o==NULL) return NULL;
	name(o)=(char *)malloc(sizeof(char)*NAME_MAX);
	if(name(o)==NULL){
		object_free(o);
		return NULL;
	}
	desc(o)=(char *)malloc(sizeof(char)*DESC_MAX);
	if(desc(o)==NULL){
		free(name(o));
		object_free(o);
		return NULL;
	}

	/*The reading starts*/
	fscanf(f,"%d\n",&id(o));
	fgets(name(o),NAME_MAX,f);
	name(o)[strlen(name(o))-1]=0; /*We remove the line end \n*/
	fscanf(f,"%d\n",(int *) &has(o));
	fscanf(f,"%d\n",&spaceid(o));
	fgets(desc(o),DESC_MAX,f);
	desc(o)[strlen(desc(o))-1]=0;
	return o;
}

