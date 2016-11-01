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

	int bbkcl;/*background color of the board*/
	int bfgcl;/*foreground color of the board*/
	int dbkcl;/*background color of the board*/
	int dfgcl;/*foreground color of the board*/
	int cbkcl;/*background color of the board*/
	int cfgcl;/*foreground color of the board*/

	char  cplayer;/*character of the player*/


};

Interface *i_create(int bc, int br, int dc, int dr, int cc, int cr
					, char cplayer, int bbkcl, int bfgcl, int dbkcl, int dfgcl, 
					int cbkcl, int cfgcl){

	Interface * interface;
	interface=(Interface*)malloc(sizeof(Interface));
	iterface->bc=bc;
	interface->br=br;
	interface->dc=dc;
	interface->dr=dr;
	interface->cc=cc;
	interface->cr=cr;
	interface->cplayer=cplayer;

	interface->board=win_new()
	return interface;
}
