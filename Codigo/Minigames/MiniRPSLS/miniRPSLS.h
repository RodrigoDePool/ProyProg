#ifndef MINIRPSLS
#define MINIRPSLS
#include <../../interface.h>
#define INI_PATH
#define SPOCK_PATH
#define LIZZARD_PATH
#define SCISSORS_PATH
#define ROCK_PATH
#define PAPER_PATH
#define RPSLS_INST_PATH
#define WAIT 15000

/*
  Returns 1 in case the player wins the minigame
  Returns 0 in case the player loses the minigame
*/
int miniRPSLS(Interface *i);

#endif
