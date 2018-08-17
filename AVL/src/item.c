#include "item.h"
#include <stdlib.h>
#include <stdio.h>

ITEM *criar_item(int chave, int valor) {
	ITEM *item = (ITEM *)malloc(sizeof(ITEM));
	item->chave = chave;
	item->valor = valor;
	return item;
}

void apagar_item(ITEM **item) {
	if (item != NULL) {
		free(*item);
    		*item = NULL;
  	}
}

void imprimir_item(ITEM *item) {
	printf("%d - %d\n", item->chave, item->valor);
}
