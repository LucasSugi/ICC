#include "item.h"
#include "pilha_estatica.h"

#include <stdio.h>
#include <stdlib.h>

#define TAM 100

struct pilha {
	ITEM *vetor[TAM];
	int topo;
};

PILHA *criar_pilha(){
	
	PILHA *pilha = (PILHA*) malloc(sizeof(PILHA));
	if(pilha != NULL){
		pilha->topo = -1;
	}
	return pilha;
}

void apagar_pilha(PILHA **pilha){

	if(pilha != NULL && *pilha != NULL){
		if( !vazia(*pilha) ){
			int i;

			for(i=0;i<=(*pilha)->topo;i++){
				apagar_item( &((*pilha)->vetor[i]) );	
			}
			free(*pilha);
			*pilha = NULL;
		}
	}
}

int empilhar(PILHA *pilha, ITEM *item){
	
	if( !cheia(pilha) ){
		pilha->vetor[++pilha->topo] = item;
		return 1;
	}
	return 0;
}

int desempilhar(PILHA *pilha){
	if( !vazia(pilha) ){
		apagar_item( &(pilha->vetor[pilha->topo--]) );
		return 1;
	}
	return 0;
}

ITEM *topo(PILHA *pilha){
	
	if( !vazia(pilha) ){
		return pilha->vetor[pilha->topo];
	}
	return NULL;
}

int vazia(PILHA *pilha){
	return pilha->topo == -1;
}

int cheia(PILHA *pilha){
	return pilha->topo == TAM - 1;
}

int tamanho(PILHA *pilha){
	return pilha->topo + 1;
}

void imprimir(PILHA *pilha){

	int i;
	
	for(i=0;i<=pilha->topo;i++){
		imprimir_item(pilha->vetor[i]);
	}
}
