#ifndef MINIMAZE_H
#define MINIMAZE_H
#include "../../interface.h"
#define WIN               1
#define QUIT              0
#define MAZE_PATH         "DATA/miniInst/maze/mazeInst"
#define MAZE_CLUE_PATH    "DATA/miniInst/maze/mazeClue"

/*
   Parameters:
    i pointer to the Interface
    0 for normal mode
    1 for hard mode
   Returns:
    WIN if the player completed the maze and QUIT if the player quit the game

   NOTE:
    To display the instructions of the game in the Display Map the functions uses
    the file in the MAZE_PATH. This MUST be the path of the instructions of the maze
    from the main function that executes it.
    the same with the clues.

 */
int miniMaze(Interface *i, int hardMode);

int easyMiniMaze(Interface *i);

int hardMiniMaze(Interface *i);


#endif /*MINIMAZE_H*/
