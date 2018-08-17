#include "lista_estatica.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>

int main(){

	int i;
	ITEM *item;
	LISTA_ESTATICA *lista = criar_lista();

	for(i=0; i < 20; i++){
		inserir_fim(lista, criar_item(i,i));
	}
	
	imprimir_lista(lista);

	for(i=0; i < 5; i++){
		remover_fim(lista);
	}

	imprimir_lista(lista);

	item = recuperar_chave(lista,20);	
	imprimir_item(item);

	apagar_lista(&lista);

	return 0;
}
