
#include "cop.h"




Status drawing (void* c, char* obj, char** answers, int nans){
	int i;
	for(i = 0; i<nans; i++){
		printf("\t%s\n", answers[i]);
	}
	return OK;
}
Status painting (void* c, char* obj, char** answers, int nans){
	int i;
	for(i = 0; i<nans; i++){
		printf("\t%s\n", answers[i]);
	}
	return OK;
}
Status running (void* c, char* obj, char** answers, int nans){
	int i;
	for(i = 0; i<nans; i++){
		printf("\t%s\n", answers[i]);
	}
	return OK;
}
	
int main(){
	CoP* c;
	FILE *f;
	int i, j;
	pfun pdrawing = &drawing;
	pfun ppainting = &painting;
	pfun prunning = &running;
	void *foo_pointer = (void*)&i;
	
	
	f = fopen("cop.txt", "r");
	if(!f) return -1;
	c = cop_ini(f);
	if(!c){
		fclose(f);
		return -1;
	}
	
	/*Añadimos asociaciones, comprobamos si se hizo bien*/
	assoc_add (c, "internal_draw", pdrawing);
	assoc_add (c, "internal_paint", ppainting);
	assoc_add (c, "internal_run", prunning);
	
	/*Test cop execute: funcion solo imprime todas sus posibles respuestas*/
	printf("Ejecutamos comando draw spocks: esperamos 2 respuestas\n");
	cop_execute(c, "draw spocks", foo_pointer);
	printf("Ejecutamos comando paint lagartos: esperamos 3 respuestas\n");
	cop_execute(c, "paint lagartos", foo_pointer);
	printf("Ejecutamos comando run tijeras: esperamos 1 respuesta\n");
	cop_execute(c, "run tijeras", foo_pointer);
	
	
	fclose(f);
	cop_free(c);	
}

