#include <stdio.h>
#include <stdlib.h>
#include "arvore_busca.h"

int main(int argc, char** argv) {

	ARV *arv = criar_arvore();

	inserir_abb(arv, criar_item(17, 1));
  	inserir_abb(arv, criar_item(99, 2));
	inserir_abb(arv, criar_item(13, 3));
	inserir_abb(arv, criar_item(1, 4));
	inserir_abb(arv, criar_item(3, 5));
	inserir_abb(arv, criar_item(100, 6));
	inserir_abb(arv, criar_item(400, 7));

	imprimir_emordem(arv);

	printf("altura: %d\n", altura_arvore(arv));
  
//	imprimir_item(busca_abb(arv, 400));
   
	remove_abb(arv, 17);
	remove_abb(arv, 1);
	remove_abb(arv, 3);
	remove_abb(arv, 400);
	remove_abb(arv, 100);
	remove_abb(arv, 13);
	remove_abb(arv, 99);
	  
	printf("altura: %d\n", altura_arvore(arv));
	
	imprimir_emordem(arv);

	apagar_arvore(&arv);

  return 0;
}
