#include "fila_estatica.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>

struct fila_estatica{
	ITEM *item[TAM];
	int inicio;
	int fim;
};

FILA_ESTATICA *criar_fila(){

	FILA_ESTATICA *fila = (FILA_ESTATICA*) malloc(sizeof(FILA_ESTATICA));
	int i;

	if(fila != NULL){
		fila->inicio = 0;	
		fila->fim = 0;
	}

	for(i=0;i<TAM;i++){
		fila->item[i] = NULL;
	}

	return fila;
}

void apagar_fila(FILA_ESTATICA **fila){
	
	int i;

	if(fila != NULL && *fila != NULL){
		for(i=0;i<TAM;i++){	
			if( (*fila)->item[i] != NULL){
				apagar_item( &((*fila)->item[i]) );	
			}
		}			
		free(*fila);	
		*fila = NULL;
	}
}

int enfileirar(FILA_ESTATICA *fila, ITEM *item){

	if( !cheia(fila) ){
		if(fila->item[fila->fim] != NULL){
			apagar_item( &(fila->item[fila->fim]) );
		}
		fila->item[fila->fim] = item;
		fila->fim = (fila->fim + 1) % TAM;
	
	}
	return 0;
}

ITEM *desenfileirar(FILA_ESTATICA *fila){
		
	if( !vazia(fila) ){
		ITEM *ret = fila->item[fila->inicio];
		fila->inicio = (fila->inicio + 1 ) % TAM;
		return ret;
	}
	return NULL;
}

int cheia(FILA_ESTATICA* fila){
	return (fila->fim + 1 % TAM) == fila->inicio;
}

int vazia(FILA_ESTATICA *fila){
	return fila->fim == fila->inicio;
}

int tamanho(FILA_ESTATICA *fila){
	
	if(fila->inicio < fila ->fim){
		return fila->fim - fila->inicio;		
	} else {
		return TAM - fila->inicio + fila->fim;	
	}
}

void imprimir_fila(FILA_ESTATICA *fila){
	
	int  i = fila->inicio;
	
	while(i != fila->fim){
		imprimir_item(fila->item[i]);
		i = (i + 1) % TAM;
	}
	printf("\n");
}
