#ifndef INTERFACE_H
#define INTERFACE_H
#define WEST 1
#define EAST 2
#define NORTH 3
#define SOUTH 4

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
Status draw(Interface *i);


/*
	Moves the player in the map to the direction introduced
	Parameter: 
		i pointer to interface
		dir integer with the direction to which you ll move
	returns: OK if it moved or ERR if its not possible to move
*/
Status move(Interface *i,int dir);

#endif