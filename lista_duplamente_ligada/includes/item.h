#ifndef _ITEM_H
#define	_ITEM_H

typedef struct ITEM {
  int chave;
  int valor;
} ITEM;

ITEM *criar_item(int chave, int valor);
void apagar_item(ITEM **item);
void imprimir_item(ITEM *item);

#endif	
