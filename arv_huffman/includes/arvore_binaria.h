#ifndef _ARVORE_BINARIA_H_
#define _ARVORE_BINARIA_H_

typedef struct NO {
	int simbolo;
	int frequencia;
	struct NO *filhoEsq;
	struct NO *filhoDir;
} NO;

typedef struct ARV {
	NO *raiz;
} ARV;

ARV *criar_arvore();

void apagar_arvore(ARV **);

NO *criar_raiz(ARV *, NO *);

int vazia_arvore(ARV *);

#endif
