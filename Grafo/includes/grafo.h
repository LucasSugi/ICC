/*
*
* Grafo implementado com a seguinte estrutura de dados:  Lista de Adjacências
* author Sugi
*/

#ifndef _GRAFO_H_
#define _GRAFO_H_


/*Definindo as estruturas que serão utilizadas*/
typedef struct graph GRAPH;
typedef struct vertex VERTEX;
typedef struct edge EDGE;

/*
* Cria um grafo
* Retorna uma referência para o grafo
*/
GRAPH *createGraph();

/*
* Insere um vértice no grafo armazenando um valor nele 
* Retorna uma referência para o vértice
*/
VERTEX *insertVertex(GRAPH *, int);

/*
* Insere uma aresta no grafo armazenando um valor nele
* Retorna uma referência para a aresta
*/
EDGE *insertEdge(GRAPH *, VERTEX *, VERTEX *,int);

/*
* Remove um vértice do grafo
* Retorna o conteúdo armazenado no vértice
*/
int removeVertex(GRAPH *,VERTEX *);

/*
* Remove uma aresta do grafo
* Retorna o conteúdo armazenado na aresta
*/
int removeEdge(GRAPH *, EDGE *);

/*
* Retorna a quantidade de vértices
*/
int nVertex(GRAPH *);

/*
* Retorna a quantidade de arestas
*/
int nEdge(GRAPH *);

/*
* Setar um novo rótulo no vértice
*/
void setLabelVertex(VERTEX *, int);
 
/*
* Setar um novo rótulo na aresta
*/
void setLabelEdge(EDGE *, int );
 
/*
* Retorna o rótulo atual do vértice
*/
int getLabelVertex(VERTEX *);
 
/*
* Retorna o rótulo atual da aresta
*/
int getLabelEdge(EDGE *);

/*
* Processando o vértice
*/
void processVertex(VERTEX *);

/*
* Retorna o vértice oposto a aresta
*/
VERTEX *opposite(GRAPH *, VERTEX *, EDGE *);

/* 
* Processando a aresta
*/
void processEdge(EDGE *);

/*
* Retorna uma lista de arestas incidentes no vértice
*/
EDGE **incidentEdge(GRAPH *, VERTEX *);

/*
* Retorna uma lista de vértices do grafo
*/
VERTEX **vertices(GRAPH *);

/*
* Remove o grafo
*/
void removeGraph(GRAPH *);


#endif
