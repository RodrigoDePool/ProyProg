#include <stdio.h>
#include <stdlib.h>
#include "../../interface.h"

typedef struct _Numbers Numbers;

/*These two functions return a matrix after it being rotated 90º*/
int **matrix_rotateleft(int **matrix, int size);
int **matrix_rotateright(int **matrix, int size);

/*Function that returns the matrix after doing any movement*/
/*int **mv(int** matrix, int dir, int size, int *score, int *finished, int*won);*/

/*Function that returns the matrix after doing an horizontal movement
  pressleft: dir = 1
  pressright: dir = -1*/
int **hmove(int** matrix, int dir, int size, int *score, int *finished, int*won);

/*Function that returns the matrix after doing a vertical movement
  pressup: dir = 1
  pressdown: dir = -1*/
int **vmove(int** matrix, int dir, int size, int *score,int *finished, int *won);

/*After a movement, this function prepares the matrix for the next movement
(Checks if you have won/lost, and adds a new number to the matrix)*/
int ** prepares_for_next(int **matrix, int size, int* finished, int ch);

/* Draws on the interface all numbers of a given matrix, 
first version only available for SIZE FOUR */
int draw_matrix(Interface *i, int **matrix, Numbers *num, int size, int score);

/*main function*/
int mini2048(Interface *i);



/*Numbers functions*/

/*Allocs memory and initializes a Numbers from a file with this format
 2 ##number of files to be readed
 2
 2.txt
 4
 4.txt
 */
Numbers *Numbers_ini(char *file);

void Numbers_free(Numbers *num);

/*Returns de file name associated to a number*/
char *Numbers_getFile(int m, Numbers* num);

