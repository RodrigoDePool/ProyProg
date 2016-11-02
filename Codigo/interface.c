#include "interface.h"

struct _Interface{

	sc_rectangle *board;/*Rectangle where the map is shown*/
	sc_rectangle *display;/*Rectangle where the inventory/Notes... are display*/
	sc_rectangle *command;/*Rectangle where the player introduces the commands*/

	int bc;/*colums in board*/
	int br;/*rows in board*/
	int dc;/*colums in display*/
	/*rows in display are the same rows as the board*/
	/*columns in command are bc+dc*/
	int cr;/*rows in command*/

	/*
		Once initialized you can only change the color of the board
	*/
	int bbkcl;/*background color of the board*/
	int bfgcl;/*foreground color of the board*/


	char  cplayer;/*character of the player*/
	int pr;/*row in the board the player is in*/
	int pc;/*column in the board the player is in*/


};

Interface *i_create(int bc, int br, int dc, int cr, char cplayer,
					int bbkcl, int bfgcl, int dbkcl, int dfgcl,
					int cbkcl, int cfgcl){

	Interface * i;
	i=(Interface*)malloc(sizeof(Interface));
	if(i==NULL)
		return NULL;
	i->bc=bc;
	i->br=br;
	i->dc=dc;
	i->cr=cr;
	i->cplayer=cplayer;
	i->pr=-1;/*You need to initialized the position of the player in another*/
	i->pc=-1;/*function																											*/
	i->bbkcl=bbkcl;
	i->bfgcl=bfgcl;




	i->board=win_new(0,0,br,bc,bbkcl,bfgcl);
	if(i->board==NULL){
		free(i);
		return NULL;
	}
	i->display=win_new(0,bc,br,dc,dbkcl,dfgcl);
	if(i->display==NULL){
		win_delete(i->board);
		free(i);
		return NULL;
	}
	i->command=win_new(br,0,cr,bc+dc,cbkcl,cfgcl);
	if(i->command==NULL){
		win_delete(i->board);
		win_delete(i->display);
		free(i);
		return NULL;
	}

	return i;
}



void i_drawAll(Interface *i){
	char aux1[]="-------------------------------------------------------------------------------------------------------------------------";
	int j;
	if(i==NULL)
		return;


	/*First we markdown the board, the first row of it and the first column*/
	win_write_char_at(i->board,0,0,'+');
	win_write_line_at(i->board,0,1,aux1);
	for(j=1;j<i->br;j++){
		win_write_char_at(i->board,j,0,'|');
	}


	/*Second lets markdown the display*/
	/*the first row*/
	win_write_char_at(i->display,0,0,'+');
	win_write_line_at(i->display,0,1,aux1);
	win_write_char_at(i->display,0,i->dc-1,'+');
	/*the first and last column*/
	for(j=1;j<i->br;j++){
		win_write_char_at(i->display,j,0,'|');
		win_write_char_at(i->display,j,i->dc-1,'|');
	}


	/*Lets markdown the command*/
	/*first row*/
	win_write_line_at(i->command,0,0,aux1);
	/*last row*/
	win_write_line_at(i->command,i->cr-1,0,aux1);
	for(j=0;j<i->cr;j++){
		win_write_char_at(i->display,j,0,'|');
		win_write_char_at(i->display,j,i->dc+i->bc-1,'|');
	}
	win_write_char_at(i->command,0,0,'+');
	win_write_char_at(i->command,0,i->bc,'+');
	win_write_char_at(i->command,0,i->bc+i->dc-1,'+');
	win_write_char_at(i->command,i->cr-1,0,'+');
	win_write_char_at(i->command,i->cr-1,i->bc+i->dc-1,'+');




	return;
}



void i_drawStr(Interface *i, char *s, int r, int c,int bdc){
	if(i==NULL)
		return;

	switch (bdc) {
		case 1:
			if(r<1 || c<1)
				return;/*The row and colum 0 are not usable*/
			win_write_line_at(i->board, r, c, s);
			return;

		case 2:
			if(r<1 || c<1 || c>i->dc-2)
				return;/*The first row, the first column and the last column are not usable*/
		  win_write_line_at(i->display, r, c, s);
			return;

		case 3:
			if(r<1 || c<1 || r>i->cr-2 || c>i->bc+i->dc-2)
				return;/*The limitations are not usable*/
			win_write_line_at(i->command,r,  c, s);
			return;

		default:
			return;
	}
}
