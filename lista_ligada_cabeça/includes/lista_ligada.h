#ifndef _LISTA_LIGADA_H_
#define _LISTA_LIGADA_H_

#include "item.h"

typedef struct lista_ligada LISTA_LIGADA;

LISTA_LIGADA *criar_lista();
void apagar_lista(LISTA_LIGADA **lista);

int inserir_item(LISTA_LIGADA *lista, ITEM *item);
int remover_item(LISTA_LIGADA *lista, int chave);
ITEM *recuperar_item(LISTA_LIGADA *lista, int chave);

int tamanho(LISTA_LIGADA *lista);
int vazia(LISTA_LIGADA *lista);
int cheia(LISTA_LIGADA *lista);
void imprimir(LISTA_LIGADA *lista);

#endif 
