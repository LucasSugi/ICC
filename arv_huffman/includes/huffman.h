#ifndef _HUFFMAN_H_
#define	_HUFFMAN_H_

#include "arvore_binaria.h"

typedef struct huffman HUFFMAN;

HUFFMAN *criar_huffman();

void apagar_huffman(HUFFMAN **);

void criar_arvore_huffman(HUFFMAN *, char *);

void criar_codigo(HUFFMAN *);

void codificar(HUFFMAN *, char *, char *);

int decodificar(HUFFMAN *, char *, char *);

#endif
