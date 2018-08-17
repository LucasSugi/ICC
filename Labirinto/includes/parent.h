/*
* Armazena as refêrencias para os pais dos vértices
* author Sugi
*/

#ifndef _PARENT_H_
#define _PARENT_H_

#include "grafo.h"

/*Definindo a estrutura*/
typedef struct parent PARENT;

/*Criação da estrutura dos pais dos vértices*/
PARENT *createParent(GRAPH *);

/*Desaloca a estrutura da memória*/
void destroyParent(PARENT *);

/*Insere uma nova referência*/
void insertParent(PARENT *, VERTEX *, VERTEX *);

/*Menor caminho*/
int shortestPath(PARENT *, VERTEX *, VERTEX *, int);

#endif
