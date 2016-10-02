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

