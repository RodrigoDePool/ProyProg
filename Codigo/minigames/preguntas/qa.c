#include "qa.h"
#define NDEBUG
#include <assert.h>


struct _Game{
	char *intro;
	int nquestions;
	Question **q;
};

struct _Question{
	char *person;
	char *qu;
	int numans;
	Answer **ans;
};

struct _Answer{
	char code;	
	int truth;
	char *answer;
};


Game *game_ini(FILE *f){
	assert(f);
	int i, j;
	Game *g;
	g = (Game *)malloc(sizeof(Game));
	if( g == NULL) return NULL;
	fscanf(f, "%m[^\n]\n", g->intro);
	if(g->intro == NULL){
		free(g);
		return NULL;
	}
	fscanf("%d\n", &g->nquestions);
	
	/*Scan all the questions*/
	g->q = (Question **)malloc(g->nquestions * sizeof(Question *));
	for(i = 0; i < g->nquestions; i++){
		if((g->q[i] = question_ini(f)) == NULL){
			for(j = 0; j < i; j++){
				question_free(g->q[j]);
			}
			free(g->q);
			free(g);
			return NULL;
		}
	}
	
	return g;

}

Question *question_ini(FILE *f){
	assert(f);
	int i, j;
	Question *q = (Question *)malloc(sizeof(Question));
	if(q == NULL) return NULL;
	fscanf(f, "%m[^\n]\n", q->person);
	if(q->person == NULL){
		free(q);
		return NULL;
	}
	fscanf(f, "%m[^\n]\n", q->qu);
	if(q->qu == NULL){
		free(q->person);
		free(q);
		return NULL;	
	}
	fscanf("%d\n", &q->numans);
	q->ans = (Answer **)malloc(q->numans * sizeof(Answer *));
	if(q->ans == NULL){
		free(q->qu);
		free(q->person);
		free(q);
		return NULL;	
	
	}
	
	/*scan all the answers*/
	for(i = 0; i < q->numans; i++){
		if((q->ans[i] = answer_ini(f)) == NULL){
			for(j = 0; j < i; j++){
				answer_free(q->ans[j]);
			}
			free(q->ans);
			free(q->qu);
			free(q->person);
			free(q);
			return NULL;
		}
	}
	return q;

}
Answer *answer_ini(FILE *f){
	assert(f);
	Answer *a = (Answer *)malloc(sizeof(Answer));
	if(a == NULL) return NULL;
	fscanf("%c %d ", &a->code, &a->truth);
	fscanf(f, "%m[^\n]\n", a->answer);
	if(a->answer == NULL){
		free(a);
		return NULL;
	}
}

void game_free(Game *g){
	int i;
	if(g){
		if(g->intro){
			free(free(g->intro));
		}
		for(i = 0; i < g->nquestions; i++){
			if (g->q[i])
				question_free(g->q[i]);
		}
		free(g);
	}
}

void question_free(Question *q){
	int i;
	if(q){
		if(q->person) free(q->person);
		if(q->qu) free(q->qu);
		for(i = 0; i < q->numans; i++){
			if(q->ans[i])
				answer_freeI(q->ans[i]);
		}
		free(q);
	}
}

void answer_free(Answer *a){
	if(a){
		if(a->answer)
			free(a->answer);
		free(a);
	}
}




















