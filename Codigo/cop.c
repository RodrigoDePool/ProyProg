#include "cop.h"
#include <assert.h>

#define NDEBUG

/*EXAMPLE OF THE FILE THIS MODULE WILL READ*/
/*
	2 ##Num of commands to read
	draw * ##typed command, could change
	internal_draw ##wont change
	1 ##num of possible answers
	I'll draw * when I find my pencils
	paint *
	internal_paint
	2
	I wont paint *
	Ive already painted *
*/

/*Stores an internal string which we associate to a function*/
typedef struct _Assoc {
	char *int_name;
	pfun f;
	
};

/*Stores a command which we associate to an internal string, and to the possible
 answers it may return*/
typedef struct _Ext{
	char *ext_name;
	char *int_name;
	int n_ans;
	char **ans;
};

/*Stores an array of assocs, as well as an array of exts an the number of
 elements in each array*/
typedef struct _CoP {
	int numassocs;
	Assoc **assocs;
	int numexts;
	int maxexts; /*Ask Santini why this is necessary*/
	Ext **exts;
};




/******* LOCAL FUNCTIONS *******/


/******* FUNCTIONS ********/
CoP *CoP_ini(FILE *f){
	assert(f);
	
	int nassocs nexts;
	Ext **e;
	CoP *c = NULL;
	c = (CoP*)malloc(sizeof (CoP));
	if(!c) return NULL;
	
	fscanf(f, "%d\n", &nexts);
	e = (Ext **)malloc(nexts * sizeof(Ext *);
	if(!e){
		free(c);
		return NULL;
	}
}



































