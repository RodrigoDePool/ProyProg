#include "player.h"
#define NDEBUG
#include <assert.h>
#include <string.h>
#define name(p) (p)->name


struct _Player{
	char *name;
	int spaceid;
	int coordx;
	int coordy;
}