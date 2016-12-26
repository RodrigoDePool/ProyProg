#include <stdio.h>
#include <stdlib.h>
#include <interface.h>

typedef struct _Numbers Numbers;

/*These two functions return a matrix after it being rotated 90º*/
int **matrix_rotateleft(int **matrix, int size);
int **matrix_rotateright(int **matrix, int size);


/*Function that returns the matrix after doing an horizontal movement
  pressleft: dir = 1
  pressright: dir = -1*/
int **hmove( int** matrix, int dir, int size, int *score);

/*Function that returns the matrix after doing a vertical movement
  pressup: dir = 1
  pressdown: dir = -1*/
int **vmove( int** matrix, int dir, int size, int *score);

/*After a movement, this function prepares the matrix for the next movement
(Checks if you have won/lost, and adds a new number to the matrix)*/
int ** prepares_for_next(int **matrix, int size);

/* Draws on the interface all numbers of a given matrix, SIZE FOUR */
int draw_matrix(interface *i, int **matrix, Numbers *num);




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

