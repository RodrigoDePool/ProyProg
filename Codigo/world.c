#include "world.h"
#define NDEBUG
#include <assert.h>

typedef _World{
	Space **spaces;
	int numspaces;
	Object **objects;
	int numobjects;
	Player *player;
}