#include "world.h"
#define NDEBUG
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lineread.h"
#define MAXBUF 300
#define SPACE_PATHS_FILE "SpacePaths"
#define MAXSPACES 30


/*
    remmember that you know if a player has an object by its atribute in
    object struct
    TO BE ADD :
    POINTER TO INTERFACE
    THE ID OF THE SPACE THE PLAYER IS IN
    a path in which the game that is being played is to be saved

    array de strings dondeel primeroseael puntero que apunta al primer 
    riddle el segundo al segundo riddle
    y un int que tenga el numero de riddles que has hecho
    funcion que chequee los objetos requeridos

 */
struct _World
{
    Space  **spaces;
    int    numspaces;
    Object **objects;
    int    numobjects;
    Interface * i;
    int PlSpaceID;
    int PlRow;
    int PlCol;
    char * path;
};


/*
    I THINK WE SHOULD DIVIDE THIS
 */
World *world_ini(char * path, Interface * i)
{
    World *w;
    w = (World *) malloc(sizeof(World));
    if (w == NULL)
        return NULL;

    w->objects = NULL;
    w->numobjects = 0;
    w->objectPaths = NULL;
    w->spaces = NULL;
    w->numspaces = 0;
    w->spacePaths = NULL;
    w->PlSpaceID = -1;
    w->PlRow = -1;
    w->PlCol = -1;
    if(path==NULL)
        w->path = NULL;
    else 
        w->path=(char *)malloc(sizeof(char)*(strlen(path)+1));
        strcpy(w->path, path);

    if(i==NULL)
        w->i = NULL;
    else 
        w->i = i;
    return w;
}



void world_free(World *w)
{
    int i;
    if(w==NULL)
        return;
    for (i = 0; i < w->numobjects; i++)
        object_free(w->objects[i]);
    if(w->objects!=NULL)
        free(w->objects);
    for (i = 0; i < MAXSPACES; i++)
        space_free(w->spaces[i]);
    if(w->spaces!=NULL)
        free(w->spaces);
    if(w->path!=NULL)
        free(w->path);
    if(w->i!=NULL)
        i_free(w->i);
    free(w);

    return;
}

int world_setInterface(World * w, Interface * i)
{
	if(!w) retun -1;
	w->i=i;
	return 0;
}

Interface * world_getInterface(World * w)
{
	if(!w) retun NULL;
	return w->i;
}

void world_setPath(World * w, char * path)
{
	assert(w!=NULL);
	w->path=(char*)realloc(w->path, sizeof(char)*(strlen(path)+1));

}

char * world_getPath(World * w)
{
	assert(w!=NULL);
	return(w->path);

}

Space **world_getSpaces(World *w)
{
    assert(w != NULL);
    return w->spaces;
}

Space *world_getSpace(World *w, int ID)
{
    assert(w != NULL);
    return w->spaces[ID];
}


int world_getNumSpaces(World *w)
{
    assert(w != NULL);
    return w->numspaces;
}




Object **world_getObjects(World *w)
{
    assert(w != NULL);
    return w->objects;
}

Object *world_getObject(World *w, int ID)
{
    assert(w != NULL);
    return w->objects[ID];
}

int world_getNumObjects(World *w)
{
    assert(w != NULL);
    return w->numobjects;
}

int world_objectPick(World * w, int ID){
    if(!w||!path)
        return -1;
    object_pick(w->objects[ID]);
    w->numobjects++;
    return 0;
}

int world_objectDrop(World * w, int ID){
    if(!w||!path)
        return -1;
    object_drop(w->objects[ID]);
    w->numobjects--;
    return 0;
}

char * _world_getSpacePath(int ID){
	FILE * f;
	char * buffer;
	int i=0;
	f=fopen(SPACE_PATHS_FILE, "r");

	while(i<=ID){
		if(feof(f))
			return NULL;
		buffer=fgetll(f);
		if(++i<=ID)
			free(buffer);
	}

	fclose(f);
	return buffer;
}

char * _world_getSpacePathFile(FILE * , int ID){
	char * buffer;
	int i=0;
	while(i<=ID){
		if(feof(f))
			return NULL;
		buffer=fgetll(f);
		if(++i<=ID)
			free(buffer);
	}
	return buffer;
}

int world_AddSpace(World * w, int ID)
{
    if(!w||!path)
        return -1;
    FILE * f;
    char * path;
    path = _world_getSpacePath(ID);
    if(path==NULL)
    	return -1;
    f = fopen(path, "r");
    if(w->spaces==NULL||ID>MAXSPACES)
    	free(path);
        return -1;

    w->spaces[ID] = spacefromfile(f);
    
    w->numspaces++;
    free(path);
    return w->numspaces;
}

void world_setPlRow(World * w, int row)
{

    assert(w != NULL);
    w->PlRow=row;
}

void world_setPlCol(World * w, int Col)
{

    assert(w != NULL);
    w->PlCol=Col;
}

void world_setPlSpaceID(World * w, int ID)
{

    assert(w != NULL);
    w->PlSpaceID=ID;
}

int world_getPlSpaceID(World * w)
{
	assert(w != NULL);
	return w->PlSpaceID;
}

int world_getPlRow(World * w){
	assert(w != NULL);
	return w->PlRow;
}

int world_getPlCol(World * w){
	assert(w != NULL);
	return w->PlCol;
}

World *worldfromfile(char *file)
{
    assert(file != NULL);
    FILE   * f;
    FILE * SpacePathsFile;
    FILE * SpaceFile;
    int    i, j, SpaceID;
    World  *w;
    Space * auxspace;
    char buffer[MAXBUF];
    char * line;


    w = world_ini(file, NULL);
    f = fopen(file, "r");
    if (f == NULL)
        return NULL;

    /*PLAYER*/
    line=fgetll(f);
    sscanf(line, "%d %d %d", &(w->PlSpaceID), &(w->PlRow), &(w->PlCol));
    free(line);
    SpacePathsFile = fopen(SPACE_PATHS_FILE, "r");

    /*Space*/

    line=fgetll(f);
    sscanf(line, "%d", &(w->numspaces));
    free(line);

    w->spaces = (Space * *) malloc(sizeof(Space *) * MAXSPACES);

    if (w->spaces == NULL)
    {	
    	world_free(w);
        fclose(f);
        return NULL;
    }

    for(i=0;i<MAXSPACES;i++)
    {
    	w->spaces[i]=NULL;
    }

    for (i = 0; i < w->numspaces; i++)
    {
    	line= fgetll(f);
    	SpaceID = atoi(line);
    	buffer =_world_getSpacePathFile(SpacePathsFile, SpaceID);
    	SpaceFile = fopen(buffer, "r");
        w->spaces[SpaceID] = spacefromfile(SpaceFile);
        if (w->spaces[SpaceID] == NULL)
        {
            for (j = i; j >= 0; j--)
            {
                space_free(w->spaces[j]);
            }
            free(w->spaces);
            fclose(f);
            fclose(SpaceFile);
            fclose(SpacePathsFile);
            return NULL;
        }
        fclose(SpaceFile);
    }

    fclose(SpacePathsFile);

    /*Object*/

    fscanf(f, "%d\n", &(w->numobjects));
    w->objects = (Object * *) malloc(sizeof(Object *) * w->numobjects);
    if (objects == NULL)
    {
        world_free(w);
        fclose(f);
        return NULL;
    }

    for (i = 0; i < numobjects; i++)
    {
        objects[i] = objectfromfile(f);
        if (objects[i] == NULL)
        {
            world_free(w);
            fclose(f);
            return NULL;
        }
    }

    
    fclose(f);
    return w;
}

int world_saveToFile(World * w, char * path)
{
	assert(w!=NULL);
	FILE * f;
	int i;

	f=fopen(path, "w");

	fprintf(f, "%d %d %d\n", w->PlSpaceID, w->PlRow, w->PlCol);

	for(i=0;i<MAXSPACES;i++){
		if(w->spaces[i]!=NULL){
			fprintf(f, "%d\n", space_getID(w->spaces[i]));
		}
	}

	for(i=0;i<w->numobjects;i++){
		fprintf(f, "%d\n", object_getId(w->objects[i]));
		fprintf(f, "%s\n", object_getName(w->objects[i]));
		fprintf(f, "%d\n", (int) object_getHas(w->objects[i]));
		fprintf(f, "%d\n", object_getSpaceid(w->objects[i]));
		fprintf(f, "%s\n", object_getDesc(w->objects[i]));

	}
}

