#include <stdlib.h>
#include <stdio.h>
#include "../../interface.h"
#include "MiniMaze.h"

int main(){
  int rows=50,cols=110,sol;
  char c;
  Interface *i;
  _term_init();
  i=i_create(MAXCOLS-30,MAXROWS-6,30,6,'@',40,37,40,37,40,37);
  i_drawAll(i);

  do{
    sol=miniMaze(i);
    if(sol==WIN){
      i_drawStrMap(i,"Ganador",1,1,3);
    }
    else{
      i_drawStrMap(i,"Loser",1,1,3);
    }
    i_drawStrMap(i,"Quieres volver a jugar ?(s/n):",2,1,3);
    do{
      c=_read_key();
    }while(c!='s' && c!='S' && c!='n' && c!='N');

  }while(c=='s' || c=='S');
  i_free(i);
  _term_close();
  return 1;
}
