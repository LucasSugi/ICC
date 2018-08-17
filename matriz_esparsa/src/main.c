#include "matriz_esparsa.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	int i;	
	MATRIZ_ESPARSA *mat = criar_matriz(5,5);

/*	set(mat,0,0,1);
	set(mat,2,1,7);
	set(mat,2,4,11);
	set(mat,2,2,31);
	set(mat,1,3,69);

	printf("%.1lf\n\n",get(mat,3,1));
	printf("%.1lf\n\n",get(mat,1,3));

	imprimir_matriz(mat);*/

	apagar_matriz(&mat);

	return 0;
}
