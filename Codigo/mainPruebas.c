#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "space.h"
#include "world.h"
#include "menu.h"
#define SAVE_KEY      's'
#define SOLVE_KEY     'x'
#define HELP_KEY      'h'
#define EXIT_KEY      'q'
#define EXIT_POPUP    "Codigo/DATA/popups/exit"
#define DOOR_POPUP    "Codigo/DATA/popups/door"
#define NDEBUG
#include <assert.h>

/*
   main Game file


 */


/*
   Code of extra functions at the end
 */


/*
   Stays in a loop reading keys untill the player presses either 'y'
   or 'n'
   returns the pressed key
 */
char YorN();


/*
    given a map an its size it allocates new memory and copies it.
 */
char **map_copy(char **map, int rows, int cols);

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
    int       sid, aux;
    char      c;
    char      **map;
    _term_init();
    i = i_create(MAXCOLS - 30, MAXROWS - 6, 30, 6, '@', 40, 37, 40, 37, 40, 37);
    if (i == NULL)
        return NULL;
    i_drawAll(i);
    /*Starting menu*/
    w = worldfromfile("Codigo/DATA/LOAD/default", i);
    if (w == NULL)
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
            i_readFile_notMap(i, EXIT_POPUP, 12, 40, 1);
            c = YorN();
            if (c == 'y')
            {
                world_free(w);
                _term_close();
                i_free(i);
                return 0;
            }
            i_drawAll(i);
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
                i_readFile_notMap(i, DOOR_POPUP, 12, 40, 1);
                c = YorN();
                i_drawAll(i);
                if (c == 'y')
                {
                    aux = isItASpaceOrAMinigame(sid);
                    /*if its a space*/
                    if (aux == 0)
                    {
                        sid  = d->neighbour;
                        prow = d->ny;
                        pcol = d->nx;
                        map  = world_getSpaceMap(w, sid);
                        i_setMap(i, map);
                        i_drawPl(i, prow, pcol);
                        world_setPlSpaceID(w, sid);
                        /*are we missing any settingfor the space*/
                        /*setting info display desc + keys*/
                    }
                    else if (aux == 1)
                    {
                        /*minigame set up*/
                        /*IF LOSE*/
                        /*losing message*/
                        /*maybe allow him to go play it again or going back*/
                        /*IF WIN*/
                        /*win message, inform of new piece of info in solve*/
                        /*if they have all 3 of the minigame encourage to solve
                           the riddle*/

                        /*resetting map .. idrawALl??*/
                    }
                }
            }
        }
    }
}



char YorN()
{
    char c;
    do
    {
        c = _read_key();
    } while (c != 'y' && c != 'n');
    return c;
}



char **map_copy(char **map, int rows, int cols)
{
    char **copy;
    int  i, j;
    assert(map != NULL);
    copy = (char * *) malloc(sizeof(char *) * rows);
    if (copy == NULL)
        return NULL;
    for (i = 0; i < rows; i++)
    {
        copy[i] = (char *) malloc(sizeof(char) * cols);
        /*If there is not enough memory*/
        if (copy[i] == NULL)
        {
            for (j = 0; j < i; j++)
                free(copy[j]);
            free(copy);
            return NULL;
        }
        for (j = 0; j < cols; j++)
            copy[i][j] = map[i][j];
    }
    return copy;
}











