#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "space.h"
#include "world.h"
#include "menu.h"
#include "game.h"
#include "tutorial.h"
#define SAVE_KEY          's'
#define SOLVE_KEY         'x'
#define HELP_KEY          'h'
#define EXIT_KEY          'q'
#define EXIT_POPUP        "Codigo/DATA/popups/exit"
#define MINI_POPUP        "Codigo/DATA/popups/mini"
#define FINISHED_POPUP    "Codigo/DATA/popups/finished"
#define WIN_POPUP         "Codigo/DATA/miniInst/youwon"
#define LOST_POPUP        "Codigo/DATA/miniInst/youlost"
#define NEW_POPUP         "Codigo/DATA/popups/newobject"
#define FAIL_POPUP        "Codigo/DATA/popups/failed"
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
/*
    Frees the map
 */
void map_mainFree(char **map, int rows);
/*
    Cheating function
 */
void afro(World *w);





int main()
{
    World     *w;
    Interface *i;
    Space     *s;
    Door      *d;
    Minigame  minigame;
    /*row , col and space the player is in*/
    int       prow, pcol, pspace;
    /*flag to see if the key press was a move*/
    int       sid, aux, finished, win;
    char      c;
    char      **map;

    /*Starting menu*/
    w = menu();
    if (w == NULL)
    {
        _term_close();
        return 0;
    }

    i = world_getInterface(w);

    /*If we are in first level do some shit about the tutorial*/

    if(world_getPllevel(w)==-1){
        if(tutorial(w)==0)
            return 0;
    }

    /*sets first maps*/
    prow   = world_getPlRow(w);
    pcol   = world_getPlCol(w);
    pspace = world_getPlSpaceID(w);
    map    = world_getSpaceMap(w, pspace);
    i_setMap(i, map);
    i_drawPl(i, prow, pcol);

    /*FUNCTION set info panel*/


    /*main game loop*/
    while (1)
    {
        c = _read_key();
        if (c == SAVE_KEY)
        {
            /*menu function of save*/
        }
        else if (c == SOLVE_KEY)
        {
            /*Solve function*/
            /*if fail print fail message and thats it*/
            /*else animation and set WHOLE new space and panel*/
            /* if you won set level*/

            /*TEST FOR LEVEL 0*/
            /*world_setPlSpaceID(w, 7);
               world_setPllevel(w, 0);
               map = world_getSpaceMap(w, 7);
               i_setMap(i, map);
               i_drawPl(i, 23, 75);
               /*END OF TEST*/
            /*TEST FOR LEVEL1*/
            /*world_setPlSpaceID(w, 8);
               world_setPllevel(w, 1);
               map = world_getSpaceMap(w, 8);
               i_setMap(i, map);
               i_drawPl(i, 2, 84);
               /*END OF TEST*/
            /*TEST FOR LEVEL 2*/
            world_setPlSpaceID(w, 9);
            world_setPllevel(w, 2);
            map = world_getSpaceMap(w, 9);
            i_setMap(i, map);
            i_drawPl(i, 2, 79);
            /*END OF TEST*/
        }
        else if (c == HELP_KEY)
        {
            game_f(w, 0);
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
        else if (c == SOUTH || c == NORTH || c == WEST || c == EAST)
        {
            /*we move the player*/
            move(i, c);
            /*get new prow, pcol after movement*/
            prow = world_getPlRow(w);
            pcol = world_getPlCol(w);
            /*we get the space id and check for a door*/
            pspace = world_getPlSpaceID(w);
            s      = world_getSpace(w, pspace);
            d      = space_checkDoorAPoint(s, pcol, prow);

            if (d != NULL)
            {
                /*id of the door*/
                sid = d->neighbour;
                aux = isItASpaceOrAMinigame(sid);

                /*if its a space*/
                if (aux == 0)
                {
                    /*info of the door the player appears in*/
                    pcol = d->nx;
                    prow = d->ny;
                    /*set the space we moved to*/
                    world_setPlSpaceID(w, sid);
                    /*take the map*/
                    map = world_getSpaceMap(w, sid);
                    /*set map and player in new position*/
                    i_setMap(i, map);
                    i_drawPl(i, prow, pcol);
                }
                /*if its a minigame*/
                else if (aux == 1)
                {
                    /*check if you have or you havent finished this game*/
                    finished = world_getMinigameFinished(w, sid);
                    /*if havent finished*/
                    if (finished == 0)
                    {
                        /*ask if the player want to play the minigame*/
                        i_readFile_notMap(i, MINI_POPUP, 12, 40, 1);
                        c = YorN();
                        i_drawAll(i);
                        if (c == 'y')
                        {
                            /*we get the space id*/
                            pspace = world_getPlSpaceID(w);
                            /*take the map and copy it*/
                            map = map_copy(world_getSpaceMap(w, pspace), 34, 113);

                            /*we play the minigame*/
                            minigame = world_getMinigame(w, sid);
                            win      = (*minigame)(i);

                            if (win == 1)
                            {
                                i_cleanMap(i);
                                i_readFile(i, WIN_POPUP, 0, 0, 1);
                                _read_key();
                                i_cleanMap(i);
                                i_readFile(i, NEW_POPUP, 12, 40, 1);
                                _read_key();
                                world_setMinigameFinished(w, sid, 1);
                                aux = world_getNumObjects(w);
                                /*In case you cheated you cant get extra objects*/
                                if (aux < 12)
                                    aux++;
                                world_setNumObjects(w, aux);
                            }
                            else
                            {
                                i_cleanMap(i);
                                i_readFile(i, LOST_POPUP, 0, 0, 1);
                                _read_key();
                                i_cleanMap(i);
                                i_readFile(i, FAIL_POPUP, 12, 40, 1);
                                _read_key();
                            }
                            /*we reset the map*/
                            i_setMap(i, map);
                            /*we reset the player*/
                            i_drawPl(i, prow, pcol);
                            /*free the copy*/
                            map_mainFree(map, 13);
                            /*RESET  THE PANEL*/

                            /*resetting map .. idrawALl??*/
                        }
                    }
                    else
                    {
                        i_readFile_notMap(i, FINISHED_POPUP, 12, 40, 1);
                        _read_key();
                        i_drawAll(i);
                    }
                }
                /*we set the info in the panel again whether we moved a space*/
                /*or we played a minigame*/
                /*FUNCTION set info panel*/
            }
        } /*Movement else if*/
        else if (c == '0')
        {
            /*CHEAT CODE*/
            afro(w);
        }
    } /*while else if*/
}     /*main*/




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

void map_mainFree(char **map, int rows)
{
    int i;
    if (map == NULL)
        return;
    for (i = 0; i < rows; i++)
        free(map[i]);
    free(map);
    return;
}


void afro(World *w)
{
    char c;
    c = _read_key();
    if (c != 'a')
        return;
    c = _read_key();
    if (c != 'f')
        return;
    c = _read_key();
    if (c != 'r')
        return;
    c = _read_key();
    if (c != 'o')
        return;
    /*Cheating stuff*/
    /*we get all the objects*/
    world_setNumObjects(w, 12);
    return;
}






