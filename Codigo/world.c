
#include "world.h"
#define NDEBUG
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXBUF       130
#define MAXSPACES    30



/*
    remmember that you know if a player has an object by its atribute in
    object struct
    TO BE ADD :
    POINTER TO INTERFACE
    THE ID OF THE SPACE THE PLAYER IS IN
    a path in which the game that is being played is to be saved

    array de strings donde el primero sea el puntero que apunta al primer
    riddle el segundo al segundo riddle
    y un int que tenga el numero de riddles que has hecho
    funcion que chequee los objetos requeridos

 */
struct _World
{
    Space     **spaces;
    int       numspaces;
    int       numobjects;
    int       Pllevel;
    Interface * i;
    int       PlSpaceID;
    char      * path;
    Level     ** levels;
    Minigame  * minigame;
    /*generally 1 = has finished the minigame with the same index;0 = has not finished the minigame but it can take any value except -1*/
    int * HasFinishedMinigame;
};

char * fgetll(FILE * f)
{
    char * c;
    c=(char*)malloc(sizeof(char)*(MAXBUF+1));
    c[0]='#';
    while(c[0]=='#')
        fgets(c, MAXBUF, f);
    if(c[strlen(c)-1]=='\n')
        c[strlen(c)-1]=0;
    return c;

}

Minigame * minigamesIni()
{
    Minigame * minigames = NULL;
    int      i;
    minigames = (Minigame *) malloc(sizeof(Minigame) * numMinigames);

    minigames[0]  = &(easyMiniMaze);
    minigames[1]  = &(easyMiniPadel);
    minigames[2]  = NULL; /*&(mini2048_small);*/
    minigames[3]  = &(miniRPSLS);
    minigames[4]  = NULL;/*Calculo Rapido*/
    minigames[5]  = NULL;/*&(easyCountDots);*/
    minigames[6]  = &(snake);
    minigames[7]  = NULL;/*&(hardCountDots);*/
    minigames[8]  = &(questions);
    minigames[9]  = &(hardMiniMaze);
    minigames[10] = NULL; /*&(mini2048_big);*/
    minigames[11] = &(hardMiniPadel);

    return minigames;
}

Level ** levelsIni()
{
    Level ** levels;
    int   i;
    FILE *f;
    char * buffer;

    f=fopen(SOLUTIONS_PATH, "r");

    if(!f){
        return NULL;
    }

    levels = (Level * *) malloc(sizeof(Level*) * numLevels);
    if(!levels){
        fclose(f);
        return NULL;
    }

    for (i = 0; i < numLevels; i++)
    {
        levels[i] = (Level *) malloc(sizeof(Level));
    }
    
    for(i=0;i<numLevels;i++)
    {
        buffer=fgetll(f);
        if(buffer==NULL){
            fclose(f);
            for (i = 0; i < numLevels; i++)
            {
                free(levels[i]);
            }
            free(levels);
            return NULL;
        }
        levels[i]->solution = (char *) malloc(sizeof(char*) * (strlen(buffer) + 1));
        strcpy(levels[i]->solution, buffer);
        free(buffer);
    }

    
    levels[0]->finalAnimation   = NULL;
    levels[0]->PlIniRow         = -1;
    levels[0]->PlIniCol         = -1;
    levels[0]->PlIniSpaceID     = -1;
    

    fclose(f);
    return levels;
}

World *world_ini(char * path, Interface * i)
{
    World *w;
    int j;
    w = (World *) malloc(sizeof(World));
    if (w == NULL)
        return NULL;


    w->numobjects = 0;
    w->spaces     = NULL;
    w->numspaces  = 0;
    w->PlSpaceID  = -1;
    w->levels     = levelsIni();
    if(!w->levels){
        free(w);
        return NULL;
    }
    w->minigame   = minigamesIni();
    if(!w->minigame){
        for (j = 0; j < numLevels; j++)
        {
            free(w->levels[j]->solution);
            free(w->levels[j]);
        }
        free(w);
        return NULL;
    }
    w->Pllevel    = 0;
    w->HasFinishedMinigame=(int*)malloc(sizeof(int)*numMinigames);
    if (path == NULL)
        w->path = NULL;
    else
        w->path = (char *) malloc(sizeof(char) * (strlen(path) + 1));
        if(!w->path){
            world_free(w);
            return NULL;
        }
    strcpy(w->path, path);

    w->i = i;
    return w;
}

int isItASpaceOrAMinigame(int ID)
{
    if (ID >= 50)
        return 1;
    if (ID < 0)
        return -1;
    else
        return 0;
}



void world_free(World *w)
{
    int i = 0;
    if (w == NULL)
        return;
    for (i = 0; i < MAXSPACES; i++)
        space_free(w->spaces[i]);
    if (w->spaces != NULL)
        free(w->spaces);
    if (w->path != NULL)
        free(w->path);
    /*free the levels*/
    for (i = 0; i < numLevels; i++)
    {
        free(w->levels[i]->solution);
        free(w->levels[i]);
    }
    free(w->levels);
    free(w->HasFinishedMinigame);
    free(w->minigame);
    free(w);

    return;
}

int world_setInterface(World * w, Interface * i)
{
    if (!w)
        return -1;
    if (w->i != NULL)
        i_free(w->i);
    w->i = i;
    return 0;
}

Interface * world_getInterface(World * w)
{
    if (!w)
        return NULL;
    return w->i;
}

Level * world_getLevel(World * w, int ID){
    if(!w||ID<0||ID>numLevels)
        return NULL;
    return w->levels[ID];
}

int world_setMinigameFinished(World * w, int ID, int finished){
    if(!world_free||ID<0||ID%50>(numMinigames-1))
        return -1;
    w->HasFinishedMinigame[ID%50]=finished;
    return 0;
}

int world_getMinigameFinished(World * w, int ID){
    if(!w||ID<0||ID%50>(numMinigames-1))
        return -1;
    return w->HasFinishedMinigame[ID%50];
}

void world_setPath(World * w, char * path)
{
    assert(w != NULL);
    w->path = (char *) realloc(w->path, sizeof(char) * (strlen(path) + 1));
}

char * world_getPath(World * w)
{
    assert(w != NULL);
    return(w->path);
}

Minigame world_getMinigame(World * w, int ID)
{
    if (!w || ID < 50 || ID - 50 > numMinigames - 1)
        return NULL;
    return w->minigame[ID%50];
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

int world_getPllevel(World * w)
{
    if (!w)
        return -2;
    return w->Pllevel;
}

void world_setPllevel(World * w, int Pllevel)
{
    if (!w)
        return;
    w->Pllevel = Pllevel;
    return;
}


int world_getNumObjects(World *w)
{
    assert(w != NULL);
    return w->numobjects;
}
void world_setNumObjects(World *w, int num)
{
    assert(w != NULL);
    w->numobjects = num;
    return;
}
char * world_getSpacePath(int ID)
{
    FILE * f;
    char * buffer;
    int  i = 0;
    f = fopen(SPACE_PATHS_FILE, "r");

    while (i <= ID)
    {
        if (feof(f))
            return NULL;
        buffer = fgetll(f);
        if (++i <= ID)
            free(buffer);
    }

    fclose(f);
    return buffer;
}

/*DO NOT USE THIS FUNTION*/
char * world_getSpacePathFile(FILE * f, int ID)
{
    char * buffer;
    int  i = 0;
    while (i <= ID)
    {
        if (feof(f))
            return NULL;
        buffer = fgetll(f);
        if (++i <= ID)
            free(buffer);
    }
    return buffer;
}

int world_AddSpace(World * w, int ID)
{
    if (!w)
        return -1;
    FILE * f;
    char * path;
    path = world_getSpacePath(ID);
    if (path == NULL)
        return -1;
    f = fopen(path, "r");
    if (w->spaces == NULL || ID > MAXSPACES)
        free(path);
    return -1;

    w->spaces[ID] = spacefromfile(f);

    w->numspaces++;
    free(path);
    return w->numspaces;
}

char ** world_getSpaceMap(World * w, int SpaceID)
{
    if (!w)
        return NULL;
    return space_getMap(w->spaces[SpaceID]);
}

void world_setPlRow(World * w, int row)
{
    assert(w != NULL);
    i_drawPl(w->i, row, i_wherePlayerBeCol(w->i));
}

void world_setPlCol(World * w, int Col)
{
    assert(w != NULL);
    i_drawPl(w->i, i_wherePlayerBeRow(w->i), Col);
}

void world_setPlCoords(World * w, int row, int Col)
{
    assert(w != NULL);
    i_drawPl(w->i, row, Col);
}

void world_setPlSpaceID(World * w, int ID)
{
    assert(w != NULL);
    w->PlSpaceID = ID;
}

int world_getPlSpaceID(World * w)
{
    assert(w != NULL);
    return w->PlSpaceID;
}

int world_getPlRow(World * w)
{
    assert(w != NULL);
    return i_wherePlayerBeRow(w->i);
}

int world_getPlCol(World * w)
{
    assert(w != NULL);
    return i_wherePlayerBeCol(w->i);
}


World *worldfromfile(char *file, Interface * i)
{
    assert(file != NULL);
    FILE  * f;
    FILE  * SpacePathsFile;
    FILE  * SpaceFile;
    int   k, j, SpaceID, PlRow, PlCol;
    World *w;
    Space * auxspace;
    char  buffer[MAXBUF];
    char  * line;


    w = world_ini(file, i);
    f = fopen(file, "r");
    if (f == NULL)
        return NULL;

    
    /*PLAYER*/
    line = fgetll(f);
    sscanf(line, "%d %d %d", &(w->PlSpaceID), &(PlRow), &(PlCol));
    free(line);
    SpacePathsFile = fopen(SPACE_PATHS_FILE, "r");
    i_drawPl(w->i, PlRow, PlCol);

    
    /*Space*/
    line = fgetll(f);
    sscanf(line, "%d", &(w->numspaces));
    free(line);

    w->spaces = (Space * *) malloc(sizeof(Space *) * MAXSPACES);

    if (w->spaces == NULL)
    {
        world_free(w);
        fclose(f);
        return NULL;
    }

    for (k = 0; k < MAXSPACES; k++)
    {
        w->spaces[k] = NULL;
    }

    for (k = 0; k < w->numspaces; k++)
    {
        line    = fgetll(f);
        SpaceID = atoi(line);
        free(line);
        line=  fgetll(SpacePathsFile);

        SpaceFile = fopen(line, "r");
        free(line);
        if (SpaceFile == NULL)
        {
            for (j = k; j >= 0; j--)
            {
                space_free(w->spaces[j]);
            }
            free(w->spaces);
            fclose(f);
            fclose(SpacePathsFile);
            return NULL;
        }

        w->spaces[SpaceID] = spacefromfile(SpaceFile);
        if (w->spaces[SpaceID] == NULL)
        {
            for (j = k; j >= 0; j--)
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

    /*Pllevel*/

    fscanf(f, "%d\n", &(w->Pllevel));

    /*Finished Minigames*/

    for(j=0;j<numMinigames;j++){
        fscanf(f, "%d ", &(w->HasFinishedMinigame[j]));
    }

    fclose(f);
    return w;
}

int world_saveToFile(World * w, char * path)
{
    assert(w != NULL);
    FILE * f;
    int  i;

    if (path != NULL)
        f = fopen(path, "w");
    else if (w->path != NULL)
        f = fopen(w->path, "w");
    else
        return -1;

    if (!f)
        return -1;

    fprintf(f, "%d %d %d\n", w->PlSpaceID, i_wherePlayerBeRow(w->i), i_wherePlayerBeCol(w->i));

    fprintf(f, "%d\n", w->numspaces);

    for (i = 0; i < MAXSPACES; i++)
    {
        if (w->spaces[i] != NULL)
        {
            fprintf(f, "%d\n", space_getId(w->spaces[i]));
        }
    }

    fprintf(f, "%d\n", w->numobjects);

    /*Pllevel*/

    fprintf(f, "%d\n", (w->Pllevel));

    /*Finished Minigames*/

    for(i=0;i<numMinigames;i++){
        fprintf(f, "%d ", w->HasFinishedMinigame[i]);
    }

    fclose(f);
    return 0;
}

