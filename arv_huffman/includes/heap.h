#ifndef _HEAP_H_
#define _HEAP_H_

#include "arvore_binaria.h"

typedef struct heap HEAP;

HEAP *criar_heap();

void apagar_heap(HEAP **);

int inserir_heap(HEAP *, NO *);

NO *remover_heap(HEAP *);

int cheia_heap(HEAP *);

int vazia_heap(HEAP *);

int tamanho_heap(HEAP *);

#endif
