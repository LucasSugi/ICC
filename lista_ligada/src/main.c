#include "item.h"
#include "lista_ligada.h"
#include <stdio.h>

int main(int argc, char *argv[]){

	int i;

	LISTA_LIGADA *lista = criar_lista();

	for(i=0;i<50;i++){
		inserir_item(lista, criar_item(i,i));
	}

	printf("Tamanho da lista : %d\n",tamanho(lista));

	for(i=0;i<10;i++){
		remover_item(lista,i);
	}

	printf("Tamanho da lista : %d\n",tamanho(lista));

	imprimir(lista);
	
	apagar_lista(&lista);

	return 0;
}
