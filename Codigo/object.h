#ifndef OBJECT_H
#define OBJECT_H
#include <stdlib.h>
#include <stdio.h>
#include "types.h"



typedef struct _Object Object;

/*Function: Creates an object with its variables to NULL or -1,*/
/*except for has which is set to FALSE                         */
/*Parameters: -                                                */
/*Returns: Object *                                            */
Object *object_ini();

/*Function: free an object and all its variables    */
/*Parameters: Pointer to object                     */
void object_free(Object *o);

/*Function: sets the name of an object         */
/*Parameter: pointer to object and string(name)*/
/*Returns: ERROR or Ok                         */
Status object_set_name(Object *,char *);

/*Function: sets the description of an object         */
/*Parameters: pointer to object and string(description)*/
/*Returns: ERROR or OK                                */
Status object_set_desc(Object *o, char *desc);

/*Function: sets the spaceid                          */
/*Parameters: Object * and char * with the description*/
/*Returns: ERROR or OK*/
Status object_set_spaceid(Object *o, int spaceid);


/*Function: sets the objectid                          */
/*Parameters: Object * and integer>0 id		       */
/*Returns: ERROR or OK				      */
Status object_set_id(Object *o, int oid);


/*Function: Sets and object as picked by the player*/
/*Parameters:Pointer to object that is to be picked*/
/*Return: ERROR or OK                              */
Status object_pick(Object *o);


/*Function: Sets and objects as droped by the player*/
/*Parameters: Pointer to object that is to be droped*/
/*Return:ERROR or Ok	       			    */
Status object_drop(Object *o);


/*Function: Returns the name of an object 							  */
/*Parameters:Pointer to Object you wish to know the name of 		  */
/*Return: Returns a pointer to char with the name that HAS TO BE FREED*/
/*NULL if its not set or in case of memory problem 				      */
char *object_return_name(Object *o);


/*Function: Returns the description of an object 		 					  */
/*Parameters: Pointer to object 						 					  */
/*Return: Returns string of characters that MUST BE FREED, NULL if its not set*/
/*or in case of memory problem												  */
char *object_return_desc(Object *o);


/*Function: Returns the id of the space an object is in*/
/*Parameters: Object * 					  		 	   */
/*Return: int id of the space, -1 if its not set 	   */
int object_return_spaceid(Object *o);


/*Function: Gives back the id of an object 				  */
/*Parameters: Pointer to object 		  				  */
/*Return: int with the id of the object, -1 if its not set*/ 
int object_return_id(Object *o);


/*Function: returns whether the player has or no the object*/
/*Parameters: Object * 									   */
/*Return: TRUE if the player has it, FALSE in anyother cas */
Bool object_return_has(Object *o);


/*Returns: An initialized pointer to object given in the file*/
/*Parameter: opened file with the format of the structure    */
/*SAME ORDER AND SEPARETED BY \n							 */
Object *objectfromfile(FILE *f);

#endif
