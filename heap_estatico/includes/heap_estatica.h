#ifndef _HEAP_ESTATICA_H_
#define _HEAP_ESTATICA_H_

#include "item.h"

typedef struct heap_estatica HEAP_ESTATICA;

HEAP_ESTATICA *criar_heap();

void apagar_heap(HEAP_ESTATICA **);

int enfileirar(HEAP_ESTATICA *, ITEM *);

ITEM *desenfileirar(HEAP_ESTATICA *);

int cheia(HEAP_ESTATICA *);
int vazia(HEAP_ESTATICA *);
int tamanho(HEAP_ESTATICA *);

void imprimir_heap(HEAP_ESTATICA *);

#endif
