#ifndef _ARVORE_BINARIA_H_
#define _ARVORE_BINARIA_H_

#include "item.h"
#define FILHO_ESQ 0
#define FILHO_DIR 1

typedef struct arvore_binaria ARVORE_BINARIA;
typedef struct no NO;

ARVORE_BINARIA *criar_arvore();
void apagar_arvore(ARVORE_BINARIA **);
NO *criar_raiz(ARVORE_BINARIA *, ITEM *);

NO *inserir_filho(int , NO *, ITEM *);
int vazia(ARVORE_BINARIA *);

void imprimir_emordem(ARVORE_BINARIA *);
void imprimir_preordem(ARVORE_BINARIA *);
void imprimir_posordem(ARVORE_BINARIA *);
int altura_arvore(ARVORE_BINARIA *);

#endif
