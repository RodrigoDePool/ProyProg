#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/*First we need to make a maze generator*/

/*
  random generator of integers.
  Parameters:
    min is the smallest number you want it to generate
    max i the biggest number you want it to generate
    no is one number in this range that you do not want to be generated
  Returns:
    -1 in case of error
    the number generated if its succesfull
*/

int generator(int min, int max, int no){
  int r;
  if(max<min){
    return -1;
  }
  if(max==min)
    return min;

  do{
    r=rand()%(max-min+1);
    r=r+min;
  }while(r==no);
  return r;
}



/*
  Recursive function that will generate the random map
  Parameters:
    map a matrix of characters  full fo spaces where the map is gonna be modified
    irow the initial row of the maze
    icol the initial col of the maze
    frow the last row of the maze
    fcol the last col of the maze
    norow a row in which you cannot draw a wall
    nocol a col i which you cannot draw a wall
*/
void mazegen_rec(char **map,int irow,int icol,int frow,int fcol,int norow,int nocol){
  int i,r,c;/*i for loops, r is random row for wall, c random col for wall*/
  int h1,h2,h3;/*hi random numbers in which the holes in the wall gonna be*/
  if(map==NULL)
    return;
  if(frow-irow+1<3 || fcol-icol+1<3)/*caso base*/
    return;

  /*We generate a random number to draw walls*/
  r=generator(irow+1,frow-1,norow);
  c=generator(icol+1,fcol-1,nocol);
  /*writing the walls*/
  for(i=irow;i<=frow;i++){
    map[i][c]='|';
  }
  for(i=icol;i<=fcol;i++){
    map[r][i]='-';
  }
  /*connection between the walls*/
  map[r][c]='+';

  /*We open a hole in three walls to be able to move in the space*/

  /*First hole in the wall:
            |
            |
        -- -+-----
            |
            |
  */
  h1=generator(icol,c-1,-1);
  map[r][h1]=' ';

  /*Second hole in the wall:
              |
              |
          ----+-----

              |
  */
  h2=generator(r+1,frow,-1);
  map[h2][c]=' ';

  /*Third hole in the wall:
                |
                |
            ----+- ---
                |
                |
  */
  h3=generator(c+1,fcol,-1);
  map[r][h3]=' ';

  /*recursive call*/
  /*top left rectangle*/
  mazegen_rec(map,irow,icol,r-1,c-1,-1,h1);
  /*bot left rectangle*/
  mazegen_rec(map,r+1,icol,frow,c-1,h2,h1);
  /*top right rectangle*/
  mazegen_rec(map,irow,c+1,r-1,fcol,-1,h3);
  /*bot left rectangle*/
  mazegen_rec(map,r+1,c+1,frow,fcol,h2,h3);
  return;
}


/*
  Generates a random maze of size (rows)*(cols)
  Parameters:
    number of rows >= 3;
    number of cols >= 3;
  return: NULL if error, matrix of characters if succesfull
  REMEMBER TO FREE THIS MATRIX OUTSIDE THE FUNCITON
*/
char **mazegen(int rows, int cols){
  char **map;
  int i,j;
  if(rows<3 || cols<3)
    return NULL;

  map=(char **)malloc(sizeof(char *)*rows);

  for(i=0;i<rows;i++){
    map[i]=(char *)malloc(sizeof(char)*cols);
    /*if theres no memory*/
    if(map[i]==NULL){
      for(j=0;j<i;j++)
        free(map[j]);
      free(map);
      return;
    }
    /*We use this loop to initialize all the map to spaces*/
    for(j=0;j<cols;j++)
      map[i][j]=' ';
  }

  mazegen_rec(map,0,0,rows-1,cols-1,-1,-1);
  return  map;
}
