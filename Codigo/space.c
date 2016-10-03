struct space_{
	int sId;
	int neighbour[8];
	char *shortDesc;
	char *longDesc;
	bool light;
	bool isLocked[8];
	char ** map;
	int rows, cols;
}Space;

char *sDesc(Space * s){
	return s->shortDesc;
}

char *lDesc(Space * s){
	return s->lDesc;
}

int space_ neighbour( Space *s, int n)