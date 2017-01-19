
#include "2048.h"
#define NDEBUG
#include <assert.h>
#include <unistd.h>
#define NUMBERSPATH "./Codigo/DATA/miniInst/2048/numbers.txt"
#define BOARDPATH3 "./Codigo/DATA/miniInst/2048/board2048_3.txt"
#define BOARDPATH4 "./Codigo/DATA/miniInst/2048/board2048_4.txt"
#define INSTPATH "Codigo/DATA/miniInst/2048/instructions.txt"

int asprintf(char **strp, const char *fmt, ...);

struct _Numbers{
	int *n;
	char **files;
	int size;
};




int **matrix_rotateleft(int **matrix, int size){
	assert (size > 0 && matrix !=NULL);
	
	int i, j, newi, newj;
	int **aux = (int **)malloc(size * sizeof(int *));
	if(!aux) return NULL;
	for(i = 0; i < size; i++){
		aux[i] = (int *)malloc(size * sizeof(int));
		if(!aux[i]){
			for(j = 0; j < 1; j++) free(aux[j]);
			free(aux);
			return NULL;
		}
	}
	
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			newj = i;
			newi = size-1 - j;
			aux[j][i] = matrix[newj][newi];
		}
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			matrix[j][i] = aux[j][i];
		}
	}
	
	for(i = 0; i < size; i++)
		free(aux[i]);
	free(aux);
	return matrix;
}

int **matrix_rotateright(int **matrix, int size){
	assert (size > 0 && matrix !=NULL);
	
	int i, j, newi, newj;
	int **aux = (int **)malloc(size * sizeof(int *));
	if(!aux) return NULL;
	for(i = 0; i < size; i++){
		aux[i] = (int *)malloc(size * sizeof(int));
		if(!aux[i]){
			for(j = 0; j < 1; j++) free(aux[j]);
			free(aux);
			return NULL;
		}
	}
	
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			newj = size-1 - i;
			newi = j;
			aux[j][i] = matrix[newj][newi];
		}
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			matrix[j][i] = aux[j][i];
		}
	}
	for(i = 0; i < size; i++)
		free(aux[i]);
	free(aux);
	return matrix;
}

int **hmove(int** matrix, int dir, int size, int *score, int *finished, int*won, int max){
	assert (size > 0 && matrix !=NULL && score != NULL && (dir == 1 || dir == -1));
	
	int i, j, k, init, ch = 0;
	/*ch will tell me if, after moving in one direction, the matrix has
	has changed (just to know if I have to generate a new 2/4)*/
		
	/*This matrix will tell for each cell if its value has already changed in
	this movement. Initially 0 (cells not changed) */
	int upd[size][size];
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			upd[i][j] = 0;
		}
	}
			
	/*First loop: 
	To avoid 4004 + pressleft = 4040, bc we want
		 4004 + pressleft = 8000*/
	for(k = 0; k < size-1; k++){
	
		/*Second and third loop:
		Explore the matrix to see what happens with each [j, i]*/		
		for(i = 0; i < size; i++){
			init = (size + (2 * dir))%(size+1);
			for(j = init; j >= 0 && j < size; j += dir){
			
				if(matrix[j - dir][i] == 0){
					matrix[j - dir][i] = matrix[j][i];
					matrix[j][i] = 0;
					if (matrix[j - dir][i] != 0) ch++;
					
				}else if (matrix[j - dir][i] == matrix [j][i] &&
					  upd[j - dir][i] == 0 && upd[j][i] == 0){
					    
					    	/*We only add up two cells if none of them have 
					    	already been "twiced" in this movement 
					    	(2240+lft = 4400, not 8000):we use the upd matrix */
					    	matrix[j - dir][i] = 2 * matrix[j][i];
					    	if(matrix[j - dir][i] == max)
					    		*won = 1;
					    	matrix[j][i] = 0;
					    	upd[j - dir][i] = 1;
					    	(*score) += matrix[j - dir][i];
					    	ch ++;					    	
					    }
				
			}/*End third loop*/
		} /*End second loop*/
		/*Finished exploring the whole matrix one time*/
	} /*End first loop*/
	
	matrix = prepares_for_next(matrix, size, finished, ch);
	
	return matrix;
	
}

int **vmove(int** matrix, int dir, int size, int *score, int *finished, int*won, int max){
	
	matrix = matrix_rotateleft(matrix, size);
	matrix = hmove(matrix, dir, size, score, finished, won, max);
	matrix = matrix_rotateright(matrix, size);
	return matrix;
	
}

int ** prepares_for_next(int **matrix, int size, int *finished, int ch){
	assert(matrix && size>0);
	
	int i, j, rnd;
	
	*finished = 1;
	/*if theres a 0 or two cells that can be added up, game not finished (= 0)*/
	for(i = 0; i < size && *finished == 1; i++){
		for(j = 0; j < size && *finished == 1; j++){
			if (matrix[j][i] == 0) *finished = 0;
		}
	}
	for(i = 0; i < size && *finished == 1; i++){
		for(j = 1; j < size && *finished == 1; j++){
			if(matrix[j-1][i] == matrix[j][i]) *finished = 0;
		}
	}
	for(i = 0; i < size && *finished == 1; i++){
		for(j = 1; j < size && *finished == 1; j++){
			if(matrix[i][j-1] == matrix[i][j]) *finished = 0;
		}
	}
	
	
	/*New 2/4 to the matrix if anything has changed (ch != 0) and not finished*/
	if(*finished == 1){
		return matrix;
	}else if(ch != 0){
		rnd = rand() % 10;
		if (rnd == 0) rnd = 4;
		else rnd = 2;
		
		do{
			i = rand() % size;
			j = rand() % size;
		}while (matrix[j][i] != 0);
		
		matrix[j][i] = rnd; 
	}
	return matrix;
}

int draw_matrix(Interface *i, int **matrix, Numbers *num, int size, int score){
	assert(i && matrix && num);
	
	int k, j;
	char *sc;
	for(k = 0; k < size; k++){
		for(j = 0; j < size; j++){
			i_readFile(i, Numbers_getFile(matrix[j][k], num), 4+ k*7 ,17 + j*18, 1);
		}
	}
	/*draw the score on the display*/
	asprintf(&sc, "%d", score);
	i_drawStr(i, sc, 4, 2, 2);
	free(sc);
	return 0;

}


int mini2048_small(Interface *in){
	return mini2048(in, 3, 32);
}


int mini2048_big(Interface *in){
	return mini2048(in, 4, 2048);
}

int mini2048(Interface *in, int size, int max){

	assert(in && size > 1 && max > 2);
	int i, j, rnd, score = 0, finished = 0, won = 0;
	Numbers *num;
	char c;
	int **matrix = (int **)malloc(size * sizeof(int *));
	if(matrix == NULL) return -1;
	for(i = 0; i < size; i++){
		matrix[i] = (int *)malloc(size * sizeof(int));
		if(!matrix[i]){
			for(j = 0; j < 1; j++) free(matrix[j]);
			free(matrix);
			return -1;
		}
	}
	
	/*Print instructions*/
	i_cleanDisplay(in);
	i_cleanCommand(in);
	i_cleanMap(in);
	i_readFile(in, INSTPATH , 1, 1, 2);
	
	
	num = Numbers_ini(NUMBERSPATH);
	if(!num) return -1;
	/*Initializes matrix an adds first number*/
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			matrix[i][j] = 0;
		}
	}
	rnd = rand() % 10;
	if (rnd == 0) rnd = 4;
	else rnd = 2;
	i = rand() % size;
	j = rand() % size;
	matrix[j][i] = rnd; 	
	
	if(size == 4){
  		i_readFile(in, BOARDPATH4, 0, 0, 1);
	}else if(size == 3){
		i_readFile(in, BOARDPATH3, 0, 0, 1);
	}
	
	draw_matrix(in, matrix, num, size, score);
	i_drawStr(in, "Your score: ",  3, 2, 2);
	
	/*main loop*/
	while(finished == 0 && won == 0){
		/*read key*/
		c = _read_key();
		if (c == 'q' || c == 'Q'){
			sleep(2);
			Numbers_free(num);
			return 0;
		}
		/*call movement*/
		if(c == EAST){
			hmove(matrix, -1, size, &score, &finished, &won, max);
		}else  if (c == WEST){
			hmove(matrix, +1, size, &score, &finished, &won, max);
		}else if (c == SOUTH){
			vmove(matrix, +1, size, &score, &finished, &won, max);
		}else if (c == NORTH){
			vmove(matrix, -1, size, &score, &finished, &won, max);
		}
		/*draw things*/
		draw_matrix(in, matrix, num, size, score);
	
	}
	/*finished game, won or not?*/
	if(won == 1){
		i_drawStr(in, "YOU WON!",  5, 4, 2);
	}else{
		i_drawStr(in, "YOU LOST!", 5, 4, 2);
	}
	sleep(2);
	for(i = 0; i < size; i++)
		free(matrix[i]);
	free(matrix);
	Numbers_free(num);
	i_cleanDisplay(in);
	i_cleanCommand(in);
	i_cleanMap(in);
	return won;
}



Numbers *Numbers_ini(char *file){
	int size, i;
	Numbers *num = NULL;
	FILE *f;
	f = fopen(file, "r");
	fscanf(f, "%d\n", &size);
	num = (Numbers *)malloc(sizeof(Numbers));
	num->size = size;
	if(!num){
		fclose(f);
		return NULL;
	}
	num->n = (int *)malloc(size * sizeof(int));
	if(!num->n){
		free(num);
		fclose(f);
		return NULL;
	}
	num->files = (char **)malloc(size * sizeof(char *));
	if(!num->files){
		free(num->n);
		free(num);
		fclose(f);
		return NULL;
	}
	for(i = 0; i < size; i++){
		fscanf(f, "%d\n", &num->n[i]);
		fscanf(f, "%m[^\n]\n", &num->files[i]);
	}
	
	fclose(f);
	return num;	
}

void Numbers_free(Numbers *num){
	int i;
	if(num){
		if(num->n) free(num->n);
		if(num->files){
			for(i = 0; i < num->size; i++){
				if(num->files[i]) free(num->files[i]);
			}
			free(num->files);
		}
		free(num);
	}
}

char *Numbers_getFile(int m, Numbers* num){
	assert(num != NULL);
	
	int i;
	for(i = 0; i < num->size; i++){
		if(num->n[i] == m)
			return num->files[i];
	}
	return NULL;	
}






