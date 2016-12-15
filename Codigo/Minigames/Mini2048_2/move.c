
/*Right: +1 
Left: -1
*/

int hdispl[4] = {-1, 1, 0, 0};
int vdispl[4] = {0, 0, -1, 1};

a ? b:c



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
			
//			inew = (inew > 0) ? ((inew<size) ? inew : size-1) : 0;
		
		
		
		
		} /*End second loop*/
	} /*End first loop*/
	
}
