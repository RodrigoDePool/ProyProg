
/*Incluyo .c en vez de .h para poder acceder a los campos de las structs*/
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
	
	/*Comprobamos que dentro del cop creado esta la informacion que quiero*/
	printf("Número de exts (debería ser 3): %d\n", c->numexts);
	
	for(i = 0; i < c->numexts; i++){
		printf("Ext nº %d:\n", i+1);
		printf("\tExt_name: %s\n", c->exts[i]->ext_name);
		printf("\tInt_name: %s\n", c->exts[i]->int_name);
		printf("\tN_ans: %d\n", c->exts[i]->n_ans);
		for(j = 0; j < c->exts[i]->n_ans; j++){
			printf("\t\t%dº ans: %s\n", j+1, c->exts[i]->ans[j]);
		}
	}
	printf("Número de assocs (debería ser 0): %d\n", c->numassocs);
	printf("Número de maxassocs (debería ser 3): %d\n", c->maxassocs);
	
	
	/*Añadimos asociaciones, comprobamos si se hizo bien*/
	assoc_add (c, "internal_draw", pdrawing);
	assoc_add (c, "internal_paint", ppainting);
	assoc_add (c, "internal_run", prunning);
	
	for(i = 0; i < c->numassocs; i++){
		printf("\tAssoc[%d] asocia %s a %p\n", i,c->assocs[i]->int_name,
							c->assocs[i]->f);
	}
	printf("Las direcciones impresas debrían ser:\n");
	printf("\t%p\n\t%p\n\t%p\n", pdrawing, ppainting, prunning);
	
	
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
