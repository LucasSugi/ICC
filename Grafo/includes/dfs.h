/*
* Algoritmo responsável por realizar a busca em profundidade em um grafo
* São implementadas a busca utilizando recursividade e uma pilha
* author Sugi
*/

#ifndef _DFS_H_
#define _DFS_H_

#include "grafo.h"

/*Busca em profundidade usando recursividade*/
void dfsRecursion(GRAPH *, VERTEX* );

/*Busca em profundidade usando pilha*/
void dfsStack(GRAPH *, VERTEX* );

#endif
