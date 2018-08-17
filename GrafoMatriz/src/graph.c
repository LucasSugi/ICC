/*
* Criação de um grafo a partir da matriz de adjascências
* author Sugi
*/
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define N 50
#define M 50

//Definição das estruturas do grafo
struct vertex{

	int key,value,label;
	VERTEX *right, *left;

};

struct edge{
	
	int value,label;
	EDGE *right, *left;
	VERTEX *v1, *v2;
};

struct graph{
	
	EDGE ***matrix;
	VERTEX *listVertex;
	EDGE *listEdge;
	int nEdge, nVertex, *index;
};

//Criação do vértice
GRAPH *createGraph(){
		
	//Alocando o grafo	
	GRAPH *graph = (GRAPH*) malloc(sizeof(GRAPH));

	//Alocando as estruturas internas
	/*Aresta*/
	graph->listEdge = (EDGE*) malloc(sizeof(EDGE));
	graph->listEdge->right = graph->listEdge;
	graph->listEdge->left = graph->listEdge;
	graph->listEdge->v1 = NULL;
	graph->listEdge->v2 = NULL;
	graph->listEdge->value = -1;
	graph->listEdge->label = -1;

	/*Vértice*/
	graph->listVertex = (VERTEX*) malloc(sizeof(VERTEX));
	graph->listVertex->right = graph->listVertex;
	graph->listVertex->left = graph->listVertex;
	graph->listVertex->key = -1;
	graph->listVertex->label = -1;
	graph->listVertex->value = -1;
	
	/*Índice*/
	graph->index = (int*) malloc(sizeof(int) * N);
	for(int i=0;i<N;i++){
		graph->index[i] = -1;	
	} 
	
	/*Matriz*/
	graph->matrix = (EDGE***) malloc(sizeof(EDGE**) * N);
	for(int i=0;i<N;i++){
		graph->matrix[i] = (EDGE**) malloc(sizeof(EDGE*) * M);
		for(int j=0;j<M;j++){
			graph->matrix[i][j] = NULL;
		}
	}
	
	/*Quantidade de vértices e arestas*/
	graph->nEdge = 0;	
	graph->nVertex = 0;	

	return graph;
}

//Inserção de um vértice
VERTEX *insertVertex(GRAPH *graph, int value){
	
	int i;
	
	//Alocando novo vértice
	VERTEX *v = (VERTEX*) malloc(sizeof(VERTEX));
	
	//Arrumando o novo vértice	
	v->value = value;
	v->label = -1;		
	v->left = graph->listVertex;
	v->right = graph->listVertex->right;
	graph->listVertex->right->left = v;
	graph->listVertex->right = v;
	
	//Verificando os índices disponíveis
	for(i=0;i<N;i++){
		if(graph->index[i] == -1){
			graph->index[i] = 1;
			break;
		}
	}
	v->key = i;			

	//Aumentar o número de vértices
	graph->nVertex++;	

	return v;
}

//Inserção de uma aresta
EDGE *insertEdge(GRAPH *graph,VERTEX *v1, VERTEX *v2, int value){

	//Alocando a aresta
	EDGE *e = (EDGE*) malloc(sizeof(EDGE));	

	//Arrumando a aresta
	e->v1 = v1;
	e->v2 = v2;
	e->value = value;
	e->label = -1;
	e->left = graph->listEdge;
	e->right = graph->listEdge->right;
	graph->listEdge->right->left = e;
	graph->listEdge->right = e;
	
	//Arrumando a matrix	
	graph->matrix[v1->key][v2->key] = e;
	graph->matrix[v2->key][v1->key] = e;
	
	//Aumentar número de arestas
	graph->nEdge++;

	return e;
}

//Remoção do vértice
int removeVertex(GRAPH *graph, VERTEX *v){
	
	int ret = -1, i = 0;
	VERTEX *fetch = graph->listVertex->right;
	EDGE **list;

	//Fazendo a busca do vértice
	while(fetch != graph->listVertex && fetch != v){
		fetch = fetch->right;	
	}
	
	//Veriricando se o vértice buscado é correto
	if(fetch == v){
			
		//Remover arestas incidentes
		list = incidentEdge(graph,v);	
		while(list[i++] != NULL){
			removeEdge(graph,list[i-1]);
		}
		free(list);			

		//Arrumando o vértice	
		ret = fetch->value;
		fetch->value = -1;
		fetch->label = -1;
		graph->index[fetch->key] = -1;
		fetch->key = -1;
		fetch->right->left = fetch->left;
		fetch->left->right = fetch->right;
		fetch->right = NULL;
		fetch->left = NULL;
		
		//Diminuindo o número de vértices
		graph->nVertex--;

		//Desalocando
		free(fetch);
		fetch = NULL;
	}	

	return ret;
}

//Remoção da aresta
int removeEdge(GRAPH *graph, EDGE *e){
	
	int ret = -1;

	EDGE *fetch = graph->listEdge->right;

	//Busca da aresta a ser removida
	while(fetch != graph->listEdge && fetch != e){
		fetch = fetch->right;
	}

	//Verificando se a aresta buscada é correta
	if(fetch == e){
		//Arrumando a aresta
		ret = fetch->value;
		fetch->value = -1;
		fetch->label = -1;
		fetch->right->left = fetch->left;
		fetch->left->right = fetch->right;
		fetch->v1 = NULL;
		fetch->v2 = NULL;
		fetch->right = NULL;
		fetch->left = NULL;

		//Arrumando a matriz
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				if(graph->matrix[i][j] == e){
					graph->matrix[i][j] = NULL;	
					graph->matrix[j][i] = NULL;	
					i = M;
					j = N;
				}
			}
		}

		//Diminuindo o número de arestas
		graph->nEdge--;		

		//Desalocando
		free(fetch);
		fetch = NULL;
	}
	
	return ret;
}

//Retorna uma lista de arestas incidentes no vértice
EDGE **incidentEdge(GRAPH *graph, VERTEX *v){
	
	int counter = 0;

	//Verificando quantas arestas incidentes há no vértice
	for(int i=0;i<M;i++){
		if(graph->matrix[v->key][i] != NULL && (graph->matrix[v->key][i]->v1 == v || graph->matrix[v->key][i]->v2 == v)){
			counter++;
		}
	}
	
	//Alocando lista
	EDGE **list = (EDGE**) malloc(sizeof(EDGE*) * (counter+1));
	list[counter] = NULL;	

	
	//Populando
	counter = 0;
	for(int i=0;i<M;i++){
		if(graph->matrix[v->key][i] != NULL && (graph->matrix[v->key][i]->v1 == v || graph->matrix[v->key][i]->v2 == v)){
			list[counter++] = graph->matrix[v->key][i];	
		}
	}
	
	return list;
}

//Retorna uma lista com todos os vértices do grafo
VERTEX **vertices(GRAPH *graph){
		
	int counter = 0;	
	VERTEX *move = graph->listVertex->right;
	
	//Alocando a lista
	VERTEX **list = (VERTEX**) malloc(sizeof(VERTEX*) * (graph->nVertex+1));
	list[graph->nVertex] = NULL;
	
	//Populando
	while(move != graph->listVertex){
		list[counter++] = move;
		move = move->right;
	}	
	
	return list;
}

//Desalocação do grafo
void removeGraph(GRAPH *graph){
	
	int i=0;
	
	//Lista com todos os vértices
	VERTEX **list = vertices(graph);
	
	//Removendo todos os vértices
	while(list[i++] != NULL){
		removeVertex(graph,list[i-1]);
	}
	
	//Remoção da matriz	
	for(i=0;i<N;i++){
		free(graph->matrix[i]);
	}
	free(graph->matrix);

	free(list);	
	graph->nEdge = 0;
	graph->nVertex = 0;
	free(graph->index);	
	free(graph->listEdge);
	free(graph->listVertex);
	free(graph);
	graph = NULL;
}
