#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "MiniMaze.h"
#include "../../Animations/animations.h"

/*MAZE GEN FUNCTIONS*/

/*
   Random generator of integers.
   Parameters:
    min is the smallest number you want it to generate
    max i the biggest number you want it to generate
   Returns:
    -1 in case of error
    the number generated if its succesfull
 */

int generator(int min, int max)
{
    int r;
    srand(time(NULL) + clock());
    if (max < min)
        return -1;
    if (max == min)
        return min;

    r = rand() % (max - min + 1);
    r = r + min;

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
   This generator of mazes can, in some cases, leave the spaces unnaccessiable
   will modified that with another function.
 */
void mazegen_rec(char **map, int irow, int icol, int frow, int fcol)
{
    int i, r, c;    /*i for loops, r is random row for wall, c random col for wall*/
    int h1, h2, h3; /*hi random numbers in which the holes in the wall gonna be*/
    if (map == NULL)
        return;
    if (frow - irow + 1 < 4 || fcol - icol + 1 < 4) /*caso base*/
        return;

    /*We generate a random number to draw walls*/
    r = generator(irow + 1, frow - 1);
    c = generator(icol + 1, fcol - 1);
    /*writing the walls*/
    for (i = irow; i <= frow; i++)
    {
        map[i][c] = '|';
    }
    for (i = icol; i <= fcol; i++)
    {
        map[r][i] = '-';
    }
    /*connection between the walls*/
    map[r][c] = '+';

    /*We open a hole in three walls to be able to move in the space*/

    /*First hole in the wall:
     |
     |
          -- -+-----
     |
     |
     */
    h1         = generator(icol, c - 1);
    map[r][h1] = ' ';

    /*Second hole in the wall:
     |
     |
            ----+-----

     |
     */
    h2         = generator(r + 1, frow);
    map[h2][c] = ' ';

    /*Third hole in the wall:
     |
     |
              ----+- ---
     |
     |
     */
    h3         = generator(c + 1, fcol);
    map[r][h3] = ' ';

    /*recursive call*/
    /*top left rectangle*/
    mazegen_rec(map, irow, icol, r - 1, c - 1);
    /*bot left rectangle*/
    mazegen_rec(map, r + 1, icol, frow, c - 1);
    /*top right rectangle*/
    mazegen_rec(map, irow, c + 1, r - 1, fcol);
    /*bot left rectangle*/
    mazegen_rec(map, r + 1, c + 1, frow, fcol);
    return;
}




/*
   Its a function that opens spaces in places that could be blocked by the
   previous function and that could make the maze unsolvable.
   Parameters:
    -map an initialized map with the given format by mazegen_rec
    -rows number of rows of the map
    -cols number of cols of the map
 */
void fix_map(char **map, int rows, int cols)
{
    int i, j;
    /*
       No need to check parameters because we only call this function
       in mazegen and we make sure we use it right:)
     */

    for (i = 1; i < rows - 1; i++)
    {
        for (j = 1; j < cols - 1; j++)
        {
            if (map[i][j - 1] != ' ' && map[i][j] == ' ' && map[i][j + 1] != ' ')
            {
                map[i - 1][j] = ' ';
                map[i + 1][j] = ' ';
            }
        }
    }

    for (j = 1; j < cols - 1; j++)
    {
        for (i = 1; i < rows - 1; i++)
        {
            if (map[i - 1][j] != ' ' && map[i + 1][j] != ' ' && map[i][j] == ' ')
            {
                map[i][j + 1] = ' ';
                map[i][j - 1] = ' ';
            }
        }
    }

    return;
}


/*
   This function adds the end character for the maze
 */
void addGoal(char **map, int rows, int cols)
{
    /*Not checking parameters because its an internal function*/
    int i, j;
    for (i = cols - 1; i >= 0; i++)
    {
        for (j = rows - 1; j >= 0; j--)
        {
            if (map[j][i] == ' ')
            {
                map[j][i] = '*';
                return;
            }
        }
    }
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
char **mazegen(int rows, int cols)
{
    char **map;
    int  i, j;
    if (rows < 3 || cols < 3)
        return NULL;

    map = (char * *) malloc(sizeof(char *) * rows);

    for (i = 0; i < rows; i++)
    {
        map[i] = (char *) malloc(sizeof(char) * cols);
        /*if theres no memory*/
        if (map[i] == NULL)
        {
            for (j = 0; j < i; j++)
                free(map[j]);
            free(map);
            return NULL;
        }
        /*We use this loop to initialize all the map to spaces*/
        for (j = 0; j < cols; j++)
            map[i][j] = ' ';
    }


    /*
       generates the maze in map
     */
    mazegen_rec(map, 0, 0, rows - 1, cols - 1);
    /*
       Makes sure that the map is solvable opening spaces that could be blocked
       by the previous function.
     */
    fix_map(map, rows, cols);
    /*
       This funcition adds a <*> which represents the objective of the maze
     */
    addGoal(map, rows, cols);

    return map;
}

/*END OF MAZE GEN*/

/*
   Looks for a space where to place the player in the map
 */
void map_iniPlayer(Interface *i, char **map, int rows, int cols)
{
    /*Not checking parameters because its an internal function*/
    int k, j, sol;
    for (k = 0; k < cols; k++)
    {
        for (j = 0; j < rows; j++)
        {
            if (map[j][k] == ' ')
            {
                i_drawPl(i, j, k);
                return;
            }
        }
    }
    return;
}

/*
   checks if any of the squares surrounding (pr,pc) is the solution to the maze
   rows and cols is the information about the size of the maze
   returns 1 if the solution is theres
          0 if not
 */
int check_maze(char **map, int rows, int cols, int pr, int pc)
{
    /*NOt checking parameters because its an internal func*/
    /*First we check NORTH*/
    if (pr - 1 >= 0 && map[pr - 1][pc] == '*')
    {
        return 1;
    }
    /*Check EAST*/
    if (pc - 1 >= 0 && map[pr][pc - 1] == '*')
    {
        return 1;
    }
    /*check WEST*/
    if (pc + 1 < cols && map[pr][pc + 1] == '*')
    {
        return 1;
    }
    /*check SOUTH*/
    if (pr + 1 < rows && map[pr + 1][pc] == '*')
    {
        return 1;
    }
    return 0;
}


int miniMaze(Interface *i, int hardMode)
{
    char **map;
    int  rows, cols, pr, pc, j, rpr, rpc;
    char c;
    if (i == NULL)
        return -1;

    /*Cleaning interface*/
    i_cleanCommand(i);                 /*Deletes whatever is in the command line*/
    i_cleanDisplay(i);                 /*The same with display*/
    i_cleanMap(i);

    /*setting instructions*/
    i_readFile(i, MAZE_PATH, 3, 0, 2);
    /*Info for player*/
    i_readFile(i, INFO, 5, 40, 1);
    _read_key();

    /*Setting random made map*/
    rows = i_getbr(i) - 1; /*rows of map*/
    cols = i_getbc(i) - 1; /*cols of map*/
    map  = mazegen(rows, cols);
    i_setMap(i, map);
    map_iniPlayer(i, map, rows, cols);



    while (1)
    {
        c = _read_key();
        if (c == 'q' || c == 'Q')
        {
            /*we free map*/
            for (j = 0; j < rows; j++)
            {
                free(map[j]);
            }
            free(map);
            return QUIT;
        }
        if (c == WEST || c == EAST || c == NORTH || c == SOUTH)
        {
            /*We register the previous place of the player*/
            rpr = i_wherePlayerBeRow(i);
            rpc = i_wherePlayerBeCol(i);

            move(i, c);
            pr = i_wherePlayerBeRow(i);
            pc = i_wherePlayerBeCol(i);
            /*If its in hardMode we block the way you come from*/
            if (hardMode == 1)
            {
                /*check if you moved*/
                if (rpr != pr || rpc != pc)
                    i_writeCharMap(i, '0', rpr, rpc, 1);
            }
            if (check_maze(map, rows, cols, pr, pc) == 1)
            {
                /*we free map*/
                for (j = 0; j < rows; j++)
                {
                    free(map[j]);
                }
                free(map);
                return WIN;
            }
        }

        if (c == 'c' || c == 'C')
        {
            i_readFile(i, MAZE_CLUE_PATH, 20, 0, 2);
        }
    }
}

int easyMiniMaze(Interface *i)
{
    return miniMaze(i, 0);
}

int hardMiniMaze(Interface *i)
{
    int n;
    n = miniMaze(i, 1);
    if (n == 1)
    {
        Five_animation_maze(i);
    }
    return n;
}


















