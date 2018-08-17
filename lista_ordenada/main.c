#include "lista_estatica.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
	int i;
	LISTA_ESTATICA *lista = criar_lista();

	for(i=0; i < 50; i++) {
		inserir(lista, criar_item(50-i,50-i));
	}

	printf("tamanho: %d\n", tamanho(lista));

	for(i=0; i < 10; i++) {
		remover(lista);
	}

	printf("tamanho %d\n", tamanho(lista));

	imprimir_lista(lista);

	apagar_lista(&lista);

	return 0;
}
