#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "space.h"
#include "world.h"
#include "menu.h"

#define SAVE_KEY     's'
#define SOLVE_KEY    'x'
#define HELP_KEY     'h'
#define EXIT_KEY     'q'


/*
   mainGame file


 */
int main()
{
    World     *w;
    Interface *i;
    Space     *s;
    Door      *d;
    /*row , col and space the player is in*/
    int       prow, pcol, pspace;
    /*flag to see if the key press was a move*/
    int       fmove;
    int       sid;
    char      c;
    char      **map;
    /*Starting menu*/
    w = menu();
    if (menu == NULL)
    {
        return 0;
    }
    prow   = world_getPlRow(w);
    pcol   = world_getPlCol(w);
    pspace = world_getPlSpaceID(w);
    map    = world_getSpaceMap(w, pspace);
    i      = world_getInterface(w);
    i_setMap(i, map);
    i_drawPl(i, prow, pcol);

    /*SET INFO IN PANEL*/
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
            move(i, c);
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
        else if (c == EXIT_KEY)
        {
            world_free(w);
            _term_close();
            i_free(i);
            return 0;
        }
        /*if there was a movement*/
        if (fmove == 1)
        {
            /*get new prow, pcol after movement*/
            prow = world_getPlRow(w);
            pcol = world_getPlCol(w);
            s    = world_getSpace(w, pspace);
            d    = space_checkDoorAPoint(s, pcol, prow);
            if (d != NULL)
            {
                /*PRINT 'Do you want to go through the door? (y/n)'*/
                do
                {
                    c = _read_key();
                } while (c != 'y' && c != 'n');
                if (c == 'y')
                {
                    sid  = d->neighbour;
                    prow = d->ny;
                    pcol = d->nx;
                    map  = world_getSpaceMap(w, sid);
                    i_setMap(i, map);
                    i_drawPl(i, prow, pcol);
                    world_setPlSpaceID(w, sid);
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