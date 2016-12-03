#include "miniRPSLS.h"
#include <time.h>
#include <unistd.h>
#define rock 1
#define scissors 2
#define paper 3
#define lizzard 4
#define spock 5

int round(Interface *i);
int miniRPSLS(Interface *i){
  i_readFile(i,INI_PATH,0,0,1);
  return 0;
}



/*
  Plays one round of the game
  Gets the choice of the player from stdin, prints hes option,
  prints enemies option, and decides the result
  returns 0 if lost
  returns 1 if win
  returns 2 it tie
  returns -1 if error
*/
int round(Interface *i){
  int ran,des;


  do{
    des=fgetc(stdin);
  }while(des==1 || des ==2 || des==3 || des==4 || des==5);

  srand(time(NULL));
  ran = rand() % 5 + 1;


  /*WHO WON?*/
  /*Prints enemys choice*/
  if(ran==rock)
    i_readFile(i,ROCK_PATH,17,59,1);
  if(ran==scissors)
    i_readFile(i,SCISSORS_PATH,17,59,1);
  if(ran==paper)
    i_readFile(i,PAPER_PATH,17,59,1);
  if(ran==lizzard)
    i_readFile(i,LIZZARD_PATH,17,59,1);
  if(ran==spock)
    i_readFile(i,SPOCK_PATH,17,59,1);

  if(des==rock){
      i_readFile(i,ROCK_PATH,17,15,1);
      if (ran == rock){
          return 2;
      }
      else if (ran == lizzard || ran == scissors){
        return 1;
      }
      else {
          return 0;
      }
  }
  if(des==scissors){
    i_readFile(i,SCISSORS_PATH,17,15,1);
    if(ran== scissors){
      return 2;
    }
    else if(ran==lizzard || ran==paper){
      return 1;
    }
    else
      return 0;
  }
  if(des==paper){
    i_readFile(i,PAPER_PATH,17,15,1);
    if(ran==paper)
      return 2;
    else if(ran==rock || ran==spock)
      return 1;
    else
      return 0;
  }
  if(des==lizzard){
    i_readFile(i,LIZZARD_PATH,17,15,1);
    if(ran==lizzard)
      return 2;
    else if(ran==spock || ran==paper)
      return 1;
    else
      return 0;
  }
  if(des==spock){
    i_readFile(i,SPOCK_PATH,17,15,1);
    if(ran==scissors || ran==rock)
      return 1;
    else if(ran==spock)
      return 2;
    else
      return 0;
  }
  return -1;
}
