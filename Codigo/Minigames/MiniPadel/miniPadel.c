#include "miniPadel.h"
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#define PAD_XPOS    ;

/*
    Ball structure, the coords used in this structure are map coords
    from the interface
 */
typedef struct _Ball
{
    char obj;
    int  xspeed;
    int  yspeed;
    int  xpos;
    int  ypos;
}Ball;


/*
    Pad structure:

 |
 |

    The positon of the pad is fixed in x but moves in Y,
    the variable ypos references the position of the lower character
    of the pad
    We add to this struct a pointer to interface so we can
    implement the threads without an extra struct
 */
typedef struct _Pad
{
    char      pad;
    int       size;
    int       xpos;
    int       ypos;
    Interface *intf;
}Pad;


/*
    AUXILIAR FUNCTIONS
 */
void printPad(Interface *i, Pad pd)
{
    i_writeCharMap(i, pd.pad, pd.ypos, pd.xpos, 1);
    i_writeCharMap(i, pd.pad, pd.ypos - 1, pd.xpos, 1);
    return;
}
void printBall(Interface *i, Ball ball)
{
    i_writeCharMap(i, ball.obj, ball.ypos, ball.xpos, 1);
    return;
}






/*
    This function is occupied of the pad movement
 */
void *pad_movement(void *pdaux)
{
    char      c;
    Pad       *pd;
    Interface *i;
    int       rows; /*rows of the map*/
    pd   = (Pad *) pdaux;
    i    = pd->intf;
    rows = i_getbr(i) - 1;
    if (i == NULL)
        return NULL;
    while (1)
    {
        c = _read_key();
        if (c == 'q')
        {
            return NULL;
        }
        if (c == NORTH && pd->ypos > 1)
        {
            /*we delete the bottom part of the pad*/
            i_writeCharMap(i, ' ', pd->ypos, pd->xpos, 1);
            /*we write the top one*/
            i_writeCharMap(i, pd->pad, pd->ypos - 2, pd->xpos, 1);
            /*we change the coords*/
            pd->ypos--;
        }
        if (c == SOUTH && pd->ypos < rows - 1)
        {
            /*we delete the top one*/
            i_writeCharMap(i, ' ', pd->ypos - 1, pd->xpos, 1);
            /*we write the bottom one*/
            i_writeCharMap(i, pd->pad, pd->ypos + 1, pd->xpos, 1);
            /*we change the coords*/
            pd->ypos++;
        }
    }
}


/*
    Minigame, reference in .h
 */
int miniPadel(Interface * i, int hardMode)
{
    int       cols, rows;
    Pad       *pd;
    Ball      *ball;
    int       random;
    pthread_t pth[2]; /*Two main threads the ball and the pad*/
    if (i == NULL)
    {
        return -1;
    }
    /*Lets alloc memory for our pointers*/
    pd   = (Pad *) malloc(sizeof(Pad));
    ball = (Ball *) malloc(sizeof(Ball));

    /*FIXED VALUES OF STRUCTS*/
    pd->pad  = '|';
    pd->size = 2;
    pd->xpos = 4;

    ball->obj = 'o';



    /*Initialize the interface for the game*/
    i_cleanDisplay(i);
    i_cleanCommand(i);
    i_cleanMap(i);
    /*INSTRUCTIONS HERE*/

    /*we get the usable cols and rows of the map*/
    rows = i_getbr(i) - 1;
    cols = i_getbc(i) - 1;
    if (rows < 10 || cols < 10)
        return -1;


    /*Initialize the ypos of the pad*/
    pd->ypos = 5; /*pad is ocupying y=5 and y=4 */
    /*Print the pad*/
    printPad(i, *pd);

    /*Initialize the ball*/
    ball->xpos = cols / 2; /*Fix the ball more or less in the center of the map*/
    ball->ypos = rows / 2;

    ball->xspeed = 1; /*Always starts towards the wall*/
    /*random direction of Y*/
    random = rand() % 3;
    if (random == 2)
    {
        random = -1;
    }
    ball->yspeed = random;
    /*Print the ball*/
    printBall(i, *ball);

    /*We assign the interface to pd so we can use it in threads*/
    pd->intf = i;
    /*Create thread for pad movement*/
    pthread_create(pth, NULL, pad_movement, (void *) pd);
    /*IT WORKSS*/
    sleep(8);

    /*we cancel pad_movement*/
    pthread_cancel(pth[0]);

    /*we free pad and ball*/
    free(pd);
    free(ball);
    return 1;
}























