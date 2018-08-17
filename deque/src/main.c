#include "item.h"
#include "deque.h"

#include <stdio.h>

#define n 5

int main(int argc, char *argv[]){
	
	int i;
	DEQUE *deque = criar_deque();

	for(i=0;i<n;i++){
		inserir_fim(deque,criar_item(i,i));
	}
		
	imprimir_deque(deque);

	for(i=n;i<2*n;i++){
		inserir_inicio(deque,criar_item(i,i));
	}


	imprimir_deque(deque);

	remover_inicio(deque);
	remover_fim(deque);
	
	apagar_deque(&deque);

	return 0;
}
