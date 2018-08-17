#ifndef _ARVORE_H_
#define _ARVORE_H_

#include "item.h"

typedef struct NO{

	ITEM *item;
	struct NO *fesq;
	struct NO *fdir;
	int altura;
} NO;

typedef struct arvore {
	NO *raiz;
} ARVORE;

ARVORE *criar_arvore();

void apagar_arvore(ARVORE **);

int inserir_arvore(ARVORE *, ITEM *);

ITEM *buscar_arvore(ARVORE *, int chave);

void posordem(ARVORE *);

void emordem(ARVORE *);

void preordem(ARVORE *);

#endif
