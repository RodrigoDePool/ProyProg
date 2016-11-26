#include "elestack.h"

struct _EleStack { 
    Point* info; 
}; 

EleStack * elestack_ini(){
    EleStack * pe;
    pe = (EleStack *)malloc (sizeof (EleStack)); /*Si pe es null, 
    no hace falta comprobar error porque ya devuelve null*/
    pe->info = NULL;
    return pe;
}

void elestack_free(EleStack * pe){
    if(pe->info != NULL) point_free (pe->info);
    if(pe != NULL) free (pe);
}

EleStack * elestack_setInfo(EleStack * pe, void * p){
    if (!pe || !p) return NULL;

    p = (Point *) p;

    if(pe->info != NULL) point_free(pe->info);

    pe->info = point_copy(p);

    if(!pe->info) return NULL;

    return pe;
}

void * elestack_getInfo(EleStack *pe){
    if (!pe) return NULL;
    return pe->info;
}

EleStack * elestack_copy(const EleStack *pe){
    EleStack *pc;
    if (!pe) return NULL;
    pc = elestack_ini();
    pc = elestack_setInfo(pc, pe->info);
    return pc;
}

Bool elestack_equals(const EleStack *pe1, const EleStack *pe2){
    if (!pe1 || !pe2) return FALSE;
    if (point_equals(pe1->info, pe2->info) == TRUE) return TRUE;
    else return FALSE;
}

int elestack_print(FILE *f, const EleStack *pe){
    int cantidad;
    
    if (!f || !pe) return -1;

    cantidad = point_print(f, pe->info);
    return cantidad;
}
