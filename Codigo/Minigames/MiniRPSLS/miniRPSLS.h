#ifndef MINIRPSLS
#define MINIRPSLS
#include "../../interface.h"
#define INI_PATH "DATA/miniInst/RPSLS/RPSLSini"
#define SPOCK_PATH "DATA/miniInst/RPSLS/SPOCK"
#define LIZZARD_PATH "DATA/miniInst/RPSLS/LIZZARD"
#define SCISSORS_PATH "DATA/miniInst/RPSLS/SCISSORS"
#define ROCK_PATH "DATA/miniInst/RPSLS/ROCK"
#define PAPER_PATH "DATA/miniInst/RPSLS/PAPER"
#define RPSLS_INST_PATH "DATA/miniInst/RPSLS/InstructionsRPSLS"
#define WAIT 15000

/*
  Returns 1 in case the player wins the minigame
  Returns 0 in case the player loses the minigame
  Returns 2 in case the player ties
*/
int miniRPSLS(Interface *i);

#endif
