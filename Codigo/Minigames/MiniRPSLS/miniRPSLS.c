#include "miniRPSLS.h"
#include <time.h>
#include <unistd.h>
#include <string.h>
#define rock        1
#define scissors    2
#define paper       3
#define lizzard     4
#define spock       5
#define LEN         40
#define lines       4




/*
   Plays one round of the game
   Gets the choice of the player from stdin, prints hes option,
   prints enemies option, and decides the result
   returns 0 if lost
   returns 1 if win
   returns 2 it tie
   returns -1 if error
 */
int _round(Interface *i)
{
    int ran, des;

    do
    {
        des = fgetc(stdin);
        des = des - '0';
    } while (des != 1 && des != 2 && des != 3 && des != 4 && des != 5);

    srand(time(NULL));
    ran = rand() % 5 + 1;

    /*WHO WON?*/
    /*Prints enemys choice*/
    if (ran == rock)
        i_readFile(i, ROCK_PATH, 17, 59, 1);
    if (ran == scissors)
        i_readFile(i, SCISSORS_PATH, 17, 59, 1);
    if (ran == paper)
        i_readFile(i, PAPER_PATH, 17, 59, 1);
    if (ran == lizzard)
        i_readFile(i, LIZZARD_PATH, 17, 59, 1);
    if (ran == spock)
        i_readFile(i, SPOCK_PATH, 17, 59, 1);

    if (des == rock)
    {
        i_readFile(i, ROCK_PATH, 17, 15, 1);
        if (ran == rock)
        {
            return 2;
        }
        else if (ran == lizzard || ran == scissors)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (des == scissors)
    {
        i_readFile(i, SCISSORS_PATH, 17, 15, 1);
        if (ran == scissors)
        {
            return 2;
        }
        else if (ran == lizzard || ran == paper)
        {
            return 1;
        }
        else
            return 0;
    }
    if (des == paper)
    {
        i_readFile(i, PAPER_PATH, 17, 15, 1);
        if (ran == paper)
            return 2;
        else if (ran == rock || ran == spock)
            return 1;
        else
            return 0;
    }
    if (des == lizzard)
    {
        i_readFile(i, LIZZARD_PATH, 17, 15, 1);
        if (ran == lizzard)
            return 2;
        else if (ran == spock || ran == paper)
            return 1;
        else
            return 0;
    }
    if (des == spock)
    {
        i_readFile(i, SPOCK_PATH, 17, 15, 1);
        if (ran == scissors || ran == rock)
            return 1;
        else if (ran == spock)
            return 2;
        else
            return 0;
    }
    return -1;
}


/*
   Function writes in the pointer passed the lines the game is gonna write in
   the command line, given in ROUNDS_PATH
 */
void read_sols(char **s)
{
    FILE *f;
    int  i;
    f = fopen(ROUND_PATH, "r");
    if (f == NULL)
        return;
    for (i = 0; i < lines; i++)
        fgets(s[i], LEN - 1, f);
    fclose(f);
    return;
}


int miniRPSLS(Interface *i)
{
    char **com;
    int  j, enemy = 0, points = 0, aux, col;

    /*Reservamos memoria para un array de strings*/
    com = (char * *) malloc(sizeof(char *) * lines);
    if (com == NULL)
        return -1;
    for (j = 0; j < lines; j++)
    {
        com[j] = (char *) malloc(sizeof(char) * LEN);
        if (com[j] == NULL)
        {
            j--;
            while (j >= 0)
            {
                free(com[j]);
                j--;
            }
            free(com);
            return -1;
        }
    }
    /*we initialize the screen*/
    i_cleanDisplay(i);
    i_readFile(i, INI_PATH, 0, 0, 1);
    i_readFile(i, RPSLS_INST_PATH, 0, 0, 2);
    read_sols(com); /*read lines for round plus tie text*/

    for (j = 0; j < 3 && points < 2 && enemy < 2; j++)
    {
        i_cleanCommand(i);
        i_drawStrMap(i, com[j], 1, 1, 3); /*round line*/
        aux = _round(i);
        i_cleanCommand(i);                /*we clean to draw resul*/
        /*we draw result in column*/
        switch (j)
        {
        case 0:
            col = 16;
            break;
        case 1:
            col = 48;
            break;
        case 2:
            col = 87;
            break;
        }
        if (aux == 1) /*win*/
        {
            points++;
            i_readFile(i, TICK_PATH, 31, col, 1);
        }
        if (aux == 0) /*lose*/
        {
            enemy++;
            i_readFile(i, CROSS_PATH, 31, col, 1);
        }
        if (aux == 2) /*Tie*/
        {
            i_drawStrMap(i, com[3], 31, col, 1);
        }
        sleep(WAIT);
    }

    /*Free memory*/
    for (j = 0; j < lines; j++)
    {
        free(com[j]);
    }
    free(com);

    if (points > enemy)
        return 1;
    else if (enemy > points)
        return 0;
    else
        return 2;
}
