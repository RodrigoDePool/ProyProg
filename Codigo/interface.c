#include "interface.h"
#include <string.h>
#include <assert.h>
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

	char **map;/*Map as it is in the board*/

	char  cplayer;/*character of the player*/
	int pr;/*row in the MAP the player is in DIFFERENT FROM BOARD COORDS*/
	int pc;/*column in the MAP the player is in DIFFERENT FROM BOARD COORDS*/


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
	i->map=NULL; /*The board map must be initialized in another function*/




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
	int j;
	if(i==NULL)
		return;

/*FALTA REFRESCAR LOS RECTANGULOS PERO POR ALGUNA RAZON PETA
	win_cls(i->command);
	win_cls(i->board);
	win_cls(i->display);
*/


	/*First we markdown the board, the first row of it and the first column*/
	for(j=1;j<i->bc;j++){
		win_write_line_at(i->board,0,j,"-");
	}

	for(j=1;j<i->br;j++){
		win_write_char_at(i->board,j,0,'|');
	}


	/*Second lets markdown the display*/
	/*the first row*/
	for(j=1;j<i->bc;j++){
		win_write_line_at(i->display,0,j,"-");
	}

	/*the first and last column*/
	for(j=0;j<i->br;j++){
		win_write_char_at(i->display,j,0,'|');
		win_write_char_at(i->display,j,i->dc-1,'|');
	}


	/*Lets markdown the command*/
	/*first row*/
	for(j=0;j<i->bc+i->dc;j++){
		win_write_line_at(i->command,0,j,"-");
	}

	/*last row*/
	for(j=0;j<i->bc+i->dc;j++){
		win_write_line_at(i->command,i->cr-1,j,"-");
	}
	for(j=0;j<i->cr;j++){
		win_write_char_at(i->command,j,0,'|');
		win_write_char_at(i->command,j,i->dc+i->bc-1,'|');
	}


	/*We finally draw the edges*/
	win_write_char_at(i->board,0,0,'+');
	win_write_char_at(i->command,i->cr-1,i->bc+i->dc-1,'+');
	win_write_char_at(i->command,0,0,'+');
	win_write_char_at(i->command,0,i->bc,'+');
	win_write_char_at(i->command,0,i->bc+i->dc-1,'+');
	win_write_char_at(i->command,i->cr-1,0,'+');
	win_write_char_at(i->display,0,0,'+');
	win_write_char_at(i->display,0,i->dc-1,'+');


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



void i_setMap(Interface *i,char **map){
	int j,k;
	if(i==NULL || map==NULL)
		return;
	i->map=(char **)malloc(sizeof(char *)*(i->br));
	if(i->map==NULL)
		return;

	for(j=0;j<i->br;j++){
		i->map[j]=(char *)malloc(sizeof(char *)*(i->bc-1));
		if(i->map[j]==NULL){
				for(k=0;k<j;k++)
					free(i->map[k]);
				free(i->map);
				return;
		}
	}
	for(j=0;j<i->br-1;j++)
		strcpy(i->map[j],map[j]);


	for(j=0;j<i->br-1;j++){
		i_drawStr(i,map[j],j+1,1,1);
	}
	return;
}


int i_drawPl(Interface *i,int br,int bc){
	if(i==NULL || br<0 || bc<0 || br>(i->br-2) || bc>(i->bc-2) || i->map==NULL)
		return 0;


	if(i->map[br][bc]!=' ')
		return 0;


	i->pr=br;
	i->pc=bc;
	i->map[br][bc]=i->cplayer;
	win_write_char_at(i->board,br+1,bc+1,i->cplayer);/*we must pass from map coords*/
																									 /*to board coords 						 */

	return 1;
}



void move(Interface *i,int dir){
	int aux;
	if(i==NULL)
		return;
	if(i->pr==-1)
			return;
		switch (dir) {
		case NORTH:
			aux=i_drawPl(i,i->pr-1,i->pc);/*writes it*/
			if(aux==1){/*if you were able to move delete the previous player postion*/
				win_write_char_at(i->board,i->pr+2,i->pc+1,' ');/*Previous position in board coords*/
				i->map[i->pr+1][i->pc]=' ';/*Setting a space in previous pposition*/
			}
			return;
		case WEST:
			aux=i_drawPl(i,i->pr,i->pc-1);
			if(aux==1){/*if you were able to move delete the previous player postion*/
				win_write_char_at(i->board,i->pr+1,i->pc+2,' ');/*Previous position in board coords*/
				i->map[i->pr][i->pc+1]=' ';/*Setting a space in previous pposition*/
			}
			return;
		case SOUTH:
			aux=i_drawPl(i,i->pr+1,i->pc);
			if(aux==1){/*if you were able to move delete the previous player postion*/
				win_write_char_at(i->board,i->pr,i->pc+1,' ');/*Previous position in board coords*/
				i->map[i->pr-1][i->pc]=' ';/*Setting a space in previous pposition*/
			}
			return;
		case EAST:
			aux=i_drawPl(i,i->pr,i->pc+1);
			if(aux==1){/*if you were able to move delete the previous player postion*/
				win_write_char_at(i->board,i->pr+1,i->pc,' ');/*Previous position in board coords*/
				i->map[i->pr][i->pc-1]=' ';/*Setting a space in previous pposition*/
			}
			return;
		default:
			return;
	}
}



void i_free(Interface *i){
	int j;
	/*we clear the windows*/
	win_cls(i->board);
	win_cls(i->display);
	win_cls(i->command);
	/*we free the windows*/
	win_delete(i->board);
	win_delete(i->display);
	win_delete(i->command);

	/*we free the map*/
	for(j=0;j<i->br;j++){
		if(i->map[j])
			free(i->map[j]);
	}
	if(i->map)
		free(i->map);

	free(i);
}

int i_setBackgroundColor(Interface *i, int bbkcl){
	if(!i) return -1;
	i->bbkcl=bbkcl;

	/*If the color doesen't appear, add this line:
	i_drawAll(i);
	after the win_bgcol...
	*/

	return (0-(win_bgcol(i->board, bbkcl) && win_bgcol(i->display, bbkcl) && win_bgcol(i->command, bbkcl)));
}

int i_setForegroundColor(Interface *i, int bfgcl){
	if(!i) return -1;
	i->bfgcl=bfgcl;

	/*If the color doesen't appear, add this line:
	i_drawAll(i);
	after the win_fgcol...
	*/

	return (0-(win_fgcol(i->board, bfgcl) && win_fgcol(i->display, bfgcl) && win_fgcol(i->command, bfgcl)));
}
