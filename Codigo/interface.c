#include "interface.h"

struct _Interface{

	sc_rectangle *board;/*Rectangle where the map is shown*/
	sc_rectangle *display;/*Rectangle where the inventory/Notes... are display*/
	sc_rectangle *command;/*Rectangle where the player introduces the commands*/

	int bc;/*colums in board*/
	int br;/*rows in board*/
	int dc;/*colums in display*/
	int dr;/*columns in display*/
	int cc;/*columns in command*/
	int cr;/*rows in command*/

	char  cplayer;/*character of the player*/


};
Interface *i_create(int bc, int br, int dc, int dr, int cc, int cr
					, char cplayer);
