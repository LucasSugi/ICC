#include "lista_duplamente_ligada.h"
#include "item.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct NO{
	ITEM *item;
	struct NO *proximo;
	struct NO *anterior;
} NO;

struct lista_duplamente_ligada {
	NO *sentinela;
};

void apagar_no(NO *no){
	if(no != NULL){
		apagar_item( &(no->item) );
		free(no);
	}
}

LISTA_DUPLAMENTE_LIGADA *criar_lista(){
	
	LISTA_DUPLAMENTE_LIGADA *lista = (LISTA_DUPLAMENTE_LIGADA*) malloc(sizeof(LISTA_DUPLAMENTE_LIGADA));		
	
	if(lista != NULL){
		lista->sentinela = (NO*) malloc(sizeof(NO));
		if(lista->sentinela != NULL){
			lista->sentinela->item = criar_item(0,0);	
			lista->sentinela->proximo = lista->sentinela;
			lista->sentinela->anterior = lista->sentinela;
		} 
		else {
			free(lista);
			lista = NULL;
		}
	}
	return lista;
}

void apagar_lista(LISTA_DUPLAMENTE_LIGADA **lista){

	if(lista != NULL && *lista != NULL){
		NO *paux = (*lista)->sentinela->proximo;
		while( paux != (*lista)->sentinela){
			paux = paux->proximo;
			apagar_no(paux->anterior);
		}
		apagar_no(paux);
		free(*lista);
	}		
}

int inserir_lista(LISTA_DUPLAMENTE_LIGADA *lista, ITEM * item){
	
	NO *pnovo = NULL;
	NO *paux = NULL;
	
	if( !cheia_lista(lista) ){
		pnovo = (NO*) malloc(sizeof(NO));
		if(pnovo != NULL){
			pnovo->item = item;	
			lista->sentinela->item->chave = item->chave;
			paux = lista->sentinela;
			
			while( paux->proximo->item->chave < item->chave){
				paux = paux->proximo;
			}
			pnovo->proximo = paux->proximo;
			pnovo->anterior = paux;
			paux->proximo->anterior = pnovo;
			paux->proximo = pnovo;
			return 1;
		}
	}
	return 0;
}

ITEM *buscar_lista(LISTA_DUPLAMENTE_LIGADA *lista, int chave){
	
	NO *paux = lista->sentinela->proximo;
	lista->sentinela->item->chave = chave;

	while(paux->item->chave < chave){
		paux = paux->proximo;
	}

	if(paux != lista->sentinela && paux->item->chave == chave){
		return paux->item;
	}
	return NULL;
}

int remover_lista(LISTA_DUPLAMENTE_LIGADA *lista, int chave){

	NO *paux = lista->sentinela->proximo;
	lista->sentinela->item->chave = chave;

	while( paux->item->chave < chave){
		paux = paux->proximo;
	}

	if( paux != lista->sentinela &&  paux->item->chave == chave){
		paux->anterior->proximo = paux->proximo;	
		paux->proximo->anterior = paux->anterior;
	
		apagar_no(paux);	
		return 1;
	}
	return 0;
}

void imprimir_lista(LISTA_DUPLAMENTE_LIGADA *lista){
	
	NO *paux = lista->sentinela->proximo;

	while( paux != lista->sentinela ){
		imprimir_item(paux->item);
		paux = paux->proximo;
	}
}

int vazia_lista(LISTA_DUPLAMENTE_LIGADA *lista){
	return (lista->sentinela->proximo == lista->sentinela);
}

int cheia_lista(LISTA_DUPLAMENTE_LIGADA *lista){
	return 0;
}
