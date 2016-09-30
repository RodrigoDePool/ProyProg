#ifndef OBJECT_H
#define OBJECT_H
#include <stdlib.h>
#include <stdio.h>
#define HASIT 1
#define HASNIT 0

typedef struct _Object Object;

typedef enum{HASIT=1, HASNIT=0}Possession;

Object *object_ini();



#endif
