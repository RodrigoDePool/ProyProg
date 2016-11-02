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
	i->pr=-1;/*You need to initialize the position of the player in another*/
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
	/*

	*/
	char aux1[]="-------------------------------------------------------------------------------------------------------------------------";
	int j, k;
	if(i==NULL)
		return;


	/*First we markdown the board, the first row of it and the first column*/
	win_write_char_at(i->board,0,0,'+');
	
	/*for(j=1;j<i->bc;j++){
		win_write_char_at(i->board,0,j,'-')
	}*/

	win_write_line_at(i->board,0,1,aux1);
	for(j=1;j<i->br;j++){
		win_write_char_at(i->board,j,0,'|');
	}


	/*Second lets markdown the display*/
	/*the first row*/
	win_write_char_at(i->display,0,0,'+');
	
	/*for(j=1;j<(i->dc);j++){
		win_write_char_at(i->display,0,j,'-')
	}*/

	win_write_line_at(i->display,0,1,aux1);
	win_write_char_at(i->display,0,i->dc-1,'+');
	/*the first and last column*/
	for(j=1;j<i->br;j++){
		win_write_char_at(i->display,j,0,'|');
		win_write_char_at(i->display,j,i->dc-1,'|');
	}


	/*Lets markdown the command*/
	/*first row*/

	/*for(j=1;j<(i->bc+i->dc);j++){
		win_write_char_at(i->display,0,j,'-')
	}*/

	win_write_line_at(i->command,0,0,aux1);
	/*last row*/

	/*for(j=1;j<(i->bc+i->dc);j++){
		win_write_char_at(i->display, i->cr-1, j, '-')
	}*/

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

void i_drawPl(Interface *i,int br, int bc){
	if(!i||br<1||bc<1||bc>=i->bc||br>=i->br) return; /*Si hay errores que no se sabe de donde vienen, revisar esta línea*/
	/*We check if the player poition hasalready been initialized, so that we don't write a space where we can not*/
	if(i->pr>0 && i->pc>0){
		win_write_char_at(i->board, i->pr, i->pc, ' ');
	}
	
	win_write_char_at(i->board, br, bc, PLAYER);
	i->pr=br;
	i->pc=bc;
	return;

}

void move(Interface *i, int dir){
	/*We check that there is not a wall where we want to move, the rest of the checks are made in teh drawPl*/



	/*We draw the player*/
	switch (dir):

	case 1:
		i_drawPl(i, i->pr, i->pl+1);
		return;

	case 2:
		i_drawPl(i, i->pr, i->pl-1);
		return;
	
	case 3:
		i_drawPl(i, i->pr+1, i->pl);
		return;

	case 4:
		i_drawPl(i, i->pr-1, i->pl-1);
		return;

	default:
		return;
}

void i_free(Interface *i){
	if(!i) return;

	win_delete(i->board);
	win_delete(i->display);
	win_delete(i->command);

	free(i);
	return;
}

int i_setBackgroundColor(Interface *i, int bbkcl){
	if(!i) return;
	i->bbkcl=bbkcl;

	/*If the color doesen't appear, add this line:
	i_drawAll(i);
	after the win_bgcol...
	*/
	
	return (0-(win_bgcol(i->board, bbkcl) && win_bgcol(i->display, bbkcl) && win_bgcol(i->command, bbkcl)));
}

int i_setForegroundColor(Interface *i, int bfgcl){
	if(!i) return;
	i->bfgcl=bfgcl;

	/*If the color doesen't appear, add this line:
	i_drawAll(i);
	after the win_fgcol...
	*/
	
	return (0-(win_fgcol(i->board, bfgcl) && win_fgcol(i->display, bfgcl) && win_fgcol(i->command, bfgcl)));
}