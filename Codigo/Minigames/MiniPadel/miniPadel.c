#include "miniPadel.h"
#define PAD_XPOS    ;

typedef struct _Ball
{
    char obj = 'o';
    int  xspeed;
    int  yspeed;
    int  xpos;
    int  ypos;
}Ball;

typedef struct _Pad
{
    char pad  = '|';
    int  size = 2;
    int  ypos;
}Pad;

/*
    Minigame, reference in .h
 */
int miniPadel(Interface * i, int hardMode)
{
    if (i == NULL)
    {
        return -1;
    }
    /*Initialize the interface for the game*/
}