#include "cop.h"

int main(){
	CoP* c;
	FILE *f;
	
	f = fopen("cop.txt", "r");
	if(!f) return -1;
	c = cop_ini(f);
	if(!c){
		fclose(f);
		return -1;
	}
	
	assoc
	
	
	cop_free(c);	
}

