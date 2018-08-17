#include <stdlib.h>
#include "item.h"
#include "arvore_busca.h"

struct no{

	ITEM *item;
	struct no *filhoEsq;
	struct no *filhoDir;

};

struct arv{
	
	NO *raiz;

};

ARV *criar_arvore(){

	ARV *arv = (ARV*) malloc(sizeof(ARV));

	if(arv != NULL){
		arv->raiz = NULL;
	}

	return arv;
}

NO *criar_raiz(ARV *arv, ITEM *item){

	arv->raiz = (NO*) malloc(sizeof(NO));

	if(arv->raiz != NULL){
		arv->raiz->filhoDir = NULL;
		arv->raiz->filhoEsq = NULL;
		arv->raiz->item = item;
	}

	return arv->raiz;
}


void apagar_arvore_aux(NO *raiz){
	
	if(raiz != NULL){
		apagar_arvore_aux(raiz->filhoEsq);
		apagar_arvore_aux(raiz->filhoDir);
		apagar_item(&(raiz->item));
		free(raiz);
	}
}

void apagar_arvore(ARV **arv){
	apagar_arvore_aux((*arv)->raiz);
	free(*arv);
}

int vazia(ARV *arv){
	return arv->raiz == NULL;
}

NO *inserir_filho(int filho, NO *no, ITEM *item){

	NO *pnovo = (NO*) malloc(sizeof(NO));

	if(pnovo != NULL){
		pnovo->filhoDir = NULL;
		pnovo->filhoEsq = NULL;
		pnovo->item = item;

		if(filho == FILHO_ESQ){
			no->filhoEsq = pnovo;
		}
		else{
			no->filhoDir = pnovo;
		}
	}
	return pnovo;
}

void imprimir_emordem_aux(NO *no){
	
	if(no != NULL){
		imprimir_emordem_aux(no->filhoEsq);
		imprimir_item(no->item);
		imprimir_emordem_aux(no->filhoDir);
	}
}

void imprimir_emordem(ARV *arv){
	imprimir_emordem_aux(arv->raiz);
}

int altura_arvore_aux(NO *no){
	
	if(no == NULL) return -1;
	int esq = altura_arvore_aux(no->filhoEsq);
	int dir = altura_arvore_aux(no->filhoDir);
	return (esq > dir ? esq : dir) + 1;
}

int altura_arvore(ARV *arv){
	return altura_arvore_aux(arv->raiz);
}

int inserir_abb_aux(NO *raiz, ITEM *item){

	
	if(raiz->item->chave > item->chave){
		if(raiz->filhoEsq != NULL){
			return inserir_abb_aux(raiz->filhoEsq,item); 	
		}
		else{
			return (inserir_filho(FILHO_ESQ,raiz,item) != NULL);
		}
	}
	else if(raiz->item->chave < item->chave){
		if(raiz->filhoDir != NULL){
			return inserir_abb_aux(raiz->filhoDir,item);
		}
		else{
			return (inserir_filho(FILHO_DIR,raiz,item) != NULL);
		}
	}
	else {
		return 0;
	}
}

int inserir_abb(ARV *arv, ITEM *item){

	if(vazia(arv)){
		return (criar_raiz(arv,item) != NULL);
	}
	else{
		return inserir_abb_aux(arv->raiz,item);
	}
}

ITEM *busca_abb_aux(NO *no, int chave){
	
	if(no == NULL) {
		return NULL;
	}
	else if(no->item->chave == chave){
		return no->item;
	}
	else if(no->item->chave > chave){
		return busca_abb_aux(no->filhoEsq,chave);
	}
	else if(no->item->chave < chave){
		return busca_abb_aux(no->filhoDir,chave);
	}
}

ITEM *busca_abb(ARV *arv, int chave){
	return busca_abb_aux(arv->raiz,chave);
}

void troca_max_esq(NO *ptroca, NO *prem, NO *pant){

	if(ptroca->filhoDir != NULL){
		troca_max_esq(ptroca->filhoDir,prem,ptroca);
	}
	if(prem == pant) pant->filhoEsq = ptroca->filhoEsq;
	else pant->filhoDir = ptroca->filhoEsq;

	apagar_item(&(prem->item));
	prem->item = ptroca->item;
	free(ptroca);
}

int remove_abb_aux(ARV *arv, NO *prem, NO *pant, int chave){
		
	if(prem == NULL){
		return 0;
	}
	else if(prem->item->chave > chave){
		return remove_abb_aux(arv,prem->filhoEsq,prem,chave);
	}
	else if(prem->item->chave < chave){
		return remove_abb_aux(arv,prem->filhoDir,prem,chave);
	}
	else if(prem->item->chave == chave){
		if(prem->filhoDir == NULL || prem->filhoEsq == NULL){
			NO *pprox = (prem->filhoEsq == NULL) ? prem->filhoDir : prem->filhoEsq;
			
			if(pant == NULL) arv->raiz = pprox;
			else if(prem == pant->filhoEsq) pant->filhoEsq = pprox;
			else pant->filhoDir = pprox;

			apagar_item(&(prem->item));
			free(prem);
		}
		else{
			troca_max_esq(prem->filhoEsq,prem,prem);
		}
		return 1;
	}
}

int remove_abb(ARV *arv, int chave){
	return remove_abb_aux(arv,arv->raiz,NULL,chave);
}
