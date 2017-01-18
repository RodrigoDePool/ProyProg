#ifndef MINIPADEL_H
#define MINIPADEL_H
/*Libraries*/
#include "../../interface.h"
#define PADEL_INST    "Codigo/DATA/miniInst/padel/padelInst"
#define INFO_PONG     "Codigo/DATA/miniInst/padel/info"
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

int easyMiniPadel(Interface *i);

int hardMiniPadel(Interface *i);

#endif /*MINIPADEL_H*/