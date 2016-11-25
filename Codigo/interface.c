
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

	int bbkcl;/*background color of the board*/
	int bfgcl;/*foreground color of the board*/
	int dbkcl;/*background color of the display*/
	int dfgcl;/*foreground color of the display*/
	int cbkcl;/*background color of the command*/
	int cfgcl;/*foreground color of the command*/

	char **map;/*Maps*/
	char **mapDisplay;
	char **mapCommand;

	char  cplayer;/*character of the player*/
	int pr;/*row in the MAP the player is in DIFFERENT FROM BOARD COORDS*/
	int pc;/*column in the MAP the player is in DIFFERENT FROM BOARD COORDS*/


};

Interface *i_create(int bc, int br, int dc, int cr, char cplayer,
					int bbkcl, int bfgcl, int dbkcl, int dfgcl,
					int cbkcl, int cfgcl){

	Interface * i;
	int j, k;
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
	i->dbkcl=dbkcl;
	i->dfgcl=dfgcl;
	i->cbkcl=cbkcl;
	i->cfgcl=cfgcl;
	i->map=NULL; /*The board map must be initialized in another function*/

	i->mapDisplay=(char**)malloc(sizeof(char*)*i->br-1);
	if(!i->mapDisplay){
		free(i);
		return NULL;
	}

	i->mapCommand=(char**)malloc(sizeof(char*)*(i->cr-2));
	if(!i->mapCommand){
		free(i->mapDisplay);
		free(i);
		return NULL;
	}

	for(j=0;j<i->br-1;j++){
		i->mapDisplay[j]=(char*)malloc(sizeof(char)*(i->dc-2));
		if(!i->mapDisplay[j]){
			while(j>0){
				free(i->mapDisplay[--j]);
			}
			free(i->mapDisplay);
			free(i->mapCommand);
			free(i);
			return NULL;
		}
		for(k=0;k<i->dc-2;k++){
			i->mapDisplay[j][k]=' ';
		}
	}

	for(j=0;j<i->cr-2;j++){
		i->mapCommand[j]=(char*)malloc(sizeof(char)*(i->dc+i->bc-2));
		if(!i->mapCommand[j]){
			while(j>0){
				free(i->mapCommand[--j]);
			}
			for(k=0;k<i->dc;k++){
				free(i->mapDisplay[k]);
			}
			free(i->mapDisplay);
			free(i->mapCommand);
			free(i);
			return NULL;
		}
		for(k=0;k<i->dc+i->bc-2;k++){
			i->mapCommand[j][k]=' ';
		}
	}

	i->board=win_new(0,0,br,bc,bbkcl,bfgcl);
	if(i->board==NULL){
		for(j=0;j<i->br-2;j++){
			free(i->mapDisplay[j]);
		}
		for(j=0;j<i->cr-2;j++){
			free(i->mapCommand[j]);
		}
		free(i->mapDisplay);
		free(i->mapCommand);
		free(i);
		return NULL;
	}

	i->display=win_new(0,bc,br,dc,dbkcl,dfgcl);
	if(i->display==NULL){
		for(j=0;j<i->dc;j++){
			free(i->mapDisplay[j]);
		}
		for(j=0;j<i->dc;j++){
			free(i->mapCommand[j]);
		}
		free(i->mapDisplay);
		free(i->mapCommand);
		win_delete(i->board);
		free(i);
		return NULL;
	}
	
	i->command=win_new(br,0,cr,bc+dc,cbkcl,cfgcl);
	if(i->command==NULL){
		for(j=0;j<i->dc;j++){
			free(i->mapDisplay[j]);
		}
		for(j=0;j<i->dc;j++){
			free(i->mapCommand[j]);
		}
		free(i->mapDisplay);
		free(i->mapCommand);
		win_delete(i->board);
		win_delete(i->display);
		free(i);
		return NULL;
	}

	return i;
}


void i_drawAll(Interface *i){
	int j, k;
	if(i==NULL)
		return;

	win_cls(i->command);
	win_cls(i->board);
	win_cls(i->display);

	/*Now we write the map if it is there*/
	if(i->map!=NULL){
		for(j=0;j<i->br-1;j++){
			for(k=0;k<i->bc-1;k++){
				win_write_char_at(i->board,i->map[j][k],j+1,k+1);
			}
		}
	}

	/*Now we write the command line and the display*/
	for(j=0;j<i->br-1;j++){
		for(k=0;k<i->dc-2;k++){
			win_write_char_at(i->display,i->mapDisplay[j][k],j+1,k+1);
		}
	}

	for(j=0;j<i->cr-2;j++){
		for(k=0;k<i->bc+i->dc-2;k++){
			win_write_char_at(i->command,i->mapCommand[j][k],j+1,k+1);
		}
	}

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
	
	fflush(stdout);
	return;
}



void i_drawStr(Interface *i, char *s, int r, int c,int bdc){
	int j;
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

void i_drawStrMap(Interface *i, char *s, int r, int c,int bdc){
	int j;
		if(i==NULL)
		return;

	switch (bdc) {
		case 1:
			if(r<0 || c<0 || r>i->br-2)
				return;/*The row and colum 0 are not usable*/

			for(j=c;j<i->bc-1&&j-c<strlen(s);j++){
				i->map[r][j]=s[j-c];
			}

			break;

		case 2:
			if(r<0 || c<0 || r>i->br-2)
				return;/*The first row, the first column and the last column are not usable*/
			
			for(j=c;j<i->dc-2&&j-c<strlen(s);j++){
				i->mapDisplay[r][j]=s[j-c];
			}

			break;

		case 3:
			if(r<0 || c<0 || r>i->cr-3)
				return;/*The limitations are not usable*/

			for(j=c;j<i->bc+i->dc-2&&j-c<strlen(s);j++){
					i->mapCommand[r][j]=s[j-c];

			}
			
			break;

		default:
			return;
	}
	i_drawAll(i);
	return;
}



void i_setMap(Interface *i,char **map){
	int j,k;
	if(i==NULL || map==NULL)
		return;
	i->map=(char **)malloc(sizeof(char *)*(i->br-1));
	if(i->map==NULL)
		return;

	for(j=0;j<i->br-1;j++){
		i->map[j]=(char *)malloc(sizeof(char *)*(i->bc-1));
		if(i->map[j]==NULL){
				for(k=0;k<j;k++)
					free(i->map[k]);
				free(i->map);
				return;
		}
	}
	for(j=0;j<i->br-1;j++){
		for(k=0;k<i->bc-1;k++){
			if(map[j][k]==0)
				break;
			i->map[j][k]=map[j][k];
		}
	}


	for(j=0;j<i->br-1;j++){
		i_drawStr(i,map[j],j+1,1,1);
	}
	return;
}

void i_freeMap(Interface * i){
	int j;
	if(!i) return;
	if(!i->map) return;
	for(j=0;j<i->br-1;j++){
		if(i->map[j]){
			free(i->map[j]);
			i->map[j]=NULL;
		}
	}
	free(i->map);
	i->map=NULL;
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

	/*we free the maps*/
	i_freeMap(i);

	for(j=0;j<i->br-2;j++){
		free(i->mapDisplay[j]);
	}
	for(j=0;j<i->cr-2;j++){
		free(i->mapCommand[j]);
	}
	free(i->mapDisplay);
	free(i->mapCommand);
	free(i);
}

int i_setBackgroundColor(Interface *i, int bkcl, int bdc){
	int ret;
	if(!i) return -1;

	switch(bdc){
	case 1:
		if((win_bgcol(i->board, bkcl))==1)
			return -1;
		i->bbkcl=bkcl;
		break;
		
	case 2:
		if((win_bgcol(i->display, bkcl))==1)
				return -1;
		
		i->dbkcl=bkcl;
		break;

	case 3:
		if((win_bgcol(i->command, bkcl))==1)
			return -1;
		i->cbkcl=bkcl;
			break;
	default:
		break;
	}
	
	i_drawAll(i);
	return 0;
}

int i_setForegroundColor(Interface *i, int fgcl, int bdc){
	if(!i) return -1;

		switch(bdc){
	case 1:
		if((win_fgcol(i->board, fgcl))==1)
			return -1;
		i->bfgcl=fgcl;
		break;
		
	case 2:
		if((win_fgcol(i->display, fgcl))==1)
			return -1;
		i->dfgcl=fgcl;
		break;

	case 3:
		if((win_fgcol(i->command, fgcl))==1)
			return -1;
		i->cfgcl=fgcl;
			break;
	default:
		break;
	}
	i_drawAll(i);
	return 0;
}

int i_writeChar(Interface *i,char c,int row, int col, int bdc){
	if(!i)
		return -1;
	switch(bdc){
		case 1:
			if(row>i->br||col>i->bc) return -1;
			win_write_char_at(i->board, row, col, c);
			return 0;
		case 2:
			if(row>i->br||col>i->dc) return -1;
			win_write_char_at(i->display, row, col, c);
			return 0;
		case 3:
			if(row>i->cr||col>(i->bc+i->dc)) return -1;
			win_write_char_at(i->command, row, col, c);
			return 0;
		default:
			return -1;
	}
}

int i_wherePlayerBeRow(Interface * i){
	if(!i) return -1;
	
	return i->pr;
}

int i_wherePlayerBeCol(Interface * i){
	if(!i) return -1;
	
	return i->pc;
}

char i_whatCaractHere(Interface * i, int r, int c){
	if(!i||r>i->br-1||c>i->bc-1){
		return 0;
	}
	
	return i->map[r][c];
}

int i_getbc(Interface * i){
	if(!i) return -1;
	return i->bc;
}

int i_getdc(Interface * i){
	if(!i) return -1;
	return i->dc;
}

int i_getbr(Interface * i){
	if(!i) return -1;
	return i->br;
}

int i_getcr(Interface * i){
	if(!i) return -1;
	return i->cr;
}

int i_getpc(Interface * i){
	if(!i) return -1;
	return i->pc;
}

int i_getpr(Interface * i){
	if(!i) return -1;
	return i->pr;
}

char i_getCPlayer(Interface * i){
	if(!i) return 0;
	return i->cplayer;
}
