#include "deque.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TAM 12

struct deque {
	ITEM *vetor[TAM];
	int inicio;
	int fim;
};

DEQUE *criar_deque(){

	DEQUE *deque = malloc(sizeof(DEQUE));

	if(deque != NULL){
		deque->inicio = 0;
		deque->fim = 0;
	}
	return deque;
}

void apagar_deque(DEQUE **deque){
	
	if(deque != NULL && *deque != NULL){
		int i;
		for(i=(*deque)->inicio;i != (*deque)->fim;i = (i + 1) % TAM){
			apagar_item( &((*deque)->vetor[i]) );
		}
		free(*deque);
		*deque = NULL;	
	}
}

int inserir_fim(DEQUE *deque, ITEM *item){
	
	if( !cheia(deque) ){
		deque->vetor[deque->fim] = item;
		deque->fim = (deque->fim + 1) % TAM;
		return 1;
	}
	return 0;
}

int inserir_inicio(DEQUE *deque, ITEM *item){
	
	if( !cheia(deque) ){
		deque->inicio = (deque->inicio + TAM - 1) % TAM;		
		deque->vetor[deque->inicio] = item;
		return 1;
	}
	return 0;
}

int remover_inicio(DEQUE *deque){
	
	if( !vazia(deque) ){
		free(deque->vetor[deque->inicio]);		
		deque->inicio = (deque->inicio + 1) % TAM;
		return 1;
	}
	return 0;
}

int remover_fim(DEQUE *deque){

	if( !vazia(deque) ){
		free(deque->vetor[deque->fim-1]  );	
		deque->fim = (deque->fim + TAM -1 ) % TAM;
		return 1;
	}
	return 0;
}

int cheia(DEQUE *deque){
	return ((deque->fim + 1) % TAM == deque->inicio);
}

int vazia(DEQUE *deque){
	return deque->fim == deque->inicio;
}

int tamanho(DEQUE *deque){
	
	if( !vazia(deque) ){
		if(deque->fim > deque->inicio){
			return deque->fim - deque->inicio;
		} else {
			return  TAM - deque->inicio + deque->fim;
		}
	}	
	return 0;
}
	
void imprimir_deque(DEQUE *deque){
	int i;
	for(i=deque->inicio; i != deque->fim; i = (i + 1) % TAM){
		imprimir_item(deque->vetor[i]);
	}	
	printf("\n");
}
