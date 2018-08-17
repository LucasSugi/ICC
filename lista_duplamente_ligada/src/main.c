#include <stdio.h>
#include <stdlib.h>

#include "lista_duplamente_ligada.h"
#include "item.h"

int main(int argc, char *argv[]){
	
	int i;
	LISTA_DUPLAMENTE_LIGADA *lista = criar_lista();

  	for (i = 0; i < 10; i++) {
		inserir_lista(lista, criar_item(i, i));
  	}
  
  	imprimir_lista(lista);
	printf("\n");
  
  	remover_lista(lista, 0);
  	remover_lista(lista, 2);
  	remover_lista(lista, 5);
  	remover_lista(lista, 4);

	imprimir_lista(lista);
	printf("\n");

	imprimir_item(buscar_lista(lista,9));
	printf("\n");

	for(i=10;i<15;i++){
		inserir_lista(lista,criar_item(i,i));
	}
	inserir_lista(lista,criar_item(2,2));

	imprimir_lista(lista);
  
  	apagar_lista(&lista);

	return 0;
}

