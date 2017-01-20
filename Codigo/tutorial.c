#include "tutorial.h"
#include <unistd.h>

char YorN2()
{
    char c;
    do
    {
        c = _read_key();
    } while (c != 'y' && c != 'n');
    return c;
}

void waitUntilNotArrow()
{
    char c = NORTH;
    while (c == NORTH || c == SOUTH || c == EAST || c == WEST)
    {
        c = _read_key();
    }
    return;
}

int tutorial(World *w)
{
    Interface * i;
    int       flag1;
    int       pcol;
    int       prow;
    int       sid;
    int       pspace;
    char      ** map;
    char      c;
    Space     * s;
    Door      * d;


    i = world_getInterface(w);
    i_readFile(i, "Codigo/DATA/Dialogue/TutorialDialogue/1", 0, 0, 3);

    waitUntilNotArrow();
    waitUntilNotArrow();
    i_cleanCommand(i);
    i_readFile(i, "Codigo/DATA/Dialogue/TutorialDialogue/2", 0, 0, 3);

    waitUntilNotArrow();

    /*sets first maps*/
    prow   = world_getPlRow(w);
    pcol   = world_getPlCol(w);
    pspace = world_getPlSpaceID(w);
    map    = world_getSpaceMap(w, pspace);
    i_setMap(i, map);
    i_drawPl(i, prow, pcol);
    i_cleanCommand(i);
    i_readFile(i, "Codigo/DATA/Dialogue/TutorialDialogue/3", 0, 0, 3);

    i_readFile(i, "Codigo/DATA/Dialogue/tutorialDisplay", 1, 1, 2);
    /*This flag will controll that you move 4 spaces*/
    flag1 = 0;

    while (flag1 < 4)
    {
        c = _read_key();


        if (c == EXIT_KEY)
        {
            i_readFile_notMap(i, EXIT_POPUP, 12, 40, 1);
            c = YorN2();
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
            flag1++;

            /*we move the player*/
            move(i, c);
        }
    }


    i_cleanCommand(i);
    i_readFile(i, "Codigo/DATA/Dialogue/TutorialDialogue/4", 0, 0, 3);
    waitUntilNotArrow();

    i_cleanCommand(i);
    i_readFile(i, "Codigo/DATA/Dialogue/TutorialDialogue/5", 0, 0, 3);

    /*This flag will controll that you move pass through a door*/
    flag1 = 0;

    while (flag1 < 1)
    {
        c = _read_key();


        if (c == EXIT_KEY)
        {
            i_readFile_notMap(i, EXIT_POPUP, 12, 40, 1);
            c = YorN2();
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
                flag1++;
                /*id of the door*/
                sid = d->neighbour;


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
        }
    }

    i_cleanCommand(i);
    i_readFile(i, "Codigo/DATA/Dialogue/TutorialDialogue/6", 0, 0, 3);
    waitUntilNotArrow();
    i_cleanCommand(i);

    /*This flag will controll that you reach the balcony*/
    flag1 = 0;

    while (flag1 < 1)
    {
        c = _read_key();


        if (c == EXIT_KEY)
        {
            i_readFile_notMap(i, EXIT_POPUP, 12, 40, 1);
            c = YorN2();
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
            /*We check if player has reached the end of the balcony*/
            if (sid == 6 && prow < 20 && prow > 15 && pcol == 11)
            {
                flag1++;
            }


            /*we get the space id and check for a door*/
            pspace = world_getPlSpaceID(w);
            s      = world_getSpace(w, pspace);
            d      = space_checkDoorAPoint(s, pcol, prow);

            if (d != NULL)
            {
                /*id of the door*/
                sid = d->neighbour;


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
        }
    }

    One2Two_animation(i);
    /*SET FOR THE NEXT LEVEL (0)*/
    world_setPlSpaceID(w, 7);
    world_setPllevel(w, 0);
    i_drawPl(i, 21, 70);

    return 1;
}

