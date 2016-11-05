#include "cop.h"
#define NDEBUG
#include <assert.h>
#define MAX_STR 500


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
Ext *ext_ini(FILE *f){
	assert(f);
	char *extname, *intname, **answers;
	int numans, i, j;
	Ext *e = (Ext*)malloc(sizeof(Ext));
	if(!e) return NULL;
	
	/*Read ext from file (format is after #defines*/
	/*This strange way of reading strings will read EVERYTHING it reads till
	it finds a \n and store it in the CHAR** given afterwards, allocating
	sufficient memory for it. Then, itll read the /n */
	fscanf(f, "%m[\n]\n", &extname);
	fscanf(f, "%m[\n]\n", &intname);
	fscanf(f, "%d\n", &numans);
	answers = (char **)malloc(numans * sizeof(char*));
	if(!answers){
		free(extname);
		free(intname);
		free(e);
		return NULL;
	}
	for(i = 0; i<numans; i++){
		fscanf(f, "%m[^\n]\n", &(answers[i]));
		if(!answers[i]){
			for (j = 0; j<i; j++)
				free(answers[j]);
			free(answers);
			free(extname);
			free(intname);
			free(e);
			return NULL;
		}		
	}
	
	
}

void ext_free( Ext *e){

}

CoP *cop_ini(FILE *f){
	assert(f);
	
	int n_assocs n_exts, i, j;
	char *bu
	Ext **e;
	CoP *c = NULL;
	c = (CoP*)malloc(sizeof (CoP));
	if(!c) return NULL;
	
	/*Start reading file*/
	fscanf(f, "%d\n", &n_exts);
	CoP->numexts = n_exts;
	e = (Ext **)malloc(n_exts * sizeof(Ext *);
	if(!e){
		free(c);
		return NULL;
	}
	for(i = 0; i < n_exts; i++){
		e[i] = ext_ini(f);
		if(!e[i])}
			for(j = 0; j<i; j++)
				ext_free(e[j]);
			free(e);
			free(CoP);
			return NULL;			
		}
		
	
	}
	
}



































