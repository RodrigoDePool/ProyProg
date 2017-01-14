#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lineread.h"
#include "interface.h"
#include "space.h"
#include "world.h"

#define SAVE_KEY     's'
#define SOLVE_KEY    'x'
#define HELP_KEY     'h'


/*
   mainGame file


 */
int main()
{
    World     *w;
    Interface *i;
    Door      *d;
    /*row , col and space the player is in*/
    int       prow, pcol, pspace;
    /*flag to see if the key press was a move*/
    int       fmove;
    int       sid;
    char      c;
    /*Starting menu*/
    w = menu();
    if (menu == NULL)
    {
        return 0;
    }
    /*Get prow, pcol,pspace*/
    /*get map of pspace*/
    /*get interface and set it in i*/
    /*set interface map of space*/
    /*draw map*/
    /*set player with prow and pcol*/
    /*set descriptions and objects(part of the riddle) in display*/
/*SEE IF YOU ARE IN SPACE 0 AND EXECUTE TUTORIAL*/
    /*main game loop*/
    while (1)
    {
        fmove = 0;
        c     = _read_key();
        /*if its a move*/
        if (c == SOUTH || c == NORTH || c == WEST || c == EAST)
        {
            fmove = 1; /*there was a movement*/
            move(i, c)
        }
        else if (c == SAVE_KEY)
        {
            /*menu function of save*/
        }
        else if (c == SOLVE_KEY)
        {
            /*Solve function*/
            /*if fail print fail message and thats it*/
            /*else animation and set WHOLE new space and stuff*/
        }
        else if (c == HELP_KEY)
        {
            /*print help message*/
        }
        /*ADD EXIT GAMEE*/
        /*if there was a movement*/
        if (fmove == 1)
        {
            /*get new prow, pcol after movement*/
            d = space_checkDoorAPoint(pspace, pcol, prow);
            if (d != NULL)
            {
                /*print 'Do you want to go through the door? (y/n)'*/
                do
                {
                    c = _read_key();
                } while (c != 'y' && c != 'n');
                if (c == 'y')
                {
                    /*check if d is new space or a minigame*/
                    /*if space set new space with coords and map and stuff and
                       descriptions*/
                    /*else must be a minigame, then execute it
                       maybe allow it to play again or go back to the map
                       in case of winning print message and give object*/
                }
            }
        }
    }
}