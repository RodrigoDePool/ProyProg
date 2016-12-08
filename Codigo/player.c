#include "player.h"
#define NDEBUG
#include <assert.h>
#include <string.h>
#define name(p)       (p)->name
#define spaceid(p)    (p)->spaceid
#define x(p)          (p)->coordx
#define y(p)          (p)->coordy

struct _Player
{
    char *name;
    int  spaceid;
    int  coordx;
    int  coordy;
};

Player *player_ini()
{
    Player *p;

    p = (Player *) malloc(sizeof(Player));
    if (p == NULL)
        return NULL;

    name(p)    = NULL;
    spaceid(p) = -1;
    x(p)       = -1;
    y(p)       = -1;

    return p;
}

void player_free(Player *p)
{
    assert(p != NULL);

    if (name(p) != NULL)
        free(name(p));

    free(p);
}

Status player_setName(Player *p, char *name)
{
    assert(p != NULL);
    assert(name != NULL);

    if (name(p) != NULL)
        free(name(p));

    name(p) = (char *) malloc(sizeof(char) * (1 + strlen(name)));
    if (name(p) == NULL)
        return ERROR;

    name(p) = strcpy(name(p), name);

    return OK;
}

char *player_getName(Player *p)
{
    char *name;
    assert(p != NULL);
    assert(name(p) != NULL);
    name = strdup(name(p));
    return name;
}

Status player_setSpaceid(Player *p, int id)
{
    assert(p != NULL);
    assert(id > 0);  /*Just greater or grater or equal?*/

    spaceid(p) = id;

    return OK;
}

int player_getSpaceid(Player *p)
{
    assert(p != NULL);

    return spaceid(p);
}

Status player_setCoordinateX(Player *p, int x)
{
    assert(p != NULL);
    assert(x > 0);  /*Just greater or greater or equal?*/

    x(p) = x;

    return OK;
}

int player_getCoordinateX(Player *p)
{
    assert(p != NULL);

    return x(p);
}

Status player_setCoordinateY(Player *p, int y)
{
    assert(p != NULL);
    assert(y > 0);  /*Just greater or greater or equal?*/

    y(p) = y;

    return OK;
}

int player_getCoordinateY(Player *p)
{
    assert(p != NULL);

    return y(p);
}

Player *playerfromfile(FILE* f)
{
    char   c[20];
    int    spaceid, x, y;
    Player *p = player_ini();
    if (p == NULL)
        return NULL;
    fscanf(f, "%s\n", c);
    fscanf(f, "%d\n", &spaceid);
    fscanf(f, "%d %d\n", &x, &y);
    Player_setName(p, c);
    Player_setSpaceid(p, spaceid);
    Player_setCoordinateX(p, x);
    Player_setCoordinateY(p, y);
    return p;
}















