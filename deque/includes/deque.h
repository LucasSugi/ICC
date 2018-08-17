#ifndef _DEQUE_ESTATICA_H_
#define	_DEQUE_ESTATICA_H_

#include "item.h"
typedef struct deque DEQUE;

DEQUE *criar_deque();
void apagar_deque(DEQUE**);

int inserir_fim(DEQUE*, ITEM*);
int inserir_inicio(DEQUE*, ITEM*);

int remover_inicio(DEQUE*);
int remover_fim(DEQUE*);

int cheia(DEQUE*);
int vazia(DEQUE*);
int tamanho(DEQUE*);

void imprimir_deque(DEQUE*);

#endif

