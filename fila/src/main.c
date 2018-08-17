#include <stdio.h>
#include <stdlib.h>

#include "fila_estatica.h"

int main(int argc, char *argv[]){
	
	int i;
	FILA_ESTATICA *fila = criar_fila();
	
	for(i=0;i<8;i++){
		enfileirar(fila,criar_item(i,i));
	}
	
	imprimir_fila(fila);

	desenfileirar(fila);
	desenfileirar(fila);
	desenfileirar(fila);
	desenfileirar(fila);

	imprimir_fila(fila);
	
	for(i=8;i<12;i++){
		enfileirar(fila,criar_item(i,i));
	}

	imprimir_fila(fila);

	apagar_fila(&fila);

	return 0;
}
