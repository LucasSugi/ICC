#include "item.h"
#include "pilha_dinamica.h"

#include <stdio.h>
#define n 10

int main(int argc, char *argv[]){
	
	int i;
	PILHA *pilha = criar_pilha();
	
	for(i=0;i<n;i++){
		empilhar(pilha,criar_item(i,i));
	}

	imprimir(pilha);	
	printf("\n");

	for(i=0;i<n/2;i++){
		desempilhar(pilha);
	}

	imprimir(pilha);
	printf("\n");

	for(i=n;i<n+5;i++){
		empilhar(pilha,criar_item(i,i));
	}

	imprimir_item(topo(pilha));
	printf("\n");

	imprimir(pilha);

	apagar_pilha(&pilha);


	return 0;
}
