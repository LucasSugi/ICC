#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

struct no{

	ITEM *item;
	NO *filhoEsq;
	NO *filhoDir;
};

struct arvore_binaria{
	NO *raiz;
};

ARVORE_BINARIA *criar_arvore(){

	ARVORE_BINARIA *arv = (ARVORE_BINARIA*) malloc(sizeof(ARVORE_BINARIA));

	if(arv != NULL){
		arv->raiz = NULL;
	}
	return arv;
}

void apagar_arvore_aux(NO *no){
	if(no != NULL){
		apagar_arvore_aux(no->filhoEsq);
		apagar_arvore_aux(no->filhoDir);
		apagar_item(&(no->item));
		free(no);
	}
}

void apagar_arvore(ARVORE_BINARIA **arv){

	if(arv != NULL && *arv != NULL){
		apagar_arvore_aux((*arv)->raiz);
		free(*arv);
	}
}

NO *criar_raiz(ARVORE_BINARIA *arv, ITEM *item){

	if(arv != NULL){
		arv->raiz = (NO*) malloc(sizeof(NO));
		if(arv->raiz != NULL){
			arv->raiz->filhoEsq = NULL;	
			arv->raiz->filhoDir = NULL;
			arv->raiz->item = item;
		}

	}
	return arv->raiz;
}

NO *inserir_filho(int filho,NO *no, ITEM *item){

	NO *pnovo  = (NO*) malloc(sizeof(NO));

	if(pnovo != NULL){	
		pnovo->item = item;
		pnovo->filhoEsq = NULL;
		pnovo->filhoDir = NULL;

		if(filho == FILHO_ESQ){
			no->filhoEsq = pnovo;
		}
		else{
			no->filhoDir = pnovo;
		}
	}
	return pnovo;
}

int vazia(ARVORE_BINARIA *arv){
	return arv->raiz == NULL;
}

void imprimir_emordem_aux(NO *no){
	if(no != NULL){
		imprimir_emordem_aux(no->filhoEsq);
		imprimir_item(no->item);
		imprimir_emordem_aux(no->filhoDir);
	}
}

void imprimir_emordem(ARVORE_BINARIA *arv){
	if(arv != NULL){
		imprimir_emordem_aux(arv->raiz);
	}
}

void imprimir_preordem_aux(NO *no){
	if(no != NULL){
		imprimir_item(no->item);	
		imprimir_preordem_aux(no->filhoEsq);
		imprimir_preordem_aux(no->filhoDir);
	}
}

void imprimir_preordem(ARVORE_BINARIA *arv){
	if(arv != NULL){
		imprimir_preordem_aux(arv->raiz);
	}
}


void imprimir_posordem_aux(NO *no){
	if(no != NULL){
		imprimir_posordem_aux(no->filhoEsq);
		imprimir_posordem_aux(no->filhoDir);		
		imprimir_item(no->item);
	}
}

void imprimir_posordem(ARVORE_BINARIA *arv){
	if(arv != NULL){
		imprimir_posordem_aux(arv->raiz);
	}
}

int altura_arvore_aux(NO *no){
	if(no == NULL) return -1;
	int esq = altura_arvore_aux(no->filhoEsq);
	int dir = altura_arvore_aux(no->filhoDir);
	return (esq>dir) ? esq + 1: dir + 1;
}

int altura_arvore(ARVORE_BINARIA *arv){
	return altura_arvore_aux(arv->raiz);
}
