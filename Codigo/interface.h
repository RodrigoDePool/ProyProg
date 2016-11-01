#ifndef INTERFACE_H
#define INTERFACE_H
#define HERE 0
#define WEST 1
#define EAST 2
#define NORTH 3
#define SOUTH 4
#include <stdlib.h>
#include <stdio.h>
#include "rectangles.h"

typedef struct _Interface Interface;



/*	Creates an interface.
	Parameters: bc colums of the board (usable bc -2)
					The other two are used for margins
				br rows of the board (usuable br -2)
				dc colums of display...
				cr rows of command
				bkcl background colour of the board
				bfgkl foreground colour of the board
				the same with display and commands
	return: Pointer to Interface initialized
*/
Interface *i_create(int bc, int br, int dc, int cr, char cplayer,
					int bbkcl, int bfgkl, int dbkcl, int dfgcl,
					int cbkcl, int cfgcl);



/*
	Draws the Interface in the terminal
	Parameter: i Pointer to Interface
	returns: OK or ERR
*/
Status i_drawAll(Interface *i);



/*
	Draws a characrer in the board.
	Parameters:
		i Pointer to interface
		c character thats gonna be written
		br row in the board you wanna write the character in
		bc column in the board you wanna write the character in
	returns: OK or ERR
*/
Status i_drawChar(Interface *i, char c, int br, int bc);



/*
	Initilizes the position of the player in the board and draw it
	Paramters:
		i Pointer to interface
		br row in the board the player is in
		bc column in the board the player is in
	returns: OK or ERR
*/
Status i_drawPl(Interface *i,int br, int bc);


/*
	Moves the player in the map to the direction introduced
	Parameter:
		i pointer to interface
		dir integer with the direction to which you ll move
	returns: OK if it moved or ERR if its not possible to move
	ATTENTION THE PLAYER MUST HAVE BEEN INITIALIZED FIRST
*/
Status move(Interface *i,int dir);


/*
	frees an interface
	Parameters:
		Pointer to interface
	Does not clear the interface, it leaves it as it was before calling the
	function, you must clear it in the main, see : interfacetest.c

*/
void i_free(Interface *i);


#endif
