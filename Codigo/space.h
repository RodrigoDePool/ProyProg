#ifndef SPACE_H
#define SPACE_H
#include "types.h"
typedef struct space_ Space;


/*Creates a new space, allocating memory, NULL in case of error*/
Space * spaceIni();

/*Frees memory allocated for a space and its members*/
void spaceFree(Space *s);

/*Returns sId of s, -1 in  case of error*/
int spaceId(Space *s);

/*Returns sId of the chosen s neighbour (minigame case 4:7). -1 in case of error*/
int space_ neighbour( Space *s, int n);

/*JUAN
Con la funcion anterior me he dado cuenta de que lo de definir vecinos 1-4 habit 5-8 minijuegos esta muy bien si 
asumes que siempre estas en habitaciones, pero eso no sirve cuando estas dentro del space de un minijuego: 
Estas en el minijuego y podrias moverte a su vecino numero 6 que seria un minijuego inside a minijuego¿? 
Como el unico movimiento que podriamos hacer en un minijuego es salir (volver a la habitacion "padre"), 
se me ocurre implementar una funcion minig_exit, ¿que opinas?*/

/*LUCIA
estoy completamente de acuerdo contigo, los minijuegos no son habitaciones como las otras, de hecho, no se si deberian tener las mismas
propiedades (light, neighbour como bien has dicho tampoco tiene sentido...) Igual deberiamos crear un nuevo tipo que sea Minigame y que
ya pensaremos como implementar mas adelante cuando vayamos pensando como van a funcionar los minijuegos (que van a tener una tela...) 
El minigame es muy parecido a un space en el sentido de que, al menos por ahora tendría un spaceId igual que un space, pero detrás de éste
spaceId se encuentra algo distinto a un space normal. ¿Que opinas?

Tambien he cambiado el formato de algunas funciones para que todas tengan el mismo formato: primeraPalabraMinusculaYMayusculaLasDemas
Si prefieres la barra baja lo podemos cambiar tambien :D
*/

/*Takes the player back to the minigame "parent" space, returning parent sId, -1 in case of error*/
int exitMgame(Space *s);

/*Returns short description of s, NULL in case of error*/
char *sDesc(Space * s);

/*Returns long description of s, NULL in case of error*/
char *lDesc(Space * s);

/*Returns 0 if the chosen s neigbour is unlocked, 1 if its locked*/
Bool isLocked(Space *s, int dir)

/*Returns char map of the specified space, NULL in case of error*/
char **whatIsInMap(Space *c, int *s);

/*Returns 0 if s is dark, 1 if not*/
/*To use "bool, true, false" instead of "_Bool, 1, 0" : <stdbool.h> has to be included*/
Bool canISee(Space *s);

/*Returns number of columns of s map, -1 error*/
int nCols(Space *s);

/*Returns number of rows of s map, -1 error*/
int nRows(Space *s);

/*Up to here, we have the ini/free functions and the ones to access all members of struct*/

/*Returns sId of the space you have gone to, -1 in case of no space, -2 if locked*/
int go(Space *s, int dir);

/*Status tells us whether the user wants to lock or unlock door
 Returns 0 if succesfully (un)locked, -1 in case of no space, -2 if no key and 1 if it is already locked or unlocked*/
int unlock(Space *s, int dir, Bool status);


#endif