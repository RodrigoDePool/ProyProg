#include "qa.h"
#define NDEBUG
#include <assert.h>
#define CLEANBOARD "blanco.txt"

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
	fscanf(f, "%m[^\n]\n", &(g->intro));
	if(g->intro == NULL){
		free(g);
		return NULL;
	}
	fscanf(f, "%d\n", &(g->nquestions));
	
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
	fscanf(f, "%m[^\n]\n", &(q->person));
	if(q->person == NULL){
		free(q);
		return NULL;
	}
	fscanf(f, "%m[^\n]\n", &(q->qu));
	if(q->qu == NULL){
		free(q->person);
		free(q);
		return NULL;	
	}
	fscanf(f, "%d\n", &(q->numans));
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
	fscanf(f, "%c %d ", &(a->code), &(a->truth));
	fscanf(f, "%m[^\n]\n", &(a->answer));
	if(a->answer == NULL){
		free(a);
		return NULL;
	}
	return a;
}

void game_free(Game *g){
	int i;
	if(g){
		if(g->intro){
			free(g->intro);
		}
		if(g->q){
			for(i = 0; i < g->nquestions; i++){
				if (g->q[i])
					question_free(g->q[i]);
			}
			free(g->q);
		}
		free(g);
	}
}

void question_free(Question *q){
	int i;
	if(q){
		if(q->person) free(q->person);
		if(q->qu) free(q->qu);
		if(q->ans){
			for(i = 0; i < q->numans; i++){
				if(q->ans[i])
					answer_free(q->ans[i]);
			}
		free(q->ans);
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

int answer_check(Interface *in, Question *q, int row, int col, char choice){
	assert(in && q && row > 0 && col > 0);
	int i;
	for (i = 0; i < q->numans; i++){
		if(q->ans[i]->code == choice){
			if(q->ans[i]->truth == 1){
				i_drawStr(in, "Correct answer!", row + 1, col, 1);
				sleep(1);
				return 1;
			}
			i_drawStr(in, "Incorrect answer!", row + 1, col, 1);
			return 0;
		}
	}
	/*If the choice didnt match any answer*/
	i_drawStr(in, "I couldnt find any answer matching your char choice, try again", 1+row, col, 1);
	sleep(2);
	i_drawStr(in, "                                                              ", 1+row, col, 1);
	return -1;
	
}

int qa(Interface *in, char *path){
	assert(path);
	int i, j, row, col, size, result;
	char *buff, *intro, choice;
	FILE *f;
	f = fopen(path, "r");
	
	if(f == NULL){
		return -1;
	}
	Game *g = game_ini(f);
	fclose(f);
	if(g == NULL){
	return -1;
	}
	/*We build and ask each question*/
	for(i = 0; i < g->nquestions; i++){
		row = 5;
		col = 10;
		/*Build intro using a cop function*/
		/*First we replace the person name,then the question between " "*/
		intro = unpack_answer(g->intro, g->q[i]->person, '*' );
		buff = unpack_answer(intro, g->q[i]->qu,')');
		free(intro);
		/*We have to add a \n at the end of the question*/
		size = 1 + strlen(buff);
		intro = (char *)malloc((size + 1)*sizeof(char));
		if(intro == NULL){
			free(buff);
			game_free(g);
			return -1;
		}
		
		strcpy(intro, buff);
		intro[strlen(buff)+1] = '\n';
		intro[strlen(buff) + 2] = '\0';
		/*Clean board to erase previous question*/
		i_readFile(in, "blanco.txt", 0, 0, 1);
		
		/*Ask question and check the answer*/
		i_drawStr(in, intro, row, col, 1);
		free(intro);
		free(buff);
		
		for(j = 0; j < g->q[i]->numans; j++){
			i_writeChar(in, g->q[i]->ans[j]->code, ++row, col, 1);
			i_writeChar(in, ' ' , row, col + 1, 1);			
			i_drawStr(in, g->q[i]->ans[j]->answer, row, col + 2, 1);
		}
		
		
		do{
		choice = _read_key();
		if(choice == 'q'){
			sleep(1);
			game_free(g);
			return 0;
		}
		result = answer_check(in, g->q[i], 1+row, col, choice);
		}while (result == -1);
		if(result == 0){
			sleep(2);
			game_free(g);
			return 0;
		}
		
	}
	
	/*If the game hasnt returned yet, its because all the answers were correct:
	return 1*/
	i_drawStr(in, "All your answers were correct: you won!", row+2, col, 1);
	sleep(2);
	game_free(g);
	return 1;
}



















