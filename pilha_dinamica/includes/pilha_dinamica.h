#ifndef _PILHA_DINAMICA_H_
#define _PILHA_DINAMICA_H_

#include "item.h"

typedef struct pilha PILHA;

PILHA *criar_pilha();
void apagar_pilha(PILHA **);

int empilhar(PILHA *, ITEM *);
int desempilhar(PILHA*);
ITEM *topo(PILHA *);

int vazia(PILHA *);
int cheia(PILHA *);

int tamanho(PILHA *);
void imprimir(PILHA *);

#endif
