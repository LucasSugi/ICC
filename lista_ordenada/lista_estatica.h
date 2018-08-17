#ifndef LISTA_ESTATICA_H
#define LISTA_ESTATICA_H
#define TAM 100
#include "item.h"

typedef struct lista_estatica{

	ITEM *vetor[TAM];
	int fim;

} LISTA_ESTATICA;

LISTA_ESTATICA *criar_lista();
void apagar_lista(LISTA_ESTATICA **lista);

int inserir(LISTA_ESTATICA *lista, ITEM *item);
int remover(LISTA_ESTATICA *lista);

ITEM *recuperar_chave(LISTA_ESTATICA *lista, int chave);

void imprimir_lista(LISTA_ESTATICA *lista);

int tamanho(LISTA_ESTATICA *lista);
int vazia(LISTA_ESTATICA *lista);
int cheia(LISTA_ESTATICA *lista);

#endif
