#include <stdio.h>
#include <stdlib.h>
#include "complexo.h"

N_COMPLEXO *criar(int r, int i){

	N_COMPLEXO *n = NULL;

	n = (N_COMPLEXO*) malloc(sizeof(N_COMPLEXO));

	n[0].real = r;
	n[0].imaginario = i;

	return n;
}

void destruir(N_COMPLEXO *n){

	free(n);
}

N_COMPLEXO *adicao(N_COMPLEXO *n1, N_COMPLEXO *n2){

	N_COMPLEXO *n3 = NULL;
	
	n3 = criar(0,0);
	
	n3[0].real = n1[0].real + n2[0].real;
	n3[0].imaginario = n1[0].imaginario + n2[0].imaginario;

	return n3;
}


N_COMPLEXO *multiplicar(N_COMPLEXO *n1, N_COMPLEXO *n2){

	N_COMPLEXO *n4 = NULL;

	n4 = criar(0,0);
	
	n4[0].real = n1[0].real * n2[0].real - (n1[0].imaginario * n2[0].imaginario);
	n4[0].imaginario = n1[0].real * n2[0].imaginario + n1[0].imaginario * n2[0].real;

	return n4;
}

void imprimir(N_COMPLEXO *n){

	if(n[0].imaginario > 0){
		printf("Número complexo resultante: %d + %di\n",n[0].real,n[0].imaginario);
	} else{
		printf("Número complexo resultante: %d - %di\n",n[0].real,n[0].imaginario);
	}
}

