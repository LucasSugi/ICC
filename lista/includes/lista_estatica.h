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

int inserir_fim(LISTA_ESTATICA *lista, ITEM *item);
int inserir_posicao(LISTA_ESTATICA *lista, ITEM *item, int pos);
int remover_fim(LISTA_ESTATICA *lista);

ITEM *recuperar_chave(LISTA_ESTATICA *lista, int chave);

int tamanho(LISTA_ESTATICA *lista);
int vazia(LISTA_ESTATICA *lista);
int cheia(LISTA_ESTATICA *lista);

void imprimir_lista(LISTA_ESTATICA *lista);

#endif
