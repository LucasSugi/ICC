#include "pilha_dinamica.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct no{
	ITEM *item;
	struct no *anterior;
} NO;

struct pilha{
	NO* topo;
	int tamanho;
};

void apagar_no(NO **no){

	if(no != NULL && *no != NULL){
		apagar_item( &((*no)->item) );
		free(*no);
		*no = NULL;
	}
}

PILHA *criar_pilha(){
	
	PILHA *pilha = (PILHA*) malloc(sizeof(PILHA));
	if( pilha != NULL){
		pilha->topo = NULL;
		pilha->tamanho = 0;
	}
	return pilha;
}

void apagar_pilha(PILHA **pilha){
	
	if(pilha != NULL && *pilha != NULL){
		NO *paux = (*pilha)->topo;	
		while(paux != NULL){
			NO *prem = paux;
			paux = paux->anterior;
			apagar_no(&prem);	
		}
		free(*pilha);
		*pilha = NULL;
	}
}

int empilhar(PILHA *pilha, ITEM *item){
	
	if( !cheia(pilha) ){
		NO *pnovo = (NO*) malloc(sizeof(NO));
		if(pnovo != NULL){
			pnovo->item = item;
			pnovo->anterior = pilha->topo;
			pilha->topo = pnovo;
			pilha->tamanho++;
		}
	
		return 1;
	}
	return 0;
}

int desempilhar(PILHA *pilha){

	if( !vazia(pilha) ){
		NO *paux = pilha->topo;		
		pilha->topo = pilha->topo->anterior;
		apagar_no(&paux);
		pilha->tamanho--;
		return 1;
	}
	return 0;
}

ITEM *topo(PILHA *pilha){

	if( !vazia(pilha) ){
		return pilha->topo->item;
	}
	return NULL;
}

int vazia(PILHA *pilha){
	return pilha->topo == NULL;
}

int cheia(PILHA *pilha){
	return 0;
}

int tamanho(PILHA *pilha){
	return pilha->tamanho;
}

void imprimir(PILHA *pilha){

	NO *paux = pilha->topo;

	while(paux != NULL){
		imprimir_item(paux->item);
		paux = paux->anterior;
	}

}
