#ifndef _ARV_BUSCA_H_
#define _ARV_BUSCA_H_

#define FILHO_ESQ 0
#define FILHO_DIR 1
#include "item.h"

typedef struct no NO;

typedef struct arv ARV;

ARV *criar_arvore();

NO *criar_raiz(ARV *, ITEM *);

void apagar_arvore(ARV **);

int vazia(ARV *);

void imprimir_emordem(ARV *);

int altura_arvore(ARV *);

int inserir_abb(ARV *, ITEM *);

ITEM *busca_abb(ARV *, int);

int remove_abb(ARV *, int);

#endif
