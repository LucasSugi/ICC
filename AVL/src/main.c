#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "item.h"

int main(){
	
	ARVORE *arv = criar_arvore();
	
	inserir_arvore(arv,criar_item(7,7));
	inserir_arvore(arv,criar_item(5,5));
	inserir_arvore(arv,criar_item(8,8));
	inserir_arvore(arv,criar_item(4,4));
	inserir_arvore(arv,criar_item(6,6));
	inserir_arvore(arv,criar_item(2,2));
	
	apagar_arvore(&arv);

	return 0;
}
