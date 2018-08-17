#ifndef _ITEM_H_
#define _ITEM_H_

typedef struct item {

	int valor;
	int chave;

} ITEM;

ITEM *criar_item(int, int);
void apagar_item(ITEM **);
void imprimir_item(ITEM *);

#endif
