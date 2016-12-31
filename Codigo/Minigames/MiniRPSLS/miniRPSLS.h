#ifndef MINIRPSLS
#define MINIRPSLS
#include "../../interface.h"
#define INI_PATH           "DATA/miniInst/RPSLS/RPSLSini"
#define SPOCK_PATH         "DATA/miniInst/RPSLS/SPOCK"
#define LIZZARD_PATH       "DATA/miniInst/RPSLS/LIZZARD"
#define SCISSORS_PATH      "DATA/miniInst/RPSLS/SCISSORS"
#define ROCK_PATH          "DATA/miniInst/RPSLS/ROCK"
#define PAPER_PATH         "DATA/miniInst/RPSLS/PAPER"
#define RPSLS_INST_PATH    "DATA/miniInst/RPSLS/InstructionsRPSLS"
#define TICK_PATH          "DATA/miniInst/RPSLS/TICK"
#define CROSS_PATH         "DATA/miniInst/RPSLS/CROSS"
#define ROUND_PATH         "DATA/miniInst/RPSLS/ROUNDS"
#define WAIT               5 /*sleep time in seconds between rounds*/

/*
   Returns 1 in case the player wins the minigame
   Returns 0 in case the player loses the minigame
   Returns 2 in case the player ties
   REturns -1 if error
 */
int miniRPSLS(Interface *i);
/*
    FALTA AGREGAR EL MODO HARD CORE QUE SERIA QUE TE IMPIDIERA VOLVER pointer
    DONDE HAS ANDADO
 */
#endif
