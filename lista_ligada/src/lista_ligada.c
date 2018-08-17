#include "lista_ligada.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NO{

	ITEM *item;
	struct NO *proximo;

} NO;

struct lista_ligada{

	NO *inicio;
	NO *fim;
	int tamanho;	
};

void apagar_no(NO *no){

	apagar_item( &(no->item) );
	free(no);
}

LISTA_LIGADA *criar_lista(){

	LISTA_LIGADA *lista = (LISTA_LIGADA*) malloc(sizeof(LISTA_LIGADA));	
	
	if(lista != NULL){
		lista->inicio = NULL;
		lista->fim = NULL;
		lista->tamanho = 0;
	}

	return lista;
}

void apagar_lista(LISTA_LIGADA **lista){

	NO *paux = (*lista)->inicio;
	NO *prem = NULL;

	while(paux != NULL){
		prem = paux;
		paux = paux->proximo;
		apagar_no(prem);
	}
	free(*lista);
	*lista = NULL;
}

int inserir_item(LISTA_LIGADA *lista, ITEM *item){

	if( !(cheia(lista)) ){
		NO *pnovo = (NO*) malloc(sizeof(NO)); 
		
		if(pnovo != NULL){
			pnovo->item = item;
			pnovo->proximo = NULL;
		}	

		if(lista->inicio == NULL){
			lista->inicio = pnovo;
		} else {
			lista->fim->proximo = pnovo;
		}
		
		lista->fim = pnovo;	
		lista->tamanho++;
		return 1;
	}
	return 0;
}

int remover_item(LISTA_LIGADA *lista, int chave){

	NO *prem = lista->inicio;
	NO *pant = NULL;
	
	while( prem != NULL && prem->item->chave != chave){
		pant = prem;
		prem = prem->proximo;		
	}

	if(prem != NULL){
		if(prem == lista->inicio){
			lista->inicio = prem->proximo;
		} else {
			pant->proximo = prem->proximo;	
		}
		if(prem == lista->fim){
			lista->fim = pant;
		}

		lista->tamanho--;
		apagar_no(prem);
		return 1;
	}

	return 0;
}

ITEM *recuperar_item(LISTA_LIGADA *lista, int chave){
	
	if( !(vazia(lista)) ){
		NO *paux = lista->inicio;

		while(paux != NULL){
			if(paux->item->chave == chave){
				return paux->item;
			}
			paux = paux->proximo;
		}
	}
	return NULL;	
}

int tamanho(LISTA_LIGADA *lista){
	return (lista->tamanho);
}

int vazia(LISTA_LIGADA *lista){
	return (lista->inicio == NULL);
}

int cheia(LISTA_LIGADA *lista){
	return 0;
}

void imprimir(LISTA_LIGADA *lista){
	
	NO *paux;

	paux = lista->inicio;

	while(paux != NULL){
		imprimir_item(paux->item);
		paux = paux->proximo;
	}	
}
