#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct _Interface Interface;

/*	Creates an interface:
	Parameters: bc colums of the board (usable board -2)

*/
Interface *i_create(int bc, int br, int dc, int dr, int cc, int cr);


#endif