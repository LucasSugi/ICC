#include "lista_ligada.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NO{

	ITEM *item;
	struct NO *proximo;

} NO;

struct lista_ligada{

	NO *cabeca;
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
		NO *no = (NO*) malloc(sizeof(NO));
		if(no != NULL){
			no->item = criar_item(0,0);	
			no->proximo = NULL;
			lista->cabeca = no;
			lista->fim = no;
			lista->tamanho = 0;
		}
	}

	return lista;
}

void apagar_lista(LISTA_LIGADA **lista){

	NO *paux = (*lista)->cabeca->proximo;
	NO *prem = NULL;

	while(paux != NULL ){
		prem = paux;
		paux = paux->proximo;
		apagar_no(prem);
	}
	apagar_no( (*lista)->cabeca );
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
		
		lista->fim->proximo = pnovo;
		lista->fim = pnovo;
		lista->tamanho++;
		return 1;
	}
	return 0;
}

int remover_item(LISTA_LIGADA *lista, int chave){

	NO *prem = lista->cabeca->proximo;
	NO *pant = lista->cabeca;
	
	while( prem != NULL && prem->item->chave != chave){
		pant = prem;
		prem = prem->proximo;		
	}

	if(prem != NULL){
	
		if(prem->proximo == NULL){
			lista->fim = pant;
		}
	
		pant->proximo = prem->proximo;
		apagar_no(prem);	
		lista->tamanho--;
		
		return 1;
	}

	return 0;
}

ITEM *recuperar_item(LISTA_LIGADA *lista, int chave){
	
	if( !(vazia(lista)) ){
		NO *paux = lista->cabeca->proximo;

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
	return (lista->cabeca->proximo == NULL);
}

int cheia(LISTA_LIGADA *lista){
	return 0;
}

void imprimir(LISTA_LIGADA *lista){
	
	NO *paux = lista->cabeca->proximo;

	while(paux != NULL){
		imprimir_item(paux->item);
		paux = paux->proximo;
	}	
}
