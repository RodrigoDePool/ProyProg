#include "snake.h"
#define SNAKE_CHARACTER 'S'
#define POINT_CHARACTER 'O'
typedef struct Dot {
	int row;
	int col;
	} Dot;

typedef struct Snake {
	Dot** body;
	int tamanio;
	} Snake;

Dot *dot_ini(int row, int col)
{
	Dot *d = (Dot *) malloc (sizeof(Dot));
	if (d == NULL) return NULL;
	d->row = row;
	d->col = col;
	return d;
}

Dot dot_free(Dot *d)
{
	free (d);
}


int* dot_getCol(Dot *d)
{
	return d->col;
}

int* dot_getRow(Dot *d)
{
	return d->row;
}


void dot_setCoordinates(Dot *d, int row, int col)
{
	d->row = row;
	d->col = col
}


Snake *snake_ini(int* coordinates)
{
	Snake *s = (Snake*) malloc(sizeof(Snake));
	s->body[0] = dot_ini (coordinates);
	tamanio = 1;
	return s;
}

void snake_free(Snake* s)
{
	int i;
	for (i=0; i<s->tamanio; i++)
		dot_free(s->body[i]);
	free(s);
}

void snake_move(Snake *s,Interface *i, int dir)
{
    int aux;
    if (i == NULL)
        return;
    if (i->pr == -1)
        return;
    switch (dir)
    {
    case NORTH:
        return;
    case WEST:
        aux = i_drawPl(i, i->pr, i->pc - 1);
        if (aux == 1)                                               /*if you were able to move delete the previous player postion*/
        {
            win_write_char_at(i->board, i->pr + 1, i->pc + 2, ' '); /*Previous position in board coords*/
            i->map[i->pr][i->pc + 1] = ' ';                         /*Setting a space in previous pposition*/
        }
        return;
    case SOUTH:
        aux = i_drawPl(i, i->pr + 1, i->pc);
        if (aux == 1)                                           /*if you were able to move delete the previous player postion*/
        {
            win_write_char_at(i->board, i->pr, i->pc + 1, ' '); /*Previous position in board coords*/
            i->map[i->pr - 1][i->pc] = ' ';                     /*Setting a space in previous pposition*/
        }
        return;
    case EAST:
        aux = i_drawPl(i, i->pr, i->pc + 1);
        if (aux == 1)                                           /*if you were able to move delete the previous player postion*/
        {
            win_write_char_at(i->board, i->pr + 1, i->pc, ' '); /*Previous position in board coords*/
            i->map[i->pr][i->pc - 1] = ' ';                     /*Setting a space in previous pposition*/
        }
        return;
    default:
        return;
    }
}

void snake_moveHead(Interface *i, int row, int col, Snake *s)
{
	int aux, i;
	char point;	
	if (row < 1 || col < 1) return -1;
	point = i_whatCaractHere(i, row+1, col+1);
	if (point == SNAKE_CHARACTER) return -2 
	aux = i_writeChar(i, SNAKE_CHARACTER, row, col, 1);
	if (aux == -1) return -1;
	if (point != POINT_CHARACTER)
		i_writeChar(i, ' ', dot_getRow[s->body[s->tamanio-1]], dot_getCol[s->body[s->tamanio-1]], 1);
	for (i=0; i<s->tamanio; i++)
		s->body[i+1] = s->body[i];
	dot_setCoordinates(s->body[0], row, col);
}
	


			
	







i_writeChar(Interface *i, char c, int row, int col, int bdc)































