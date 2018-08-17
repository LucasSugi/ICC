#ifndef _GRAPH_H_
#define _GRAPH_H_

//Definindo as estruturas do grafo
typedef struct vertex VERTEX;

typedef struct edge EDGE;

typedef struct graph GRAPH;

//Criação do vértice
GRAPH *createGraph();

//Inserção de um vértice
VERTEX *insertVertex(GRAPH *, int);

//Inserção de uma aresta
EDGE *insertEdge(GRAPH *,VERTEX *, VERTEX *, int);

//Remoção do vértice
int removeVertex(GRAPH *, VERTEX *);

//Remoção da aresta
int removeEdge(GRAPH *, EDGE *);

//Lista de arestas incidentes no vértice
EDGE **incidentEdge(GRAPH *,VERTEX *);

//Retorna uma lista com todos os vértices do grafo
VERTEX **vertices(GRAPH *);

//Desalocação do grafo
void removeGraph(GRAPH *);

#endif
