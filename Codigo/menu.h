#ifndef MENU_H
#define MENU_H
#include "interface.h"
/*#include "world.h"*/
/*
    CHANGE VOIDS FOR WORLDS AFTER TESTS
 */
#define MENU_BASE         "DATA/Menu/menuGraph"
#define MENU_INST         "DATA/Menu/menuInst"
#define MENU_INDEX        "DATA/Menu/Index"
#define MENU_CREATE       "DATA/Menu/Create"
#define CREATE_INST       "DATA/Menu/CreateInst"
#define CREATE_COMMAND    "DATA/Menu/CreateCommand"
#define LOAD_INST         "DATA/Menu/LoadInst"
/*
    This is very sensible to format changes
 */

/*
    This function is in charge of all the menu proccess. This includes
    the player selecting a new game (or a saved one) then initializing
    the world.
    This function initializes the interface as well, this must be freed
    along with the entire world.
    returns:
        Pointer to the initialized world in case of success
        NULL in case of error
    MAYBE SOME MORE COMMENTS I SHOULD ADD??
 */
void *menu();


/*
    This function saves the file with info of the current game
 */
int save(void *w);

#endif