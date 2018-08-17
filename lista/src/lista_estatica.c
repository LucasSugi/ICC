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

int inserir_fim(LISTA_ESTATICA *lista, ITEM *item){

	if(!cheia(lista)){
		lista->vetor[++lista->fim] = item;
		return 1;
	}
	return 0;
}

int inserir_posicao(LISTA_ESTATICA *lista, ITEM *item, int pos){

	int i;

	if(!cheia(lista) && pos >= 0 && pos <= lista->fim) {
		for(i=lista->fim; i >= pos; i--) {
			lista->vetor[i+1] = lista->vetor[i];
    		}
    		lista->vetor[pos] = item;
		    lista->fim++;
		return 1;
  	}
	return 0;
}

int remover_fim(LISTA_ESTATICA *lista){

	if(!vazia(lista)) {
    		apagar_item(&(lista->vetor[lista->fim]));
    		lista->fim--;
   	 return 1;
  	}
  	return 0;
}

ITEM *recuperar_chave(LISTA_ESTATICA *lista, int chave){

	int i;

	for(i=0;i<=lista->fim;i++){
		if(lista->vetor[i]->chave == chave){
			return lista->vetor[i];
		}
	}
	return NULL;
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

void imprimir_lista(LISTA_ESTATICA *lista){

	int i;

	for(i=0;i<=lista->fim;i++){
		imprimir_item(lista->vetor[i]);
	}
}
