
/*Incluyo .c en vez de .h para poder acceder a los campos de las structs*/
#include "cop.h"

int main(){
	CoP* c;
	FILE *f;
	int i, j;
	
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
	
	
	fclose(f);
	cop_free(c);	
}

