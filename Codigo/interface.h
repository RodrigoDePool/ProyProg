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
#include <termios.h>

typedef struct _Interface Interface;


struct termios initial;

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
	Draws the Interface in the terminal: first it clears the whole interface,
	then it draws the map, mapDiplay and mapCommand and finally, it draws the limits
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
	 it prints in the rectangle BUT NOT in the maps
*/
void i_drawStr(Interface *i, char *s, int r, int c,int bdc);

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
	 If the string exceeds the rectangle it cuts it down
	 If the r or c exceeds the limits usable of the board/display/command
	 it wont do anything
	 It prints a copy of s in the maps and executes i_drawALl(i), it does not,
	 however, allocate any memory, nor use the memory in s.
	 You may free s with no fear in case it is dynamic.
	 Also, the coords should be in MAP coords, NOT rectangle coords
*/
void i_drawStrMap(Interface *i, char *s, int r, int c,int bdc);
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
	Frees the map in the interface.
	Paramters:
		i: the interface with the map we want to free
*/

void i_freeMap(Interface * i);

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
	It clears the interface and it also, and this is very important, free's the maps.

*/
void i_free(Interface *i);



/*
	Sets the background color of the bcd and executes i_drawAll again
	Parameters:
		i Pointer to interface
		bbkcl: integer of the backgroundcolor
		bdc: 1 in the board 2 in display 3 command

	Returns: 0 OK -1 Error
*/
int i_setBackgroundColor(Interface *i,int bbkcl, int bdc);



/*
	Sets the foreground color of the bcd and runs i_drawAll(
		Parameters:
			i Pointer to interface
			bbkcl integer of the foregroundcolor)
			bdc: 1 in the board 2 in display 3 command

	Returns: 0 OK -1 Error
*/
int  i_setForegroundColor(Interface *i,int bfgcl, int bdc);



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
	returns:  0 OK -1 Error
*/
int i_writeChar(Interface *i,char c,int row, int col, int bdc);

/*
	Gets the Row where the player is.
	Parameters: i: pointer to the interface.
	Returns: -1 Error, anything else OK.
*/
int i_wherePlayerBeRow(Interface * i);

/*
	Gets the Col where the player is.
	Parameters: i: pointer to the interface.
	Returns: -1 Error, anything else OK.
*/
int i_wherePlayerBeCol(Interface * i);

/*
	Gets the char in the given position of the map in the board.
	Parameters: i: pointer to the interface.
				r: row of the char we want
				c: column of the char we want
	Returns: '0' Error, anything else OK.
*/
char i_whatCaractHere(Interface * i, int r, int c);

/*
	Gets bc from interface
	Parameters: i: inteface to get from
	Returns: the requested number or -1 if ERROR or not initialized.
	NOTE: BOARD COORDS
*/
int i_getbc(Interface * i);

/*
	Gets dc from interface
	Parameters: i: inteface to get from
	Returns: the requested number or -1 if ERROR or not initialized.
	NOTE: BOARD COORDS
*/
int i_getdc(Interface * i);

/*
	Gets br from interface
	Parameters: i: inteface to get from
	Returns: the requested number or -1 if ERROR or not initialized.
	NOTE: BOARD COORDS
*/
int i_getbr(Interface * i);

/*
	Gets cr from interface
	Parameters: i: inteface to get from
	Returns: the requested number or -1 if ERROR or not initialized.
	NOTE: BOARD COORDS
*/
int i_getcr(Interface * i);

/*
	Gets pc from interface
	Parameters: i: inteface to get from
	Returns: the requested number or -1 if ERROR or not initialized.
	NOTE: MAP COORDS
*/
int i_getpc(Interface * i);

/*
	Gets pr from interface
	Parameters: i: inteface to get from
	Returns: the requested number or -1 if ERROR or not initialized.
	NOTE: MAP COORDS
*/
int i_getpr(Interface * i);

/*
	Gets cplayer from interface
	Parameters: i: inteface to get from
	Returns: the requested char or 0 if ERROR or not initialized.
*/
char i_getCPlayer(Interface * i);

/*
	This function cleans the display map leaving it all in blank spaces.
*/
void i_cleanDisplay(Interface *i);

/*
	This function cleans the command map leaving it all in blank spaces.
*/
void i_cleanCommand(Interface *i);

/*
	This function reads the info from a file
	and writes it in the MAP given by bdc code,
 starting in the row and column indicated
	Parameters:
		i Pointer to interface
		s path to the  file
		row is the row in which file will start writing down the file
		col is the same but with column
		bdc if 1 it writes in boardMap, 2 in DisplayMap, 3 in CommandMap
	NOTE:
		The file must have the text in such a way it fits
		the map, otherwise the text could be cutted and fitted
		into the map.
	NOTE 2:
		The reading of the file will end as soon as it finds a blank line.
		if you wish to have a line between info in the text just
		introduce a space (' ') in the blank line and then start the new line.
*/
void i_readFile(Interface *i, char *s, int row, int col,int bdc);

/*FUNCTIONS OF GENERAL USE BY OTHER STRUCTURES*/
/*
  Reads a key from the keyboard. If the key is a "regular" key it
  returns its ascii code; if it is an arrow key, it returns one of the
  four interface directions with the "minus" sign
*/
int _read_key();
/*
  Initializes the terminal in such a way that we can read the input
  without echo on the screen
*/
void _term_init();/*Initializes the terminal*/

/*
	Sets the terminal back to normality after doing a _term_init()
*/
void _term_close();

#endif
