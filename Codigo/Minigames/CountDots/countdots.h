#ifndef COUNTDOTS
#define COUNTDOTS
#include "interface.h"
#define ROWS          34
#define COLS          113
#define COUNT_INST    "DATA/miniInst/countDots/countInst"
#define COUNT_INFO    "DATA/miniInst/countDots/info"
#define SMALL_DOT     "DATA/miniInst/countDots/smallDot"
#define MEDIUM_DOT    "DATA/miniInst/countDots/mediumDot"
#define BIG_DOT       "DATA/miniInst/countDots/bigDot"
#define TIME          4
#define ROUNDS        5
#define LIVES         2

/*
    Dots appear on the screen for a given time then they are deleted
    you must remember the amounts of dots and write the number, if you
    fail you lose a live, when you hit 0 you lose the game
    Parameter:
        Pointer to Interface
        hardmode if 0 you play normally if 1 you play with half the time
    Return:
        -1  error
        0  lose
        1  win
 */
int countDots(Interface *i, int hardMode);

#endif