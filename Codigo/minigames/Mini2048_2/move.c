
/*Right: -1 
Left: +1
Up: +1
Down: -,1
*/

int hdispl[4] = {-1, 1, 0, 0};
int vdispl[4] = {0, 0, -1, 1};



int **hmove( int** matrix, int dir, int size, int *score){
	int i, j, k, init, ch = 0;
	/*ch will tell me if, after moving in one direction, the matrix has
	has changed (just to know if I have to generate a new 2/4)*/
	
	/*To be used at the end of function*/
	int rnd, finished, flag;
	
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
		Explore the matrix to see "what would happen" with each [i, j]*/		
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


int **vmove( int** matrix, int dir, int size, int *score){
	int i, j, k, init, ch = 0;
	/*ch will tell me if, after moving in one direction, the matrix has
	has changed (just to know if I have to generate a new 2/4)*/
	
	/*To be used at the end of function*/
	int rnd, finished, flag;
	
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
		Explore the matrix to see "what would happen" with each [i, j]*/		
		for(i = 0; i < size; i++){
			init = (size + (2 * dir))%(size+1);
			for(j = init; j >= 0 && j < size; j += dir){
			
				if(matrix[i, j - dir] == 0){
					matrix[i, j - dir] = matrix[i, j];
					matrix[i, j] = 0;
					if (matrix[i, j - dir] != 0) ch++;
					
				}else if (matrix[i, j - dir] == matrix [i, j] &&
					  upd[i, j - dir] == 0 && upd[i, j] == 0){
					    
					    	/*We only add up two cells if none of them have 
					    	already been "twiced" in this movement 
					    	(2240+lft = 4400, not 8000):we use the upd matrix */
					    	matrix[i, j - dir] == 2 * matrix[i, j];
					    	matrix[i, j] = 0;
					    	upd[i, j - dir] = 1;
					    	(*score) += matrix[i, j - dir];
					    	ch ++;					    	
					    }
				
			}/*End third loop*/
		} /*End second loop*/
		/*Finished exploring the whole matrix one time*/
	} /*End first loop*/
	
	
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
	
	return 0;
	
}

