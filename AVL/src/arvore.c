#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"
#include "item.h"

ARVORE *criar_arvore(){

	ARVORE *arv = (ARVORE*) malloc(sizeof(ARVORE));

	if(arv != NULL){
		arv->raiz = NULL;
	}
	return arv;
}

void apagar_arvore_aux(NO *raiz) {

	if (raiz != NULL) {
		apagar_arvore_aux(raiz->fesq);
   		apagar_arvore_aux(raiz->fdir);
		apagar_item(&raiz->item);
		free(raiz);
  	}
}

void apagar_arvore(ARVORE **arv) {

	if (arv != NULL && *arv != NULL) {
		apagar_arvore_aux((*arv)->raiz);
		free(*arv);
  	}
}

NO *criar_no(ITEM *item){

	NO *no = (NO*) malloc(sizeof(NO));
	if(no != NULL){
		no->item = item;
		no->fesq = NULL;
		no->fdir = NULL;
		no->altura = 0;
	}
	return no;
}

int altura(NO *no){
	if(no == NULL){
		return -1;
	}
	else{
		return no->altura;
	}
}

NO *rot_direita(NO *a){
	

	NO *b = a->fesq;
	a->fesq = b->fdir;	
	b->fdir = a;
		
	a->altura = (altura(a->fesq) > altura(a->fdir)) ? altura(a->fesq) : altura(a->fdir);
	a->altura++;

	return b;
}

NO *rot_esquerda(NO *a){

	NO *b = a->fdir;
	a->fdir = b->fesq;
	b->fesq = a;

	a->altura = (altura(a->fesq) > altura(a->fdir)) ? altura(a->fesq) : altura(a->fdir);
	a->altura++;

	return b;
}

NO *rot_esquerda_direita(NO *a){

	a->fesq = rot_esquerda(a->fesq);
	return rot_direita(a);
}

NO *rot_direita_esquerda(NO *a){
	
	a->fdir = rot_direita(a->fdir);
	return rot_esquerda(a);
}

NO *inserir_arvore_aux(ARVORE *arv, NO *raiz, ITEM *item){
	
	NO *paux;

	if(raiz == NULL){
		raiz = criar_no(item);
		if(arv->raiz == NULL){
			arv->raiz = raiz;
		}
	}
	else if(item->chave > raiz->item->chave){
		raiz->fdir = inserir_arvore_aux(arv,raiz->fdir,item);	
		if(altura(raiz->fesq) - altura(raiz->fdir) == -2){
			if(item->chave > raiz->fdir->item->chave){
				paux = raiz;	 
				raiz = rot_esquerda(raiz);
				if(paux == arv->raiz) arv->raiz = raiz;
			}		
			else{
				paux = raiz;	 
				raiz = rot_direita_esquerda(raiz);
				if(paux == arv->raiz) arv->raiz = raiz;
			}
		}
	}
	else if(item->chave < raiz->item->chave){
		raiz->fesq = inserir_arvore_aux(arv,raiz->fesq,item);	
		if(altura(raiz->fesq) - altura(raiz->fdir) == 2){
			if(item->chave < raiz->fesq->item->chave){
				paux = raiz;	 
				raiz = rot_direita(raiz);
				if(paux == arv->raiz) arv->raiz = raiz;
			}	
			else{
				paux = raiz;	 
				raiz = rot_esquerda_direita(raiz);
				if(paux == arv->raiz) arv->raiz = raiz;
			}
		}
	}
	
	raiz->altura = (altura(raiz->fesq) > altura(raiz->fdir)) ? altura(raiz->fesq) : altura(raiz->fdir);
	raiz->altura++;
	
	return raiz;	
}

int inserir_arvore(ARVORE *arv, ITEM *item){
	return (inserir_arvore_aux(arv,arv->raiz,item) != NULL);
}

ITEM *buscar_arvore_aux(NO *raiz, int chave) {

	if (raiz == NULL) {
    		return NULL;
  	} 
	else {
    		if (raiz->item->chave > chave) {
      			return buscar_arvore_aux(raiz->fesq, chave);
    		} 
    		else if (raiz->item->chave < chave) {
      			return buscar_arvore_aux(raiz->fdir, chave);
    		} 
    		else {
      			return raiz->item;
    		}
  	}
}

ITEM *buscar_arvore(ARVORE *arv, int chave) {
	if (arv != NULL) {
		return buscar_arvore_aux(arv->raiz, chave);
	}
  	return 0;
}

void preordem_aux(NO *raiz) {

	if (raiz != NULL) {
		imprimir_item(raiz->item);
    	preordem_aux(raiz->fesq);
    	preordem_aux(raiz->fdir);
  	}
}

void preordem(ARVORE *arv) {
	preordem_aux(arv->raiz);
}

void emordem_aux(NO *raiz) {

	if (raiz != NULL) {
		emordem_aux(raiz->fesq);
	    	imprimir_item(raiz->item);
   	 	emordem_aux(raiz->fdir);
  	}
}

void emordem(ARVORE *arv) {
	emordem_aux(arv->raiz);
}

void posordem_aux(NO *raiz) {

	if (raiz != NULL) {
    		posordem_aux(raiz->fesq);
    		posordem_aux(raiz->fdir);
    		imprimir_item(raiz->item);
  	}
}

void posordem(ARVORE *arv) {
	posordem_aux(arv->raiz);
}

int altura_arvore(ARVORE *arv) {
	if(arv->raiz == NULL){
		return -1;
	}
	else{
		return arv->raiz->altura;
	}
}
