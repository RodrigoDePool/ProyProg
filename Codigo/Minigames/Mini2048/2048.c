
#include "2048.c"
#define NDEBUG
#include <assert.h>

struct _Numbers{
	int *n;
	char **files;
	int size;
}



int **matrix_rotateleft(int **matrix, int size){
	assert (size > 0 && matrix !=NULL);
	
	int aux[size][size];
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			aux[j, i] = matrix[i, size-1 - j];
		}
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			matrix[j, i] = aux[j, i];
		}
	}
	return matrix;
}

int **matrix_rotateright(int **matrix, int size){
	assert (size > 0 && matrix !=NULL);
	
	int aux[size][size];
	int i, j;
	
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			aux[j, i] = matrix[size-1 -i, j];
		}
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			matrix[j, i] = aux[j, i];
		}
	}
	return matrix;
}

int **hmove( int** matrix, int dir, int size, int *score){
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
			
				if(matrix[j - dir, i] == 0){
					matrix[j - dir, i] = matrix[j, i];
					matrix[j, i] = 0;
					if (matrix[j - dir, i] != 0) ch++;
					
				}else if (matrix[j - dir, i] == matrix [j,i] &&
					  upd[j - dir, i] == 0 && upd[j, i] == 0){
					    
					    	/*We only add up two cells if none of them have 
					    	already been "twiced" in this movement 
					    	(2240+lft = 4400, not 8000):we use the upd matrix */
					    	matrix[j - dir, i] == 2 * matrix[j, i];
					    	matrix[j, i] = 0;
					    	upd[j - dir, i] = 1;
					    	(*score) += matrix[j - dir, i];
					    	ch ++;					    	
					    }
				
			}/*End third loop*/
		} /*End second loop*/
		/*Finished exploring the whole matrix one time*/
	} /*End first loop*/
	
	matrix = prepares_for_next(matrix, size);
	
	return matrix;
	
}

int **vmove( int** matrix, int dir, int size, int *score){
	
	matrix = matrix_rotate_left(matrix, size);
	matrix = hmovevmove(matrix, dir, size, score);
	matrix = matrix_rotate_right(matrix, size);
	return matrix;
	
}

int ** prepares_for_next(int **matrix, int size){
	assert(matrix && size>0);
	
	int i, j, finished, rnd;
	
	finished = 1;
	/*if theres a 0 or two cells that can be added up, game not finished (= 0)*/
	for(i = 0; i < size && finished = 1; i++){
		for(j = 0; j < size && finished = 1; j++){
			if (matrix[j, i] == 0) finished = 0;
		}
	}
	for(i = 0; i < size && finished = 1; i++){
		for(j = 1; j < size && finished = 1; j++){
			if(matrix[j-1, i] == matrix[j, i]) finished = 0;
		}
	}
	for(i = 0; i < size && finished = 1; i++){
		for(j = 1; j < size && finished = 1; j++){
			if(matrix[i, j-1] == matrix[i, j]) finished = 0;
		}
	}
	
	
	/*New 2/4 to the matrix if anything has changed (ch != 0) and not finished*/
	if(finished == 1){
		/*Llamada a otra funcion ¿?*/
	}else if(ch != 0){
		rnd = rand() % 10;
		if (rnd == 0) rnd = 4;
		else rnd = 2;
		
		do{
			i = rand() % 4;
			j = rand() % 4;
		}while (matrix[j, i] != 0)
		
		matrix[j, i]) = rnd; 
	}
	return matrix;
}

int draw_matrix(interface *i, int **matrix, Numbers *num){
	assert(i && matrix && num);
	
	int i, j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < i; j++){
			i_readFile(i, Numbers_getFile(matrix[j, i]), 4 + i*7, 17 + j*18, 1);
		}
	}
	return 0;

}

Numbers *Numbers_ini(char *file){
	int size, i;
	char *name;
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
	
	fclose(f);
	return num;	
}

void Numbers_free(Numbers *num){
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





