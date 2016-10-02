typedef struct space_ Space;

char **whatisinmap(Space *c, int *s);
bool canIsee(Space *s);
int go(Space *s, int dir);
int unlock(Space *s, int dir, int status);
char sDesc(Space * s);
	
