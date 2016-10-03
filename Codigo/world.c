#include "world.h"
#define NDEBUG
#include <assert.h>

struct _World{
	Space **spaces;
	int numspaces;
	Object **objects;
	int numobjects;
	Player *player;
}