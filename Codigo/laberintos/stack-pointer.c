#include "stack.h"

struct _Stack {
    EleStack** top;
    EleStack* item[MAXSTACK];
};

Stack * stack_ini(){
    int i;
    Stack *ps;

    ps = (Stack *) malloc (sizeof(Stack));


    for (i=0; i<MAXSTACK; i++) ps->item[i]=NULL;
    ps->top = &(ps->item[-1]);

    return ps;
}

void stack_free(Stack *ps){
    EleStack **aux;
    aux = ps->top + 1;

    while(aux != &ps->item[-1]){
        elestack_free(*(aux));
        aux--;
    }
    free(ps);
}

Stack * stack_push(Stack *ps, const EleStack *pe){
    EleStack *aux = NULL;
    if (!ps || !pe || stack_isFull(ps) == TRUE) return NULL; 

    aux = elestack_copy(pe);
    if (!aux) return NULL;

    ps->top ++;

    *(ps->top) = aux;

    return ps;
}

EleStack * stack_pop(Stack *ps){
    EleStack *copy;

    if(!ps || stack_isEmpty(ps) == TRUE) return NULL;

    copy = *(ps->top); /*hacemos un puntero copia que apunte al puntero "objetivo" de ps->top*/
    if(!copy) return NULL;

    ps->top--; /*Decrementamos ps->top porque ya hemos guardado su contenido en copy*/

    return copy;
}

EleStack * stack_top(const Stack *ps){
    EleStack *aux = NULL;
    if(!ps || stack_isEmpty(ps) == TRUE) return NULL;

    aux = elestack_copy(*(ps->top));
    if(!aux) return NULL;

    return aux;

}

Bool stack_isEmpty(const Stack *ps){
    if(!ps) return TRUE;

    if(ps->top == &(ps->item[-1])) return TRUE;

    else return FALSE;
}

Bool stack_isFull(const Stack *ps){
    if(!ps) return FALSE;

    if(ps->top == &(ps->item[MAXSTACK - 1])) return TRUE;

    else return FALSE;
}


int stack_print(FILE *f, const Stack *ps){
    int cantidad=0; 
    EleStack **print; /*Necesitamos print (puntero a puntero) para poder 
                    recorrer la pila sin desplazar top*/

    if(!f || !ps) return -1;

    print = ps->top;

    while(print != &(ps->item[-1])){
        cantidad += elestack_print(f, *(print));
        fprintf(f, "\r\n");
        print--;
    }

    return cantidad;
}
