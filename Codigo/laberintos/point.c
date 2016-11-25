#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "point.h"
#include <limits.h>

struct _Point{
    char symbol;
    int x;
    int y;
};

Point *point_ini(){
    Point *pc = NULL;
    
    pc = (Point*)malloc(sizeof(Point)); 
    if(!pc) return NULL;
    
    return pc;
}

void point_free(Point *point){
    if(point != NULL) free(point);
}

int point_getCoordinateY(const Point * pp){
    if(!pp || pp->y<0 || pp->y>INT_MAX) return -1; 
    
    return pp->y; 
}

int point_getCoordinateX(const Point * pp){
    if(!pp || pp->x<0 || pp->x>INT_MAX) return -1;
    return pp->x;
}

char point_getSymbol(const Point * pp){
    if(!pp) return ERRORCHAR;
    return pp->symbol;
}

Point * point_setCoordinateX(Point *pp, const int x){
    if(!pp || x<0 || x>INT_MAX) return NULL;
    pp->x = x; 
    return pp;
}

Point * point_setCoordinateY(Point *pp, const int y){
    if(!pp || y<0 || y>INT_MAX) return NULL;
    pp->y = y; 
    return pp;
}

Point * point_setSymbol(Point *pp, const char s){
    if(!pp) return NULL;
    pp->symbol = s;
    return pp;
}

Bool point_equals(const Point *pp, const Point *qq){
    if(!pp || !qq) return FALSE;
    if (pp->x == qq->x && pp->y == qq->y && pp->symbol == qq->symbol) return TRUE;
    return FALSE;  
}

Point * point_copy(const Point * pp){
    Point *qq = NULL;
    if(!pp) return NULL;
    qq = point_ini();
    if(!qq) return NULL;
    qq->symbol = pp->symbol; 
    qq->x = pp->x;
    qq->y = pp->y;
    return qq;
}

int point_print(FILE *f, const Point *pp){
    if(!pp || !f) return -1;
    return fprintf(f, "[(%d, %d) : %c]", point_getCoordinateX(pp), point_getCoordinateY(pp), point_getSymbol(pp));
}
