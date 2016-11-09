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
	Parameters:
	 			bc colums of the board (the first one is not usable, left limit)
				br rows of the board (the first one is not usable, top limit)

				dc colums of display (the fist one and last one are not usable)
														 (limit between board and display, and right limit)
			  the rows of the display are the same as the board, with the same limitation

				cr rows of command (The first and last row are not usable, they are limits) 
				the colums are equal to dc+bc , being the first and last one limitations

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
*/
void i_drawAll(Interface *i);



/*
	Draws a string in the board/display/command.
	Parameters:
		i Pointer to interface
		s the string thats gonna be written
		r row in the board/display/command you wanna start to write the string
		c column in the board/display/command you wanna start to write the string
		bdc :
			1 draws in board
			2 draws in display
			3 draws in command
	 if the string exceeds the rectangle it cuts it down
	 if the r or c exceeds the limits usable of the board/display/command
	 it wont do anything
*/
void i_drawStr(Interface *i, char *s, int r, int c,int bdc);


/*
	Sets the map in the board. If the map does not have br-1 rows and bc-1 colums
	the behaviour of this function is unexpected
	Parameters:
		i Pointer to interface
		map matrix with the ascii characters of the map in order
	ATTENTION: it creates a COPY of the map, this copy will be freed in i_free
	THE MAP IS SET SO THE POINT IN THE BOARD (1,1) IS (0,0) IN THE MAP
*/
void i_setMap(Interface *i,char **map);


/*
	Initilizes the position of the player in the board and draws it
	only if its possible. You must have initialized the board first
	THE COORDS PASSED ARE MAP COORDS NOT BOARD ONES
	Paramters:
		i Pointer to interface
		br row in the map the player is in (DIFFERENT FROM THE BOARD COORDS)
		bc column in the map the player is in (DIFFERNT FROM THE BOARD COORDS)
	returns:
		1 if it was possible to place the player
		0 if it was not possible

*/
int i_drawPl(Interface *i,int br, int bc);


/*
	Moves the player in the map to the direction introduced
	Parameter:
		i pointer to interface
		dir integer with the direction to which you ll move
	ATTENTION THE PLAYER MUST HAVE BEEN INITIALIZED FIRST.
	The player wont move if the place it want to moves to is not a space
*/
void move(Interface *i,int dir);


/*
	frees an interface
	Parameters:
		Pointer to interface
	It clears the interface and it also, and this is very important, free's the map.

*/
void i_free(Interface *i);



/*
	Sets the background color of the board and draws the board again
	Parameters:
		i Pointer to interface
		bbkcl integer of the backgroundcolor
*/
int i_setBackgroundColor(Interface *i,int bbkcl);



/*
	Sets the foreground color of the board and draws the board again
	Parameters:
		i Pointer to interface
		bbkcl integer of the foregroundcolor
*/
int  i_setForegroundColor(Interface *i,int bfgcl);



/*
	Function that draws a character in Board/Display/Command with NORMAL COORDS
	NOT MAP COORDS. THE CHARACTER MUST NOT BE WRITTEN IN THE MAP, FOR THAT THERE
	IS ANOTHER FUNCTION.
	Paramters:
		i pointer to the interface.
		c character thats gonna be written
		r row in the board/display/command you wanna start to write the character
		col column in the board/display/command you wanna start to write the character
		bdc :
			1 draws in board
			2 draws in display
			3 draws in command
	returns: constant 1
*/
int i_writeChar(Interface *i,char c,int r, int col, int bdc);



/*
	Function that writes a character in the map with MAP COORDS and draws it on 
	the board. THE CHARACTER MUST  BE WRITTEN IN THE MAP.
	Paramters:
		i pointer to the interface.
		c character thats gonna be written
		r row in the map you wanna start to write the character
		col column in the map you wanna start to write the character
	returns: constant 1
*/
int i_writeCharMap(Interface *i,char c,int r, int col);



#endif
