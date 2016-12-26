#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <termios.h>
#include "../../interface.h"



int main(){
	int k, j;
	Interface *i;
	int it = 0;
	
	char **txt = (char **)malloc(11 * sizeof(char *));
	for(k = 0; k < 11; k++){
		txt[k] = (char *) malloc(10 * sizeof(char));
	}
	txt[0] = "2.txt";
	txt[1] = "4.txt";
	txt[2] = "8.txt";
	txt[3] = "16.txt";
	txt[4] = "32.txt";
	txt[5] = "64.txt";
	txt[6] = "128.txt";
	txt[7] = "256.txt";
	txt[8] = "512.txt";
	txt[9] = "1024.txt";
	txt[10] = "2048.txt";
	
	_term_init();
	i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
	
	
  	i_drawAll(i);
  	sleep(2);
	
  	i_readFile(i, "board2048.txt", 0, 0, 1);
	sleep(2);
	
	for(k = 0; k < 4; k++){
		for(j = 0; j < 4; j++){
			i_readFile(i, txt[it], 4 + k*7, 17 + j*18, 1);
			sleep(1);
			it++;	
		}
	}
	sleep(5);
	i_free(i);
	_term_close();
	return 0;

}
