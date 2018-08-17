#include "item.h"
#include "pilha_estatica.h"

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

	for(i=0;i<3;i++){
		desempilhar(pilha);
	}
	imprimir(pilha);
	printf("\n");

	imprimir_item(topo(pilha));
	printf("\n");
	
	printf("%d\n",tamanho(pilha));

	apagar_pilha(&pilha);

	return 0;
}
