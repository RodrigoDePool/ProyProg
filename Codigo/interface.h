#ifndef INTERFACE_H
#define INTERFACE_H

typedef struct _Interface Interface;

/*	Creates an interface:
	Parameters: bc colums of the board (usable bc -2)
					The other two are used for margins
				br rows of the board (usuable br -2)
				dc colums of display...
				dr rows of display...
				cc columns of commandline...
				cr rows of ...
	return: Pointer to Interface initialized
*/
Interface *i_create(int bc, int br, int dc, int dr, int cc, int cr
					, char cplayer);


#endif