#include "lista_ligada.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NO{

	ITEM *item;
	struct NO *proximo;

} NO;

struct lista_ligada{

	NO *sentinela;
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
			no->proximo = no;
			lista->sentinela = no;
			lista->tamanho = 0;
		}
	}

	return lista;
}

void apagar_lista(LISTA_LIGADA **lista){

	NO *paux = (*lista)->sentinela->proximo;
	NO *prem = NULL;

	while(paux != (*lista)->sentinela ){
		prem = paux;
		paux = paux->proximo;
		apagar_no(prem);
	}
	apagar_no( (*lista)->sentinela );
	free(*lista);
	*lista = NULL;
}

int inserir_item(LISTA_LIGADA *lista, ITEM *item){

	if( !(cheia(lista)) ){
		NO *pnovo = (NO*) malloc(sizeof(NO)); 
		
		if(pnovo != NULL){
			pnovo->item = item;
		}	
		
		pnovo->proximo = lista->sentinela->proximo;
		lista->sentinela->proximo = pnovo;

		lista->tamanho++;

		return 1;
	}
	return 0;
}

int remover_item(LISTA_LIGADA *lista, int chave){

	NO *prem = lista->sentinela->proximo;
	NO *pant = lista->sentinela;
	
	while( prem != lista->sentinela && prem->item->chave != chave){
		pant = prem;
		prem = prem->proximo;		
	}

	if(prem != lista->sentinela ){
			
		pant->proximo = prem->proximo;		
		lista->tamanho--;
		apagar_no(prem);
	
		return 1;
	}

	return 0;
}

ITEM *recuperar_item(LISTA_LIGADA *lista, int chave){
	
	if( !(vazia(lista)) ){
		NO *paux = lista->sentinela->proximo;

		while(paux != lista->sentinela ){
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
	return (lista->sentinela == lista->sentinela->proximo);
}

int cheia(LISTA_LIGADA *lista){
	return 0;
}

void imprimir(LISTA_LIGADA *lista){
	
	NO *paux = lista->sentinela->proximo;

	while(paux != lista->sentinela ){
		imprimir_item(paux->item);
		paux = paux->proximo;
	}	
}
