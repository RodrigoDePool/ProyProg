#include <stdio.h>
#include <stslib.h>
#include <string.h>
#include "types.h"

typedef Status (*pfun)(void*, char*);

typedef struct _Assoc Assoc;
typedef struct _Ext Ext; 
typedef struct _CoP CoP;




/*Function: creates ext from an open file       */
/*Parameter: file                              */
/*Returns:  pointer to the Ext/NULL when error */
/*Revision: 5/11/2016                  	       */
Ext *ext_ini( FILE *f)

/*Function: frees given Ext */
/*Parameter: pointer to Ext */
/*Returns:                  */
/*Revision: 5/11/16         */
void ext_free( Ext *e);

/*Function: creates assoc between a string and a function */
/*Parameter: String and pointer to the function           */
/*Returns:  Ya veré */
/*Revision:                            	      */
CoP assoc_ini (CoP *c, char *int_name, pfun f);

/*Function: creates CoP from file                             */
/*Parameter: Pointer to a OPEN file that will be rerurned OPEN*/
/*Returns: pointer to CoP/ NULL when error                    */
/*Revision: 5/11/16		                              */
CoP *cop_ini(FILE *f);




/*Function: */
/*Parameter:                 */
/*Return:   */
/*Revision		      */
int cop_execute(CoP *c, char *cmd, void *pt);
