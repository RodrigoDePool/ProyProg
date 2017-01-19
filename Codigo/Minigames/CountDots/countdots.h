#ifndef COUNTDOTS
#define COUNTDOTS
#include "../../interface.h"
#define ROWS             34
#define COLS             113
#define COUNT_INST       "Codigo/DATA/miniInst/countDots/countInst"
#define COUNT_INFO       "Codigo/DATA/miniInst/countDots/info"
#define SMALL_DOT        "Codigo/DATA/miniInst/countDots/smallDot"
#define MEDIUM_DOT       "Codigo/DATA/miniInst/countDots/mediumDot"
#define BIG_DOT          "Codigo/DATA/miniInst/countDots/bigDot"
#define FAIL             "Codigo/DATA/miniInst/countDots/fail"
#define CORRECT          "Codigo/DATA/miniInst/countDots/Correct"
#define ROUNDINFO        "Codigo/DATA/miniInst/countDots/round"
#define TIME_MSECONDS    100
#define ROUNDS           5
#define LIFES            2
#define ROUNDTIME        4

/*
    Dots appear on the screen for a given time then they are deleted
    you must remember the amounts of dots and write the number, if you
    fail you lose a life, when you hit 0 you lose the game
    Parameter:
        Pointer to Interface
        hardmode if 0 you play normally if 1 you play with just 1 life
    Return:
        -1  error
        0  lose
        1  win
 */
int countDots(Interface *i, int hardMode);

int easyCountDots(Interface *i);

int hardCountDots(Interface *i);

#endif