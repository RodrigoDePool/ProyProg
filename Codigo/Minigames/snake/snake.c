#include "snake.h"
#include <pthread.h>
#include <unistd.h>
#include "../../interface.h"
#define WIN               1
#define LOSE              0
#define SNAKE_CHARACTER  '@'
#define POINT_CHARACTER  'O'
#define SNAKE_MAX_SIZE 22

int flag_snakeResult = 0; /*Global flag, manages the game result. Treat carefully*/
char key_read = NORTH; /*Needed to keep the snake moving without pressing keys*/


typedef struct Dot {
	int row;
	int col;
	} Dot;

typedef struct Snake {
	Dot** body;
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
	int i;
	Snake *s = (Snake*) malloc(sizeof(Snake));
	s->body = (Dot**) malloc(sizeof(Dot*)*SNAKE_MAX_SIZE);
	for (i=0; i<8; i++){
	s->body[i] = dot_ini (row+i, col);
	}
	s->tamanio = i;
	return s;
}

void snake_free(Snake* s)
{
	int i;
	for (i=0; i<s->tamanio; i++)
		dot_free(s->body[i]);
	free(s->body);
	free(s);
}
/*More or less complex functions*/
int snake_moveHead(Interface *i, int row, int col, Snake *s)
{
	int index;
	char point;

	if (row < 10 || col < 33 || col > 78 || row > 22){
	return -1; /*If you hit a wall you lose*/
	}

	point = i_whatCaractHere(i, row, col);

	if (point == SNAKE_CHARACTER){
	return -1; /*If you hit yourself you lose*/
	}
	i_writeCharMap(i, SNAKE_CHARACTER, row, col, 1);


	if (point != POINT_CHARACTER) /*If you dont eat a point, you move one forward*/
		i_writeCharMap(i, ' ', dot_getRow(s->body[s->tamanio-1]), dot_getCol(s->body[s->tamanio-1]), 1);

	else{ /*If you do, you add a dot to the snake*/
		Dot *d = dot_ini(dot_getRow(s->body[s->tamanio-1]), dot_getCol(s->body[s->tamanio-1]));
		s->tamanio++;
		s->body[s->tamanio-1] = d;
	}

	for (index=s->tamanio-1; index>0; index--) /*Sliding movement*/
		dot_setCoordinates(s->body[index], dot_getRow(s->body[index-1]), dot_getCol(s->body[index-1]));

	dot_setCoordinates(s->body[0], row, col); /*Head movement*/

	return 0;
}

int snake_move(Snake *s, Interface *i, int dir)
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
        return -2;
    }
}




void *snake_play(void *interface) /*This function will move the snake according to the player commands*/
{
	Interface *i = (Interface *) interface;
	int aux, index;
	char buff;
	Snake *s = snake_ini(15, 60);
	for (index=0; index<8; index++){
		i_writeCharMap(i, SNAKE_CHARACTER, 15+index, 60, 1);
	}
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
					snake_free(s);
					flag_snakeResult = -1;
					return NULL;
			    }
			    else if (aux == -2){
					snake_free(s);
					flag_snakeResult = -2;
					return NULL;
			    }
			    usleep(100000); /*soft delay between movements*/
			}
			if (s->tamanio == SNAKE_MAX_SIZE){ /*The player wins when his snake reaches a size of 15 dots*/
			    snake_free(s);
			    flag_snakeResult = 1;
			    return NULL;
			}
	   	 }
	return NULL;
}

/*Separating the functions read_keys and snake_play will make the snake automatically*/
/*move to the last direction issued, giving the game the feeling of the old school snake*/

void *read_keys() /*This function will read the keys pressed by the player*/
{
	while(flag_snakeResult==0) key_read = _read_key();
	return NULL;
}


void *snake_points(void *interface) /*This function will print points on the board*/
{
	Interface *i = (Interface *) interface;
	int index, row, col;
	srand(time(NULL)); /*Randomizes the seed*/
	for (index=0; index<14; index++){
		if (flag_snakeResult != 0) return NULL;
		row = rand()%12 + 11;
		col = rand()%46 + 33;
		while(i_whatCaractHere(i, row, col) == SNAKE_CHARACTER){
			row = rand()%12 + 11;
			col = rand()%46 + 33;
		}
		i_writeCharMap(i, POINT_CHARACTER, row, col, 1);
		sleep(4);
	}
	return NULL;
}



/*Game function*/
int snake(Interface *i)
{
	flag_snakeResult = 0;
	key_read = NORTH;
	i_cleanMap(i);
	i_readFile(i, "map.txt", 9, 32, 1); /*48x15*/
	i_drawAll(i);
	i_cleanDisplay(i);
	i_cleanCommand(i);
	pthread_t juego[3];
	pthread_create(&(juego[0]), NULL, snake_play, (void*) i); /*The function that will move the snake*/
	pthread_create(&(juego[1]), NULL, read_keys, NULL); /*The function that will move the snake*/
	pthread_create(&(juego[2]), NULL, snake_points, (void*) i); /*The function that will place the points*/

	while (flag_snakeResult == 0);

	if (flag_snakeResult == 1) return WIN;
	else if (flag_snakeResult == 0) return LOSE;
	return ERR;
}
