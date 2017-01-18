#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
/*#define NDEBUG*/
#include <assert.h>


#define sId(s)         (s)->sId
#define sDesc(s)       (s)->shortDesc
#define lDesc(s)       (s)->longDesc
#define light(s)       (s)->light
#define isLocked(s)    (s)->isLocked
#define map(s)         (s)->map
#define rows(s)        (s)->rows
#define cols(s)        (s)->cols
#define numdoors(s)    (s)->numdoors
#define doors(s)       (s)->doors
#define MAX_L_DESC    1000
#define MAX_S_DESC    100


struct space_
{
    int  sId;
    int  numdoors;
    Door *doors;
    char *shortDesc;
    char *longDesc;
    Bool light;
    Bool isLocked;
    int  rows, cols;
    char ** map;
};




/*------------------Fuciones terminadas-----------------*/


Space * space_ini()
{
    int   i;
    Space *s;
    s = (Space *) malloc(sizeof(Space));
    if (!s)
        return NULL;
    sId(s)      = -1;
    sDesc(s)    = NULL;
    lDesc(s)    = NULL;
    light(s)    = FALSE;
    isLocked(s) = FALSE;
    map(s)      = NULL;
    rows(s)     = -1;
    cols(s)     = -1;
    numdoors(s) = -1;
    doors(s)    = NULL;
    return s;
}

void space_free(Space *s)
{
    int i;
    if (!s)
        return;
    if (sDesc(s))
        free(sDesc(s));
    if (lDesc(s))
        free(lDesc(s));
    if (map(s))
    {
        for (i = 0; i < rows(s); i++)
        {
            if (map(s)[i])
                free(map(s)[i]);
        }
        free(map(s));
    }
    if (doors(s) != NULL)
    {
        free(doors(s));
    }
    free(s);
}

int space_getId(Space *s)
{
    if (!s)
        return -1;
    return sId(s);
}

Status space_setId(Space *s, int sId)
{
    assert(s && sId > -1);
    sId(s) = sId;
    return OK;
}

char *space_getSDesc(Space * s)
{
    char* description = NULL;
    if (!s)
        return NULL;
    description = strdup(sDesc(s));
    return description;
}

Status space_setSDesc(Space * s, char *sdesc)
{
    assert(s && sdesc);
    if (!sDesc(s))
        sDesc(s) = strdup(sdesc);
    return OK;
}

char *space_getLDesc(Space * s)
{
    if (!s)
        return NULL;
    return strdup(lDesc(s));
}

Status space_setLDesc(Space * s, char *ldesc)
{
    assert(s && ldesc);
    if (!lDesc(s))
        /*Assume we set lDesc only once*/
        lDesc(s) = strdup(ldesc);
    return OK;
}

Bool space_canISee(Space *s)
{
    if (!s)
        return FALSE;
    return light(s);
}

Status space_setLight(Space *s, Bool light)
{
    assert(s);
    light(s) = light;
    return OK;
}


Bool space_isLocked(Space *s)
{
    if (!s)
        return FALSE;
    return isLocked(s);
}

Status space_setLock(Space *s, Bool status)
{
    assert(s);
    if (status != isLocked(s))
        isLocked(s) = status;
    return OK;
}

int space_getNRows(Space *s)
{
    if (!s)
        return -1;
    return rows(s);
}

Status space_setNRows(Space *s, int nrows)
{
    assert(s && nrows > 0);
    rows(s) = nrows;
    return OK;
}

int space_getNCols(Space *s)
{
    if (!s)
        return -1;
    return cols(s);
}

Status space_setNCols(Space *s, int ncols)
{
    assert(s && ncols > 0);
    cols(s) = ncols;
    return OK;
}

char **space_getMap(Space *s)
{
    if (!s)
        return NULL;
    return map(s);
}

Status space_setMap(Space *s, char **map)
{
    assert(s && map);
    /*Assume map dimensions are the ones in cols, rows*/
    map(s) = map;
    return OK;
}

Status space_setNDoors(Space *s, int num)
{
    if (s == NULL || num < 0)
        return ERROR;
    numdoors(s) = num;
    /*if there is more than a door we give it memory*/
    if (num > 0)
    {
        doors(s) = (Door *) malloc(sizeof(Door) * num);
        if (doors(s) == NULL)
            return ERROR;
    }
    return OK;
}

int space_getNDoors(Space *s)
{
    if (s == NULL)
        return -1;
    return numdoors(s);
}

Status space_setDoor(Space *s, int n, int x, int y, int sId, int nx, int ny)
{
    if (s == NULL || x < 0 || y < 0 || numdoors(s) <= n || n < 0)
        return ERROR;
    doors(s)[n].x         = x;
    doors(s)[n].y         = y;
    doors(s)[n].neighbour = sId;
    doors(s)[n].nx        = nx;
    doors(s)[n].ny        = ny;
    return OK;
}

Door *space_checkDoorPoint(Space *s, int x, int y)
{
    int i;
    if (s == NULL || x < 0 || y < 0)
        return NULL;
    for (i = 0; i < numdoors(s); i++)
    {
        if (doors(s)[i].x == x && doors(s)[i].y == y)
        {
            return doors(s);
        }
    }
    return NULL;
}

Door *space_checkDoorAPoint(Space *s, int x, int y)
{
    Door *aux;
    if (s == NULL || x < 0 || y < 0)
        return NULL;
    /*up*/
    aux = space_checkDoorPoint(s, x, y - 1);
    if (aux != NULL)
        return aux;
    /*down*/
    aux = space_checkDoorPoint(s, x, y + 1);
    if (aux != NULL)
        return aux;
    /*right*/
    aux = space_checkDoorPoint(s, x + 1, y);
    if (aux != NULL)
        return aux;
    /*left*/
    aux = space_checkDoorPoint(s, x - 1, y);
    if (aux != NULL)
        return aux;
    return NULL;
}

char ** mapfromfile(FILE * f, int nrows, int ncols)
{
    assert(nrows > 0);
    assert(ncols > 0);
    assert(f != NULL);
    char **map;
    int  i, j;

    map = (char * *) malloc(sizeof(char *) * nrows);
    if (map == NULL)
        return NULL;
    for (i = 0; i < nrows; i++)
    {
        map[i] = (char *) malloc(sizeof(char) * (ncols + 1));
        if (map[i] == NULL) /*lack of memory*/
        {
            for (j = i - 1; j >= 0; j--)
            {
                free(map[j]);
            }
            free(map);
            return NULL;
        }
    }

    for (i = 0; i < nrows; i++)
    {
        fgets(map[i], ncols + 1, f);
        fscanf(f, "\n");
    }

    return map;
}

Space * spacefromfile(FILE * f)
{
    assert(f != NULL);
    char  buff[MAX_L_DESC];
    int   aux, i, ndoors, x, y, nx, ny;
    FILE  *file;
    Space *s;

    s = space_ini();
    if (!s)
        return NULL;

    fscanf(f, "%d\n", &aux);
    if (space_setId(s, aux) == ERROR)
    {
        space_free(s);
        return NULL;
    }
    fscanf(f, "%d\n", &aux);
    if (space_setNDoors(s, aux) == ERROR)
    {
        space_free(s);
        return NULL;
    }
    ndoors = aux;
    for (i = 0; i < ndoors; i++)
    {
        fscanf(f, "%d %d %d %d %d\n", &y, &x, &aux, &ny, &nx);
        if (space_setDoor(s, i, x, y, aux, nx, ny) == ERROR)
        {
            space_free(s);
            return NULL;
        }
    }

    fscanf(f, "%1000[^\n]\n", buff);
    if (space_setSDesc(s, buff) == ERROR)
    {
        space_free(s);
        return NULL;
    }
    fscanf(f, "%2000[^\n]\n", buff);
    if (space_setLDesc(s, buff) == ERROR)
    {
        space_free(s);
        return NULL;
    }
    fscanf(f, "%d\n", &aux);
    if (space_setLight(s, aux) == ERROR)
    {
        space_free(s);
        return NULL;
    }
    fscanf(f, "%d\n", &aux);
    if (space_setLock(s, aux) == ERROR)
    {
        space_free(s);
        return NULL;
    }
    fscanf(f, "%s\n", buff);
    file = fopen(buff, "r");
    if (!file)
    {
        space_free(s);
        return NULL;
    }
    fscanf(file, "%d ", &aux);
    if (space_setNRows(s, aux) == ERROR)
    {
        space_free(s);
        return NULL;
    }
    fscanf(file, "%d\n", &aux);
    if (space_setNCols(s, aux) == ERROR)
    {
        space_free(s);
        return NULL;
    }
    if (space_setMap(s, mapfromfile(file, space_getNRows(s), space_getNCols(s))) == ERROR)
    {
        space_free(s);
        fclose(file);
        return NULL;
    }
    fclose(file);
    return s;
}




