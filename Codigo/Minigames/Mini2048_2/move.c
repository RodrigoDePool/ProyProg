
/*Right: +1 
Left: -1
*/

int hdispl[4] = {-1, 1, 0, 0};
int vdispl[4] = {0, 0, -1, 1};



int **hmove( int** matrix, int direction, int size){
	int i, j, k;
	/*ch will tell me if, after moving in one direction, the matrix has
	has changed (just to know if I have to generate a new 2/4)*/
	int ch = 0;
	
	
	/*First loop: 
	To avoid 4004 + pressleft = 4040, bc we want
		 4004 + pressleft = 8000*/
	for(k = 0; k < size-1; k++){
		/*Second and third loop:
		Explore the matrix to see "what would happen" with each [i, j]*/		
		for(i = 0; i < tam; i++){
			for(j = size-2; j >=0; j++){
				if(matrix[j+1, i] == 0){
					matrix[j+1, i] = matrix[j, i];
					matrix[j, i] = 0;
					if (matrix[j+1, i] != 0) ch++;
				}else{
					
					
				}
			}/*End third loop*/
		} /*End second loop*/
	} /*End first loop*/
}





















int move(int **matrix, int direction, int size){
	int i, j, k;
	
	/*First loop: 
	To avoid 4004 + pressleft = 4040, bc we want
		 4004 + pressleft = 8000*/
	for(k = 0; k < tam-1; k++){
		/*Second loop:
		To see "what would happen" with each [i, j]
		Would it change? Then, would it duplicate or be a zero?*/		
		for(i = 0; i < tam; i++){
			inew = i+vdispl[direction];
			if (inew < 0)
				inew = 0;
			else if inew >= size
				inew = size-1;
			/*inew = (inew > 0) ? ((inew<size) ? inew : size-1) : 0;*/
			
		
		
		
		} /*End second loop*/
	} /*End first loop*/
	
}
