#ifndef OBJECT_H
#define OBJECT_H
#include <stdlib.h>
#include "types.h"



typedef struct _Object Object;

/*Function: Creates an object with its variables to NULL or -1,*/
/*except for has whchi is set to HASNIT                        */
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
/*Parameters: pointer to object and string(description*/
/*Returns: ERROR or OK                                */
Status object_set_desc(Object *o, char *desc);
#endif
