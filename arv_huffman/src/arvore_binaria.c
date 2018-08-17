#include "arvore_binaria.h"

#include <stdlib.h>
#include <stdio.h>

ARV *criar_arvore(){
	
	ARV *arv = (ARV*) malloc(sizeof(ARV));

	if(arv != NULL){
		arv->raiz = NULL;
	}
	return arv;
}

NO *criar_raiz(ARV *arv, NO* no){
	
	arv->raiz = no;	
	
	return arv->raiz;
}

int vazia_arvore(ARV *arv){
	return arv->raiz == NULL;
}

void apagar_arvore_aux(NO *no){
	
	if(no != NULL){
		apagar_arvore_aux(no->filhoEsq);
		apagar_arvore_aux(no->filhoDir);
		free(no);
	}
}

void apagar_arvore(ARV **arv){
	
	apagar_arvore_aux((*arv)->raiz);
	free(*arv);
	
}
