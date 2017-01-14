
#define NDEBUG
#include <assert.h>
#include "game.h"
#define STRPATH


struct _Strings{
	int nums;
	char **st;	
}

String *string_ini(){
	int nst, i, j;
	FILE *f = fopen(STRPATH, "r");
	if(f == NULL)
		return NULL;
	
	String *s = (String *)malloc(sizeof(String));
	if(st == NULL){
		fclose(f);
		return NULL;
	}
	fscanf(f, "%d\n", &(s->ns));
	s->st =(char **)malloc(s->ns * sizeof(char *));
	if(s->st == NULL){
		string_free(s);
		fclose(f);
		return NULL;
	}
	for(i = 0;i < s->ns; i++){
		fscanf(f, "%m[^\n]\n", (s->st)+i);
		if( s->st[i] == NULL ){
			string_free(s);
			fclose(f);
			return NULL;			
		}
	}
	return s;
}

void string_free(String *s){
	int i;
	if(s){
		if(s->st){
			for(i = 0; i < s->ns; i++){
				if(s->st[i])
					free(s->st[i]);
			}
			free(s->st);
		}
		free(s);
	}
}


int game_help(World *w){
	assert(w);
	Interface *in = world_getInterface(w);
	if(!in) return -1;
	if(world_getNumObjects != 3){
		
	}
	
}


int game_save(World *w);
