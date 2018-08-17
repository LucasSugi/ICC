#include "item.h"
#include "lista_ligada.h"
#include <stdio.h>

int main(int argc, char *argv[]){

	int i;

	LISTA_LIGADA *lista = criar_lista();

	for(i=0;i<50;i++){
		inserir_item(lista, criar_item(i,i));
	}

	imprimir(lista);
	printf("\n");
	
	for(i=0;i<40;i++){
		remover_item(lista, i);
	}

	imprimir(lista);
	printf("\n");
	
	for(i=40;i<50;i++){
		imprimir_item(recuperar_item(lista,i));
	}
	
	apagar_lista(&lista);

	return 0;
}
