
#define NDEBUG
#include <assert.h>
#include "game.h"
#define STRPATH
#define INIROW 2
#define INICOL 2
#define SLEEPTIME 2

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
		fscanf(f, "%m[^|]|\n", (s->st)+i);
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


/*Gives a clue to the space riddle if the player has all the space objects
  Else, tells the player that he cannot be helped
  Returns -1 if anything went wrong*/
int game_help(World *w, String *s){
	assert(w && s);
	Interface *in = world_getInterface(w);
	if(!in) return -1;
	if(world_getNumObjects(w) != 3){
		i_drawStr(in, s->st[0], INIROW , INICOL , 2);
		sleep(SLEEPTIME);
	}else{
	/*Level get clue?*/
	}
	return 0;
}

/*Saves the game and shows message
  Returns -1 if something went wrong, else 1*/
int game_save(World *w, String* s){
	assert(w && s);
	Interface *in = world_getInterface(w);
	if(!in) return -1;
	if(world_saveToFile(w, SAVEPATH) == -1){
		i_drawStr(in, s->st[1], INIROW , INICOL , 2);
		sleep(SLEEPTIME);
		return -1;
	}else{
		i_drawStr(in, s->st[2], INIROW , INICOL , 2);
		sleep(SLEEPTIME);
		return 0;
	}
}

int game_solve(World *w, String *s){
	assert(w && s);
	Interface *in = world_getInterface(w);
	char *solution;
	Level *l;
	if(!in) return -1;
	
	/*"Enter the solution" string*/
	i_drawStr(in, s->st[3], INIROW , INICOL , 2);
	
	/* Meto en solution la solucion del jugador... ¿habra que quitar el intro?*/
	/*Se puede resolver sin tener todos los objetos?*/
	/*Como obtienes el level??*/	
	l = world_getLevel(w);
	if(!l) return -1;
	if( strcmp(solution, l->solution) == 0 ){
		/*You passed level string*/
		i_drawStr(in, s->st[4], INIROW , INICOL , 2);
		sleep(SLEEPTIME);
		return 0;
	}else{
		/*Youre wrong string*/
		i_drawStr(in, s->st[2], INIROW , INICOL , 2);
		sleep(SLEEPTIME);
		return 0;
	}	
}


int game_f(World *w, int n){
	assert(w && n>-1 && n<3);
	String *s = string_ini(STRPATH);
	if(s == NULL)
		return -1;
	
	if(n == 0){
		return game_help(w, s);
	}else if(n == 1){
		return game_save(w, s);
	}else if(n == 2){
		return game_solve(w, s);
	}
}



