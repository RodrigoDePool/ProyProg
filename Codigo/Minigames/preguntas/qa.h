#include "../../interface.h"
/*#include "../../cop.h"*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct _Game Game;
typedef struct _Question Question;
typedef struct _Answer Answer;

/*These three functions alloc memory for a game struct and initialises it with the info given in 
file like this:

Imagine * says "\", what would you answer? //Introductory sentence
2 //Numero de preguntas
Lucia //preguntadora
¿Estoy guapa? //Pregunta
3 //Número de posibles respuestas

a 1 Si, como siempre. //carácter=codigo+ 1True/0False + respuesta
b 0 Más fea que nunca.
c 0 y a ti q te importa
Lucia
¿Ere hilipolla?
2
a 0 No
b 1 Andre y aleho zi


Returns: pointer to the game/question/answer or NULL in case of error
*/
Game *game_ini(FILE *f);
Question *question_ini(FILE *f);
Answer *answer_ini(FILE *f);


/*These three functions free the memory allocated for the given structs and all its
members
Parameters: pointer to the structure to freed*/
void game_free(Game *g);
void question_free(Question *q);
void answer_free(Answer *a);

/*Executes the LUCIA game: returns 1 if won, 0 if lost, -1 in case of error */
int lucia(Interface *in);

/*Executes the QUESTIONS game: returns 1 if won, 0 if lost, -1 in case of error
                                IMPORTANT
 If the number of questions is n, the .txt should have "n+1" in the second line
 (the nquestions line)  AND have an extra question at the end of the file*/
int questions(Interface *in);
