#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

int main(int argc, char** argv) {
	
	//Criação da árvore
	ARVORE_BINARIA *arv = criar_arvore();
	
	//Criação da raíz
	NO *raiz = criar_raiz(arv, criar_item(1, 1));
	
	//Inserção dos filhos
	NO *no1 = inserir_filho(FILHO_ESQ,raiz,criar_item(2,2));
	NO *no2 = inserir_filho(FILHO_DIR,raiz,criar_item(3,3));	
	NO *no3 = inserir_filho(FILHO_ESQ,no1,criar_item(4,4));	
	NO *no4 = inserir_filho(FILHO_DIR,no3,criar_item(5,5));	
	NO *no5 = inserir_filho(FILHO_ESQ,no2,criar_item(6,6));	
	NO *no6 = inserir_filho(FILHO_DIR,no2,criar_item(7,7));	
	NO *no7 = inserir_filho(FILHO_ESQ,no5,criar_item(8,8));	
	NO *no8 = inserir_filho(FILHO_DIR,no5,criar_item(9,9));	
	
	//Impressão dos nós
//	imprimir_emordem(arv);
//	imprimir_preordem(arv);
	imprimir_posordem(arv);
	
	//Altura da árvore
	printf("Altura da árvore: %d\n",(altura_arvore(arv)));
	
	//Apagando a árvore
	apagar_arvore(&arv);	

	return 0;
}
