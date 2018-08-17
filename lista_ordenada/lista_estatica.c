#include <stdio.h>
#include <stdlib.h>
#include "lista_estatica.h"

LISTA_ESTATICA *criar_lista(){

	LISTA_ESTATICA *lista = (LISTA_ESTATICA*) malloc(sizeof(LISTA_ESTATICA));

	if(lista != NULL){
		lista->fim = -1;
	}	

	return lista;
}

void apagar_lista(LISTA_ESTATICA **lista){

	int i;

	if(lista != NULL && *lista != NULL){
		for(i=0;i<=(*lista)->fim;i++){
			apagar_item(&((*lista)->vetor[i]));	
		}	
		free(*lista);
		*lista = NULL;	
	}
}

int inserir(LISTA_ESTATICA *lista, ITEM *item){

	int pos;

	if(!cheia(lista)){

		pos = lista->fim + 1;
		while( (pos != 0) &&  (lista->vetor[pos-1]->chave > item->chave) ){
			lista->vetor[pos] = lista->vetor[pos-1];	
			pos--;						
		}
		lista->vetor[pos] = item;
		lista->fim++;
		return 1;
	}

	return 0;
}

int remover(LISTA_ESTATICA *lista){

	if(!vazia(lista)){
		apagar_item(&(lista->vetor[lista->fim])); 
		lista->fim--;
		return 1;
	}	
	return 0;
}

ITEM *recuperar_chave(LISTA_ESTATICA *lista, int chave){

	int i, esq, dir, meio;
	if(!vazia(lista)) {
		esq = 0;
		dir = lista->fim;

		while (esq <= dir) {
			meio = (esq+dir)/2;

			if(lista->vetor[meio]->chave == chave) {
				return lista->vetor[meio];
			} else if(lista->vetor[meio]->chave < chave) {
				esq = meio+1;
			} else {
				dir = meio-1;
			}
		}
	}
	return NULL;
}

void imprimir_lista(LISTA_ESTATICA *lista){
	
	int i;

	for(i=0;i<=lista->fim;i++){
		imprimir_item(lista->vetor[i]);
	}
}

int tamanho(LISTA_ESTATICA *lista){
	return (lista->fim+1);
}

int vazia(LISTA_ESTATICA *lista){
	return (lista->fim == -1);
}

int cheia(LISTA_ESTATICA *lista){
	return (lista->fim == TAM -1);
}

