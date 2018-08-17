#ifndef ITEM_H
#define ITEM_H

typedef struct item{ 

	int chave;	
	int valor;
}ITEM;

ITEM *criar_item(int, int );
void apagar_item(ITEM **);
void imprimir_item(ITEM *);

#endif
