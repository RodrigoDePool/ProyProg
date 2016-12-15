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
    int  xdir;
    int  ydir;
    int  xpos;
    int  ypos;
    int  speed;
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
    int       stop; /*0 for quit/lose, 1 for win, 2 for keep playing*/
}Pad;


/*
    Auxiliar structure to run ball_movement function on
    thread
 */
typedef struct _Aux
{
    Pad  *pad;
    Ball *ball;
    int  rows; /*rows and cols of the interface*/
    int  cols;
}Aux;



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
            pd->stop = 0;
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
    FUNCTIONS FOR BALL MECHANICS
 */

/*
    Checks in which state the ball is in the current position, changes
    the direction of the ball if its hitting a wall.
    Parameters:
        rows and cols make reference to those of the interface
    Returns:
        -1 for error
        0 if it hit a wall and change direction, or if it didnt hit anything
        1 if the game was lost cause the player did not hit it with the pad
 */
int check(Pad *pad, Ball *ball, int rows, int cols)
{
    int random;
    if (pad == NULL || ball == NULL)
        return -1;
    srand(time(NULL) + clock());
    /*If the ball is next to pad xpos*/
    if (ball->xpos == pad->xpos + 1)
    {
        /*If the pad hits directly the ball*/
        if (pad->ypos == ball->ypos || pad->ypos - 1 == ball->ypos)
        {
            /*we change the direction of x*/
            ball->xdir = (-1) * ball->xdir;

            /*66% chance we change direction of Y by -1*/
            /*33% chance it goes in a straight line*/
            random = rand() % 3;
            /*Change Y*/
            if (random == 0 || random == 1)
            {
                ball->ydir = ball->ydir * (-1);
                /*In case it came from being in a straight line*/
                /*50% chance that it goes or up or down*/
                if (ball->ydir == 0 && random == 1)
                {
                    ball->ydir = 1;
                }
                if (ball->ydir == 0 && random == 0)
                {
                    ball->ydir = -1;
                }
            }
            /*go straight*/
            if (random == 2)
            {
                ball->ydir = 0;
            }

            return 0;
        }

        /*
            If the pad and the ball are in the  the next exceptions:
            -------------------------------
         ** o
         **|
         **|

         */
        if (ball->ypos == 0 && pad->ypos == 2)
        {
            ball->xdir = (-1) * ball->xdir;
            ball->ydir = 1;
            return 0;
        }

        /*
            If the pad and the ball are in the  the next exceptions:
            -------------------------------
         **
         **|
         **|
         ** o
            ----------------------------------
         */
        if (ball->ypos == rows - 1 && pad->ypos == rows - 2)
        {
            ball->xdir = (-1) * ball->xdir;
            ball->ydir = 1;
            return 0;
        }
        /*In any other case the player lost*/
        return 1;
    } /*END OF IF THE BALL IS NEXT TO THE XPOS OF THE PAD*/



    /*if the ball hits the right wall*/
    if (ball->xpos == cols - 1)
    {
        ball->xdir = (-1) * ball->xdir;
        /*in case the ball hits the top corner or the bottom one*/
        if (ball->ypos == 0 || ball->ypos == rows - 1)
        {
            ball->ydir = (-1) * ball->ydir;
        }
        else
        {
            /*in any other case we will have 66% chance the ball changes dir in Y*/
            /*and 33 percent that it goes in a straight line*/
            random = rand() % 3;
            /*Change Y*/
            if (random == 0 || random == 1)
            {
                ball->ydir = ball->ydir * (-1);
                /*In case it came from being in a straight line*/
                /*50% chance that it goes or up or down*/
                if (ball->ydir == 0 && random == 1)
                {
                    ball->ydir = 1;
                }
                if (ball->ydir == 0 && random == 0)
                {
                    ball->ydir = -1;
                }
            }
            /*go straight*/
            if (random == 2)
            {
                ball->ydir = 0;
            }
        }
        return 0;
    }

    /*if the ball hits the top wall*/
    if (ball->ypos == 0)
    {
        ball->ydir = (-1) * ball->ydir;
        return 0;
    }
    /*if the ball hits the bottom one*/
    if (ball->ypos == rows - 1)
    {
        ball->ydir = (-1) * ball->ydir;
        return 0;
    }
    /*if the ball aint hitting a thing*/
    return 0;
}


/*
   Main ball movement mechanics function
 */
void *ball_movement(void *auxstruct)
{
    Aux  *aux;
    Ball *ball;
    Pad  *pd;
    int  lose = 0; /*flag for losing, 1 if lost*/

    if (auxstruct == NULL)
        return NULL;

    /*We do this assignments to simplify code*/
    aux  = (Aux *) auxstruct;
    ball = aux->ball;
    pd   = aux->pad;

    while (1)
    {
        lose = check(pd, ball, aux->rows, aux->cols);
        /*If you lose or if the player wants to quit the game*/
        if (lose == 1 || pd->stop == 0)
        {
            pd->stop = 0;
            return NULL;
        }
        /*we delete the ball in its current position*/
        i_writeCharMap(pd->intf, ' ', ball->ypos, ball->xpos, 1);
        /*We move the ball*/
        ball->xpos = ball->xpos + ball->xdir;
        ball->ypos = ball->ypos + ball->ydir;
        /*we print it*/
        printBall(pd->intf, *ball);
        /*we delay it MAYBE OR SPEED INCREASES??*/
        usleep(1000 * 30); /*EN micro segundo, ponemos 500 milis*/
        /*MAYBE WE HAVE A COUNTER TO KNOW WHEN TO STOP??*/
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
    Aux       *auxstruct;

    srand(time(NULL) + clock());

    if (i == NULL)
    {
        return -1;
    }

    /*Lets alloc memory for our pointers*/
    pd = (Pad *) malloc(sizeof(Pad));
    if (pd == NULL)
        return -1;
    ball = (Ball *) malloc(sizeof(Ball));
    if (ball == NULL)
    {
        free(pd);
        return -1;
    }
    auxstruct = (Aux *) malloc(sizeof(Aux));
    if (auxstruct == NULL)
    {
        free(pd);
        free(ball);
        return -1;
    }

    /*FIXED VALUES OF STRUCTS*/
    pd->pad  = '|';
    pd->size = 2;
    pd->xpos = 4;

    ball->obj = 'o';

    /*Lets set our auxstruct pointers*/
    auxstruct->pad  = pd;
    auxstruct->ball = ball;

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
    auxstruct->rows = rows;
    auxstruct->cols = cols;

    /*Initialize the ypos of the pad*/
    pd->ypos = 5; /*pad is ocupying y=5 and y=4 */
    /*Print the pad*/
    printPad(i, *pd);

    /*Initialize the ball*/
    ball->xpos = cols / 2; /*Fix the ball more or less in the center of the map*/
    ball->ypos = rows / 2;

    ball->xdir = 1; /*Always starts towards the wall*/
    /*random direction of Y*/
    random = rand() % 3;
    if (random == 2)
    {
        random = -1;
    }
    ball->ydir = random;

    /*We set the speed in seconds*/
    ball->speed = 1; /* is this enough??*/

    /*Print the ball*/
    printBall(i, *ball);

    /*We assign the interface to pd so we can use it in threads*/
    pd->intf = i;

    /*We config the terminal for pad movement (autorepeat rate)*/
    system("xset r rate 100");
    /*Create thread for pad movement*/
    pthread_create(pth, NULL, pad_movement, (void *) pd);
    /*The same for the ball*/
    pthread_create(pth + 1, NULL, ball_movement, (void *) auxstruct);

    /*We wait for the  ball thread to stop, if the player wants to quit from*/
    /*player movement it will as well kill ball thread, so its enough to quit
       the last one*/
    pthread_join(pth[1], NULL);



    /*WE NEED TO CHECK FOR LOSING OR WINNING*/

    /*we cancel pad_movement*/
    pthread_cancel(pth[0]);

    /*we cancel ball_movement*/
    pthread_cancel(pth[1]);

    /*We set back to normality the autorepeat rate*/
    system("xset r rate 500");

    /*we free pad and ball*/
    free(auxstruct);
    free(pd);
    free(ball);
    return 1;
}























