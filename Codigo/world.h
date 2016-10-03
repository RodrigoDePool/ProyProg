#ifndef WORLD_H
#define WORLD_H
#include <stdlib.h>
#include "types.h"
#include "space.h"
#include "player.h"
#include "object.h"

typedef struct _World World;

World *world_ini();

void world_free(World *);

#endif