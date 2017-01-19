#ifndef TUTORIAL_H
#define TUTORIAL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "space.h"
#include "world.h"
#include "menu.h"
#include "game.h"
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
    Funcion del tutorial
 */
int tutorial(World *w);

#endif
