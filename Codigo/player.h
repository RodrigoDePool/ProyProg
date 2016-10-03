#ifndef PLAYER_H
#define PLAYER_H
#include <stdlib.h>
#include "types.h"

typedef struct _Player Player;

Player *player_ini();

void player_free();


#endif