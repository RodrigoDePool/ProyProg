#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <termios.h>
#include "../../interface.h"



int main(){
  Interface *i;
  int c,k,flag1,flag2,flag3;
	char **s;
	/*Inicializamos un mapa vacio*/
	s=(char **)malloc(sizeof(char *)*19);
	for(c=0;c<19;c++)
		s[c]=(char *)malloc(sizeof(char)*60);
	for(c=0;c<19;c++)
		strcpy(s[c],"                                                           ");
	_term_init();/*Initializes the terminal for the interface*/
	i=i_create(113,34,34,6,'@',40,37,40,37,40,37);
	i_drawAll(i);
	i_readFile(i, "../../Maps/Entrance.map", 0, 0, 1);
	i_drawPl(i,6,6);
	flag1=0;
	flag2=0;
	flag3=0;
	while(1){
		c=_read_key();
		if(c=='q'){

				break;
		}
		if(c=='w'){
			if(flag1==0){
			i_setBackgroundColor(i, 41, 1);
			flag1=1;
			}else{
			i_setBackgroundColor(i, 40, 1);
			flag1=0;
			}
		}
		if(c=='e'){
			if(flag2==0){
			i_setBackgroundColor(i, 42, 2);
			flag2=1;
			}else{
			i_setBackgroundColor(i, 40, 2);
			flag2=0;
			}
		}
		if(c=='r'){
			if(flag3==0){
			i_setBackgroundColor(i, 43, 3);
			flag3=1;
			}else{
			i_setBackgroundColor(i, 40, 3);
			flag3=0;
			}
		}
		if(c=='t'){
			i_setForegroundColor(i, 31, 1);
		}
		if(c=='y'){
			i_setForegroundColor(i, 32, 2);
		}
		if(c=='u'){
			i_setForegroundColor(i, 33, 3);
		}
		if(c=='i'){
			i_setForegroundColor(i, 32, 3);
			i_setForegroundColor(i, 32, 2);
			i_setForegroundColor(i, 32, 1);
		}

		if(c=='a'){
			i_writeChar(i,'a',2, 3, 1);
		}
		if(c=='s'){
			i_writeChar(i,'s',2, 3, 1);
		}
		if(c=='d'){
			i_writeChar(i,'d',2, 3, 2);
		}
		if(c=='f'){
			i_writeChar(i,'f',2, 3, 2);
		}
		if(c=='g'){
			i_writeChar(i,'g',2, 3, 3);
		}
		if(c=='h'){
			i_writeChar(i,'h',2, 3, 3);
		}
		if(c=='j'){
			i_drawStrMap(i,"abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijA",01, 01, 1);
			i_drawStrMap(i,"abcdefghijklmnopqrA",1, 1, 2);
			i_drawStrMap(i,"abcdefghijklmnopqrsabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijA",01, 01, 3);
		}
		if(c=='k'){
			i_drawStrMap(i,"It's me",2, 3, 1);
			i_drawStrMap(i,"It's me",2, 3, 2);
			i_drawStrMap(i,"It's me",2, 3, 3);
		}
		move(i,c);
	}

	for(c=0;c<19;c++)
		free(s[c]);
	free(s);

  i_free(i);
  tcsetattr(fileno(stdin), TCSANOW, &initial);
  return 0;

}

/*CODIGO UTIL
int c = _read_key();
if (c == 'q') {
  tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd
            so that the termial behaves normally when
            the program ends */
/*  exit(0);
}
*/
