#ifndef MINIRPSLS
#define MINIRPSLS
#include "../../interface.h"
#define INI_PATH           "Codigo/DATA/miniInst/RPSLS/RPSLSini"
#define SPOCK_PATH         "Codigo/DATA/miniInst/RPSLS/SPOCK"
#define LIZZARD_PATH       "Codigo/DATA/miniInst/RPSLS/LIZZARD"
#define SCISSORS_PATH      "Codigo/DATA/miniInst/RPSLS/SCISSORS"
#define ROCK_PATH          "Codigo/DATA/miniInst/RPSLS/ROCK"
#define PAPER_PATH         "Codigo/DATA/miniInst/RPSLS/PAPER"
#define RPSLS_INST_PATH    "Codigo/DATA/miniInst/RPSLS/InstructionsRPSLS"
#define TICK_PATH          "Codigo/DATA/miniInst/RPSLS/TICK"
#define CROSS_PATH         "Codigo/DATA/miniInst/RPSLS/CROSS"
#define ROUND_PATH         "Codigo/DATA/miniInst/RPSLS/ROUNDS"
#define INFO_RPSLS         "Codigo/DATA/miniInst/RPSLS/info"
#define WAIT               5 /*sleep time in seconds between rounds*/

/*
   Returns 1 in case the player wins the minigame
   Returns 0 in case the player loses the minigame
   Returns 2 in case the player ties
   REturns -1 if error
 */
int miniRPSLS(Interface *i);

#endif
