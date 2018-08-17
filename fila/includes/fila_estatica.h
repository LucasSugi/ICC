#ifndef _FILA_ESTATICA_H
#define _FILE_ESTATICA_H

#include "item.h"
#define TAM 10
typedef struct fila_estatica FILA_ESTATICA;

FILA_ESTATICA *criar_fila();
void apagar_fila(FILA_ESTATICA**);

int enfileirar(FILA_ESTATICA *,ITEM *);
ITEM *desenfileirar(FILA_ESTATICA *);

int cheia(FILA_ESTATICA *);
int vazia(FILA_ESTATICA *);
int tamanho(FILA_ESTATICA *);

void imprimir_fila(FILA_ESTATICA *);

#endif
