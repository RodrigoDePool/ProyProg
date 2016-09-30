typedef struct space_{
	int sId;
	int neighbour[8];
	char *shortDesc;
	char *longDesc;
	bool light;
	bool isLocked[8];
	char ** map;
	int rows, cols;
}Space;

	char **whatisinmap(Space *c, int *s);
	bool canIsee(Space *s);
	int go(Space *s, int dir);
	int unlock(Space *s, int dir, int status);
	char sDesc(Space * s);
	
