
#define NDEBUG
#include <assert.h>
#include "string.h"
#define STRPATH "ProyProg/Codigo/DATA/game/string.txt"

struct _String{
	int nums;
	char **st;	
};


/**********************************************/
/****   PUBLIC FUNCTIONS IMPLEMENTATION   *****/
/**********************************************/

String *string_ini(char *path){
	int i;
	FILE *f = fopen(path, "r");
	if(f == NULL)
		return NULL;
	
	String *s = (String *)malloc(sizeof(String));
	if(s == NULL){
		fclose(f);
		return NULL;
	}
	
	s->nums = -1;
	fscanf(f, "%d\n", &(s->nums));
	s->st =(char **)malloc(s->nums * sizeof(char *));
	if(s->st == NULL){
		string_free(s);
		fclose(f);
		return NULL;
	}
	
	for(i = 0;i < s->nums; i++){
		fscanf(f, "%m[^#]#\n\n", (s->st)+i);
		
		if( s->st[i] == NULL ){
			string_free(s);
			fclose(f);
			return NULL;			
		}
	}
	
	fclose(f);
	return s;
}

void string_free(String *s){
	int i;
	if(s){
		if(s->st){
			for(i = 0; i < s->nums; i++){
				if(s->st[i])
					free(s->st[i]);
			}
			free(s->st);
		}
		free(s);
	}
}

int string_getNumber(String *s){
	assert(s);
	return s->nums;
}

char * string_getString(String *s, int i){
	assert(s && i >= 0);
	return s->st[i];
}

int string_drawLines(Interface *in, char *s, int row, int col, int bdc, char sep, char finish){
	assert(in && s);
		
	/*Theyll tell me the beginning and the end of each line of the string*/
	char *ini = s, *end = s;
	
	/*look for the end of first line, replace it with a \0, print
	on interface, return the end of line char with its original value,
	continueswith nex line*/
	
	
	do{
		while(*end != sep && *end != finish){
			end ++;
		}
		if(*end == finish){
			*end = 0;
			i_drawStr(in, ini, row++, col, bdc);
			/*printf("%s\n", ini);*/
			*end = finish;
		}else{
			*end = 0;
			i_drawStr(in, ini, row++, col, bdc);
			/*printf("%s\n", ini);*/		
			*end = sep;
			end ++;
			ini = end;
		}
	}while(finish != *end);
	
	return row;
}
