#ifndef MINIPADEL_H
#define MINIPADEL_H
/*Libraries*/
#include "../../interface.h"

/*Functions*/
/*
    This function executes a Padel minigame against a wall, to win
    you must survive a timer.
    Parameters:
        i Interface pointer in which the minigame will be executed
        hardMode: 0 if its normal mode (normal speed)
                  1 if its hard mode extra balls
    Returns:
        0 if you lose
        1 if you win
        -1 if error
 */
int miniPadel(Interface *i, int hardMode);

#endif /*MINIPADEL_H*/