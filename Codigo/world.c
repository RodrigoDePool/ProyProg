#include "world.h"
#define NDEBUG
#include <stdlib.h>
#include <assert.h>
#define spaces(w)       (w)->spaces
#define numspaces(w)    (w)->numspaces
#define obj(w)          (w)->objects
#define numobj(w)       (w)->numobjects
#define player(w)       (w)->player


struct _World
{
    Space  **spaces;
    int    numspaces;
    Object **objects;
    int    numobjects;
    Player *player;
};



World *world_ini(Object **obj, Player *p, Space **space, int numobj, int numspaces)
{
    World *w;
    assert(obj != NULL);
    assert(p != NULL);
    assert(space != NULL);


    w = (World *) malloc(sizeof(World));
    if (w == NULL)
        return NULL;

    obj(w)       = obj;
    player(w)    = p;
    spaces(w)    = space;
    numobj(w)    = numobj;
    numspaces(w) = numspaces;
    return w;
}



void world_free(World *w)
{
    int i;
    assert(w != NULL);
    for (i = 0; i < numobj(w); i++)
        object_free(obj(w)[i]);
    free(obj(w));
    for (i = 0; i < numspaces(w); i++)
        space_free(spaces(w)[i]);
    player_free(player(w));
    free(spaces(w));
    free(w);

    return;
}



Space **world_getSpaces(World *w)
{
    assert(w != NULL);
    return spaces(w);
}



int world_getNumSpaces(World *w)
{
    assert(w != NULL);
    return numspaces(w);
}




Object **world_getObjects(World *w)
{
    assert(w != NULL);
    return obj(w);
}




int world_getNumObjects(World *w)
{
    assert(w != NULL);
    return numobj(w);
}




Player *world_getPlayer(World *w)
{
    assert(w != NULL);
    return player(w);
}


World *worldfromfile(char *file)
{
    assert(file != NULL);
    FILE   *f;
    int    i, j;
    int    numspaces, numobjects;
    Space  **spaces;
    Player *player;
    Object **objects;
    World  *w;

    f = fopen(file, "r");
    if (f == NULL)
        return NULL;
    fscanf(f, "%d\n", &numspaces);
    spaces = (Space * *) malloc(sizeof(Space *) * numspaces);
    if (spaces == NULL)
    {
        fclose(f);
        return NULL;
    }

    for (i = 0; i < numspaces; i++)
    {
        spaces[i] = spacefromfile(f);
        if (spaces[i] == NULL)
        {
            for (j = i; j >= 0; j--)
            {
                space_free(spaces[j]);
            }
            free(spaces);
            fclose(f);
            return NULL;
        }
    }

    player = playerfromfile(f);
    if (player == NULL) /*if theres no memory free everything and return NULL*/
    {
        for (j = 0; j < numspaces; j++)
        {
            space_free(spaces[j]);
        }
        free(spaces);
        fclose(f);
        return NULL;
    }


    fscanf(f, "%d\n", &numobjects);
    objects = (Object * *) malloc(sizeof(Object *) * numobjects);
    if (objects == NULL)
    {
        for (j = 0; j < numspaces; j++)
        {
            space_free(spaces[j]);
        }
        free(spaces);
        player_free(player);
        fclose(f);
        return NULL;
    }

    for (i = 0; i < numobjects; i++)
    {
        objects[i] = objectfromfile(f);
        if (objects[i] == NULL)
        {
            for (j = 0; j < numspaces; j++)
            {
                space_free(spaces[j]);
            }
            free(spaces);
            player_free(player);
            for (j = i - 1; j >= 0; j--)
            {
                object_free(objects[i]);
            }
            free(objects);
            fclose(f);
            return NULL;
        }
    }

    w = world_ini(objects, player, spaces, numobjects, numspaces);
    if (w == NULL)
    {
        for (j = 0; j < numspaces; j++)
        {
            space_free(spaces[j]);
        }
        free(spaces);
        player_free(player);
        for (j = 0; j < numobjects; j++)
        {
            object_free(objects[i]);
        }
        fclose(f);
        free(objects);
        return NULL;
    }
    fclose(f);
    return w;
}



