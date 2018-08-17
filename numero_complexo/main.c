#include <stdio.h>
#include "complexo.h"

int main(){

	N_COMPLEXO *n1 = NULL;
	N_COMPLEXO *n2 = NULL;
	N_COMPLEXO *n3 = NULL;
	N_COMPLEXO *n4 = NULL;

	n1 = criar(1,2);
	n2 = criar(3,1);

	n3 = adicao(n1,n2);
	imprimir(n3);

	n4 = multiplicar(n1,n2);
	imprimir(n4);

	destruir(n1);
	destruir(n2);
	destruir(n3);
	destruir(n4);

	return 0;
}
