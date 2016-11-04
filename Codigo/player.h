#ifndef PLAYER_H
#define PLAYER_H
#include <stdlib.h>
#include "types.h"
#include <stdio.h>

typedef struct _Player Player;

Player *playerfromfile(FILE*);

Player *player_ini();
/*Function: Initializes the player  	      */
/*Parameters: None 		     	      */
/*Return: Player* or NULL if an error happens */



void player_free(Player*);
/*Function: Frees a player	  */
/*Parameters: Pointer to player   */
/*Return: nothing                 */




Status player_setName(Player*, char*);
/*Function: Sets the name of the player    	      */
/*Parameters: Pointer to Player and an array of chars   */
/*Return: OK if it has succeeded ERROR if it hasn't     */




char *player_getName(Player*);
/*Function: Gives back the name of the player	       */
/*Parameters: Pointer to char	 		       */
/*Return: An array of chars with the name of the player*/
/*its a COPY YOU MUST FREE IT			        */




Status player_setSpaceid(Player*, int);
/*Function: Sets the space where the player is 		*/
/*Parameters: Pointer to player and an integer   	*/
/*Returns: ERROR or OK                                  */




int player_getSpaceid(Player*);
/*Function: Gives back the id of the space where the player is */
/*Parameters: Pointer to player                                */
/*Return: int with the id of the space                         */



Status player_setCoordinateX(Player*, int);
/*Function: Sets the coordinate x of the location of the player */
/*Parameters: Pointer to player and an integer                  */
/*Return: ERROR or OK                                           */




int player_getCoordinateX(Player*);
/*Function: Gives back the coordinate x of the location of the   */
/*player					 	         */
/*Parameters: Pointer to player 		  	         */
/*Return: int with the coordinate x of the location of the player*/




Status player_setCoordinateY(Player*, int);
/*Function: Sets the coordinate y of the location of the player	*/
/*Parameters: Pointer to player and an integer                  */
/*Return: ERROR or OK                                           */




int player_getCoordinateY(Player*);
/*Function: Gives back the coordinate y of the location of the   */
/*player  							 */
/*Parameters: Pointer to player 		  	         */
/*Return: int with the coordinate y of the location of the player*/


#endif
