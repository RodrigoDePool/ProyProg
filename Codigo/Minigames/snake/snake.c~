#include "snake.h"
#include <pthread.h>
#include <unistd.h>
#include "../../interface.h"
#define WIN               1
#define LOSE              0
#define SNAKE_CHARACTER  '@'
#define POINT_CHARACTER  'O'

int flag_snakeResult = 0; /*Global flag, manages the game result. Treat carefully*/
char key_read; /*Needed to keep the snake moving without pressing keys*/


typedef struct Dot {
	int row;
	int col;
	} Dot;

typedef struct Snake {
	Dot* body;
	int tamanio;
	} Snake;

/*Basic Functions*/
Dot *dot_ini(int row, int col)
{
	Dot *d = (Dot *) malloc (sizeof(Dot));
	if (d == NULL) return NULL;
	d->row = row;
	d->col = col;
	return d;
}

void dot_free(Dot *d)
{
	free (d);
}


int dot_getCol(Dot *d)
{
	return d->col;
}

int dot_getRow(Dot *d)
{
	return d->row;
}


void dot_setCoordinates(Dot *d, int row, int col)
{
	d->row = row;
	d->col = col;
}


Snake *snake_ini(int row, int col)
{
	Snake *s = (Snake*) malloc(sizeof(Snake));
	s->body = dot_ini (row, col);
	s->tamanio = 1;
	return s;
}

void snake_free(Snake* s)
{
	int i;
	for (i=0; i<s->tamanio; i++)
		dot_free(s->body[i]);
	free(s);
}
/*More or less complex functions*/
int snake_moveHead(Interface *i, int row, int col, Snake *s)
{
	int aux, index;
	char point;	
	if (row < 1 || col < 1) return -1; /*If you hit a wall (belonging to the board) you lose*/
	point = i_whatCaractHere(i, row+1, col+1);
	if (point == SNAKE_CHARACTER) return -1; /*If you hit yourself you lose*/
	aux = i_writeChar(i, SNAKE_CHARACTER, row, col, 1);
	if (aux == -1) return -1; /*If you hit a wall (not belonging to the board) you lose*/
	if (point != POINT_CHARACTER) /*If you dont eat a point, you move one forward*/
		i_writeChar(i, ' ', dot_getRow(s->body[s->tamanio-1]), dot_getCol(s->body[s->tamanio-1]), 1); 
	else{ /*If you do, you add a dot to the snake*/
		Dot *d = dot_ini(dot_getRow(s->body[s->tamanio-1]), dot_getCol(s->body[s->tamanio-1])); 
		s->tamanio++;
		s->body[s->tamanio-1] = d;
	}
	for (index=0; index<s->tamanio; index++) /*Sliding movement*/
		s->body[index+1] = s->body[index];
	dot_setCoordinates(s->body[0], row, col); /*Head movement*/
	return 0;
}

int snake_move(Snake *s,Interface *i, int dir)
{
    if (i == NULL)
        return -1;
    switch (dir)
    {
    case NORTH:
        return snake_moveHead(i, dot_getRow(s->body[0])-1, dot_getCol(s->body[0]), s);
    case WEST:
        return snake_moveHead(i, dot_getRow(s->body[0]), dot_getCol(s->body[0])-1, s);
    case SOUTH:
        return snake_moveHead(i, dot_getRow(s->body[0])+1, dot_getCol(s->body[0]), s);
    case EAST:
        return snake_moveHead(i, dot_getRow(s->body[0]), dot_getCol(s->body[0])+1, s);
    default:
        return -1;
    }
}

	
	

void *snake_play(void *interface) /*This function will move the snake according to the player commands*/
{ 
	Interface *i = (Interface *) interface;
	int aux;
	char buff;
	Snake *s = snake_ini(17, 60);
	i_writeChar(i, SNAKE_CHARACTER, 17, 60, 1);
	while (1)
	    	{
			if (key_read == 'q' || key_read == 'Q')
			{
			    snake_free(s);
			    flag_snakeResult = -1;
			    return NULL;
			}
			if (key_read == WEST || key_read == EAST || key_read == NORTH || key_read == SOUTH) 
			{
			    buff = key_read;
			    aux = snake_move(s, i, buff);
			    if (aux == -1){
				snake_free(s)
				flag_snakeResult = -1;
				return NULL;
			    }
			    sleep(0.5); /*soft delay between movements*/
			}
			
			if (s->tamanio == 15){ /*The player wins when his snake reaches a size of 15 dots*/
			    flag_snakeResult = 1;
			    snake_free(s);
			    return NULL;
			}
	   	 }
	return NULL;
}

/*Separating the functions read_keys and snake_play will make the snake automatically*/
/*move to the last direction issued, giving the game the feeling of the old school snake*/

void *read_keys() /*This function will read the keys pressed by the player*/
{ 
	while(1) key_read = _read_key();
	return NULL;
}


void *snake_points(void *interface) /*This function will print points on the board*/
{ 
	Interface *i = (Interface *) interface;
	int index;
	srand(time(NULL)); /*Randomizes the seed*/
	for (index=0; index<15; index++){
		i_writeChar(i, POINT_CHARACTER, rand()%34 + 1, rand()%112 + 1, 1);
		sleep(10);
	}
	return NULL;
}



/*Game function*/
int snake(Interface *i)
{
	pthread_t juego[3];
	pthread_create(&(juego[0]), NULL, snake_play, (void*) i); /*The function that will move the snake*/
	pthread_create(&(juego[1]), NULL, read_keys, NULL); /*The function that will move the snake*/
	pthread_create(&(juego[2]), NULL, snake_points, (void*) i); /*The function that will place the points*/
	
	while (flag_snakeResult == 0);

	if (flag_snakeResult == 1) return WIN;
	else if (flag_snakeResult == -1) return LOSE;
	return ERR;	
}












