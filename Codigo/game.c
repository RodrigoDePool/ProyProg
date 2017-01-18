
#define NDEBUG
#include <assert.h>
#include "game.h"
#define STRPATH
#define CLUEPATH 
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
	FILE *f = NULL;
	int i;
	char *clue, c;
	Interface *in = world_getInterface(w);
	if(!in) return -1;
	
	if(world_getNumObjects(w) != 3){
		i_drawStr(in, s->st[0], INIROW , INICOL , 2);
		sleep(SLEEPTIME);
	}else{
		f = fopen(CLUEPATH, "r");
		if(f == NULL){
			return -1;
		}else{
			/*AQUI ASUMO QUE LA PRIMERA CLUE ES LA DEL LEVEL 0, NO 1*/
			for(i = 0; i < level; i++)
				fscanf(f, "%*[^|]|\n");
			fscanf(f, "%m[^|]|\n", &clue);
			if(clue == NULL){
				fclose(f);
				return -1;
			}else{
				i_drawStr(in, clue, INIROW , INICOL , 2);
				/*ASUMO QUE JUAN AÑADE A CLUE PRESS ANY KEY TO CONTINUE*/
				c = _read_key();
			}
		}
	}
	fclose(f);
	free(clue);
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
	if(!in) return -1;
	char *pl_sol, *lev_sol;
	int l, nlev;	
	Level *l;
	
	
	/*"Enter the solution" string*/
	i_drawStr(in, s->st[3], INIROW , INICOL , 2);
	
	/* Meto en solution la solucion del jugador... ¿habra que quitar el \n*/
	/*  Save in pl_sol*/
	
	
	
	/*Se puede resolver sin tener todos los objetos?*/
	nlev = world_getPllevel(w);
	if(nlev < 0) return -1;
	/*Get the pointer associated to that level number*/
	/* l = getLevel(nlev);
	   + control de errores */
	
	if( strcmp(pl_sol, l->solution) == 0 ){
		/*You passed level string*/
		i_drawStr(in, s->st[4], INIROW , INICOL , 2);
		sleep(SLEEPTIME);
		return 0;
	}else{
		/*Youre wrong string*/
		i_drawStr(in, s->st[5], INIROW , INICOL , 2);
		sleep(SLEEPTIME);
		return 0;
	}	
}


int game_f(World *w, int n){
	assert(w && n>-1 && n<3);
	String *s = string_ini(STRPATH);
	
	/*Clean evrything before calling the proper function*/
	i_cleanDisplay(world_getInterface(w));
	i_cleanCommand(world_getInterface(w));
	i_cleanMap(world_getInterface(w));
	
	if(s == NULL)
		return -1;
	
	if(n == 0){
		/*Volver al estado anterior?*/
		return game_help(w, s);
	}else if(n == 1){
		/*Volver al estado anterior?*/
		return game_save(w, s);
	}else if(n == 2){
		/*Volver al estado anterior?*/
		return game_solve(w, s);
	}
}



