#ifndef OBJECT_H
#define OBJECT_H
#include <stdlib.h>
#include <types.h>
#define HASIT 1
#define HASNIT 0


typedef struct _Object Object;
/*Funcion: inicializa un objeto sin informacion valida en sus campos
  Entada: -
  Salida: Object *                                                  */
Object *object_ini();
/*Funcion: Libera un objeto con todos sus campos   */
/*Entrada: El puntero a objeto que queremos liberar*/
void object_free(Object *o);


#endif
