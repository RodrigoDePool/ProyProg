#include <stdio.h>
#include <stdlib.h>

char ** mapfromfile(FILE * f, int nrows, int ncols);
int main(){
	char **a,b;
	int rows, cols,i,j;
	FILE *f=fopen("mapa1.txt","r");
	
	fscanf(f,"%d %d\n",&rows,&cols);
	a=mapfromfile(f,rows,cols);
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			printf("%c",a[i][j]);
		}
		printf("\n");
	}
	
	fclose(f);

	for(i=0;i<rows;i++){
		free(a[i]);
	}
	free(a);
	return 1;


}


char ** mapfromfile(FILE * f, int nrows, int ncols){
	
	char **map;
	int i,j;
	map=(char **)malloc(sizeof(char *)*nrows);
	if(map==NULL) return NULL;
	for(i=0;i<nrows;i++){
		map[i]=(char *)malloc(sizeof(char)*(ncols+1));
		if(map[i]==NULL){/*lack of memory*/		
			for(j=i-1;j>=0;j--){
				free(map[j]);
			}
			free(map);
			return NULL;
		}
	}
	
	for(i=0;i<nrows;i++){
		fgets(map[i],ncols+1,f);
		fscanf(f,"\n");		
	}

	return map;
}

