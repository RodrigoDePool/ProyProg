#ifndef MENU_H
#define MENU_H
#include "interface.h"
#include "world.h"
#define MENU_BASE         "Codigo/DATA/Menu/menuGraph"
#define MENU_INST         "Codigo/DATA/Menu/menuInst"
#define MENU_INDEX        "Codigo/DATA/Menu/Index"
#define MENU_CREATE       "Codigo/DATA/Menu/Create"
#define CREATE_INST       "Codigo/DATA/Menu/CreateInst"
#define CREATE_COMMAND    "Codigo/DATA/Menu/CreateCommand"
#define LOAD_INST         "Codigo/DATA/Menu/LoadInst"
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
World *menu();

#endif