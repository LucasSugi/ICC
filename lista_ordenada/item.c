#include "item.h"
#include <stdio.h>
#include <stdlib.h>

ITEM *criar_item(int valor, int chave){

	ITEM *item = (ITEM*) malloc(sizeof(ITEM));

	if(item != NULL){
		item->chave = chave;
		item->valor = valor;
	}
}

void apagar_item(ITEM **item){
	
	if(item != NULL && *item != NULL){
		free(*item);
	}
	*item = NULL;
}

void imprimir_item(ITEM *item){
	
	if(item != NULL){
		printf("%d - %d\n",item->chave,item->valor);
	}
}
