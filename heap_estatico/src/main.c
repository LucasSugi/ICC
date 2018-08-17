#include <stdio.h>
#include <stdlib.h>

#include "heap_estatica.h"
#include "item.h"

int main(int argc, char *argv[]){

	HEAP_ESTATICA *heap = criar_heap();
	ITEM *aux = NULL;
	int i;

	for(i=0;i<7;i++){
		enfileirar(heap,criar_item(i,i));
	}

	aux = desenfileirar(heap);
	apagar_item(&aux);

	imprimir_heap(heap);

	apagar_heap(&heap);

	return 0;
}
