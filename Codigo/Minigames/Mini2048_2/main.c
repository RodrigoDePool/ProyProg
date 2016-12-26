#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <termios.h>
#include "../../interface.h"



int main(){
  Interface *i;
  
	_term_init();/*Initializes the terminal for the interface*/
	i=i_create(115,34,30,34,'@',40,37,40,37,40,37);
  	i_drawAll(i);/*Draws limits*/
  	i_readFile(i, "tablero.txt", 0, 0, 1);
	i_drawAll(i);/*Draws limits*/
	
	
  i_free(i);
  tcsetattr(fileno(stdin), TCSANOW, &initial);
  return 0;

}
