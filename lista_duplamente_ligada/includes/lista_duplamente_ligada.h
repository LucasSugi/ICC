#ifndef _LISTA_DUPLAMENTE_LIGADA_H
#define _LISTA_DUPLAMENTE_LIGADA_H

#include "item.h"

typedef struct lista_duplamente_ligada LISTA_DUPLAMENTE_LIGADA;

LISTA_DUPLAMENTE_LIGADA *criar_lista();
void apagar_lista(LISTA_DUPLAMENTE_LIGADA **lista);

int inserir_lista(LISTA_DUPLAMENTE_LIGADA *lista, ITEM *item);
int remover_lista(LISTA_DUPLAMENTE_LIGADA *lista, int chave);
ITEM *buscar_lista(LISTA_DUPLAMENTE_LIGADA *lista, int chave);

int vazia_lista(LISTA_DUPLAMENTE_LIGADA *lista);
int cheia_lista(LISTA_DUPLAMENTE_LIGADA *lista);

void imprimir_lista(LISTA_DUPLAMENTE_LIGADA *lista);

#endif
