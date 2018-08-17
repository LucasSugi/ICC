/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */
#ifndef _ITEM_H
#define	_ITEM_H

typedef struct ITEM {
	int chave;
	int valor;
} ITEM;

ITEM *criar_item(int , int);
void apagar_item(ITEM **);
void imprimir_item(ITEM *);

#endif
