/*
* Implementação de um grafo 
* author Sugi
*/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

/*Estruturas a serem utilizadas no grafo*/
typedef struct incidentEgde{

	struct incidentEgde *right;
	struct incidentEgde *left;
	struct edge *edge;

} INCIDENT_EDGE;

struct vertex{

	VERTEX *right;
	VERTEX *left;
	INCIDENT_EDGE *incidentEgde;
	int label;
	int value;
};

struct edge{

	EDGE *right;
	EDGE *left;
	VERTEX  *vertex1;
	VERTEX *vertex2;
	INCIDENT_EDGE *incidentEgde1;
	INCIDENT_EDGE *incidentEgde2;
	int label;
	int value;
};

struct graph{
	
	EDGE *listEdge;
	VERTEX *listVertex;
	int nEdge;
	int nVertex;

};

/*
* Cria um grafo
* Retorna uma referência para o grafo
*/
GRAPH *createGraph(){
	
	/*Criação do grafo*/	
	GRAPH *graph = (GRAPH*) malloc(sizeof(GRAPH));
	
	/*
        * Inicializaçao do grafo
	* O grafo irá possuir a estrutura lista circular com nó cabeça para auxliar na remoção e inserção
	*/	
	graph->listEdge = (EDGE*) malloc(sizeof(EDGE));	
	graph->listEdge->right = graph->listEdge;
	graph->listEdge->left = graph->listEdge;
	graph->listEdge->vertex1 = NULL;
	graph->listEdge->vertex2 = NULL;
	graph->listEdge->incidentEgde1 = NULL;
	graph->listEdge->incidentEgde2 = NULL;
	graph->listEdge->value = 0;
	graph->listEdge->label = -1;
	graph->nEdge = 0;
	
	graph->listVertex = (VERTEX*) malloc(sizeof(VERTEX));	
	graph->listVertex->right = graph->listVertex;	
	graph->listVertex->left = graph->listVertex;	
	graph->listVertex->incidentEgde = NULL;
	graph->listVertex->value = 0;
	graph->listVertex->label = -1;
	graph->nVertex = 0;

	return graph;
}

/*
* Insere um vértice no grafo armazenando um valor nele 
* Retorna uma referência para o vértice
*/
VERTEX *insertVertex(GRAPH *graph, int value){
	
	/*Criação do novo vértice*/	
	VERTEX *newVertex = (VERTEX*) malloc(sizeof(VERTEX));
	
	/*Arrumando a lista circular*/
	newVertex->value = value;	
	newVertex->label = -1;	
	newVertex->left = graph->listVertex;	
	newVertex->right = graph->listVertex->right;	
	graph->listVertex->right->left = newVertex;
	graph->listVertex->right = newVertex;

	/*Criando um nó cabeça para a lista de arestas incidentes no novo vértice*/	
	newVertex->incidentEgde = (INCIDENT_EDGE*) malloc(sizeof(INCIDENT_EDGE));
	
	/*Arrumando a lista de arestas incidentes*/
	newVertex->incidentEgde->right = newVertex->incidentEgde;
	newVertex->incidentEgde->left = newVertex->incidentEgde;
	newVertex->incidentEgde->edge = NULL;

	/*Aumentando o número de vértices*/
	graph->nVertex++;

	return newVertex;
}

/*
* Insere uma aresta no grafo armazenando um valor nele
* Retorna uma referência para a aresta
*/
EDGE *insertEdge(GRAPH *graph, VERTEX *vertex1, VERTEX *vertex2, int value){
	
	/*Criação da nova aresta*/
	EDGE *newEdge = (EDGE*) malloc(sizeof(EDGE));
	
	/*Arrumando a lista circular*/
	newEdge->value = value;
	newEdge->label = -1;
	newEdge->left = graph->listEdge;
	newEdge->right = graph->listEdge->right;
	graph->listEdge->right->left = newEdge;
	graph->listEdge->right = newEdge;

	/*Fazendo a aresta apontar para os seus vértices*/
	newEdge->vertex1 = vertex1;
	newEdge->vertex2 = vertex2;
	
	/*Criando a referência para a aresta*/
	INCIDENT_EDGE  *incidentEgde1 = (INCIDENT_EDGE*) malloc(sizeof(INCIDENT_EDGE));

	/*Arrumar a lista de referência para a aresta*/
	incidentEgde1->left = vertex1->incidentEgde;
	incidentEgde1->right = vertex1->incidentEgde->right;
	vertex1->incidentEgde->right->left = incidentEgde1;
	vertex1->incidentEgde->right = incidentEgde1;

	/*Fazendo a referência apontar para a aresta*/
	incidentEgde1->edge = newEdge;

	/*Repetindo o processor para o segundo vértice*/
	INCIDENT_EDGE  *incidentEgde2 = (INCIDENT_EDGE*) malloc(sizeof(INCIDENT_EDGE));
	incidentEgde2->left = vertex2->incidentEgde;
	incidentEgde2->right = vertex2->incidentEgde->right;
	vertex2->incidentEgde->right->left = incidentEgde2;
	vertex2->incidentEgde->right = incidentEgde2;
	incidentEgde2->edge = newEdge;
	
	/*Fazendo a aresta apontar para a sua própia referência*/
	newEdge->incidentEgde1 = incidentEgde1;
	newEdge->incidentEgde2 = incidentEgde2;
	
	/*Aumentando o número de arestas*/
	graph->nEdge++;

	return newEdge;
}

/*
* Remove uma referência da aresta
*/
void removeIncidentEdge(GRAPH *graph, INCIDENT_EDGE *incidentEgde){
	
	/*Arrumando a lista de arestas incidentes*/	
	incidentEgde->right->left = incidentEgde->left;
	incidentEgde->left->right = incidentEgde->right;
	incidentEgde->edge = NULL;		
	free(incidentEgde);
}

/*
* Remove um vértice do grafo
* Retorna o conteúdo armazenado no vértice ou -1 indicando que não foi possível remove-la
*/
int removeVertex(GRAPH *graph,VERTEX *vertex){
	
	int ret = -1;
	INCIDENT_EDGE *incidentEgde, *prem;	
	
	VERTEX *fetch = graph->listVertex->right;

	/*Procurando pelo vértice a ser removido*/
	while(fetch != graph->listVertex && fetch != vertex){
		fetch = fetch->right;
	}
	
	/*Apagando a vértice*/
	if(fetch == vertex){
		/*Armazenando o valor contido no vértice*/
		ret = fetch->value;
		fetch->value = -1;
	
		/*Arrumando a lista de vértices*/	
		fetch->right->left = fetch->left;
		fetch->left->right = fetch->right;
		
		/*Arrumando ponteiros*/	
		fetch->right = NULL;	
		fetch->left = NULL;	
		
		/*Eliminando as arestas incidentes*/
		incidentEgde = fetch->incidentEgde->right;
		while(incidentEgde != fetch->incidentEgde){
			prem = incidentEgde;
			incidentEgde = incidentEgde->right;
			removeEdge(graph,prem->edge);
		}
	
		/*Dimiuindo o número de vértices*/
		graph->nVertex--;

		/*Remoção final da heap*/
		free(fetch->incidentEgde);
		free(fetch);
	}

	return ret;
}

/*
* Remove uma aresta do grafo
* Retorna o conteúdo armazenado na aresta ou -1 indicando que não foi possível remove-la
*/
int removeEdge(GRAPH *graph, EDGE *edge){
	
	int ret = -1;

	EDGE *fetch = graph->listEdge->right;

	/*Procurando pela aresta a ser removida*/
	while(fetch != graph->listEdge && fetch != edge){
		fetch = fetch->right;
	}

	/*Apagando a aresta*/
	if(fetch == edge){
		/*Arrumando ponteiros*/
		fetch->vertex1 = NULL;
		fetch->vertex2 = NULL;
		/*Armazenando o valor que estava na aresta*/
		ret = edge->value;
		fetch->value = -1;
		/*Removendo as referências*/
		removeIncidentEdge(graph,fetch->incidentEgde1);
		removeIncidentEdge(graph,fetch->incidentEgde2);
		/*Arrumando a lista de arestas*/
		fetch->right->left = fetch->left;
		fetch->left->right = fetch->right;
		/*Arrumando ponteiros*/
		fetch->incidentEgde1 = NULL;	
		fetch->incidentEgde2 = NULL;	
		fetch->right = NULL;
		fetch->left = NULL;
		/*Diminuindo o número de arestas*/
		graph->nEdge--;
		/*Desalocando*/
		free(fetch);
	}
	
	return ret;
}

/*
* Setar um novo rótulo no vértice
*/
void setLabelVertex(VERTEX *vertex, int label){
	vertex->label = label;
}

/*
* Setar um novo rótulo na aresta
*/
void setLabelEdge(EDGE *edge, int label){
	edge->label = label;
}

/*
* Retorna o rótulo atual do vértice
*/
int getLabelVertex(VERTEX *vertex){
	return vertex->label;
}

/*
* Retorna o rótulo atual da aresta
*/
int getLabelEdge(EDGE *edge){
	return edge->label;
}

/*
* Retorna a quantidade de vértices
*/
int nVertex(GRAPH *graph){
	return graph->nVertex;
}

/*
* Retorna a quantidade de arestas
*/
int nEdge(GRAPH *graph){
	return graph->nEdge;
}

/*
* Processando o vértice
*/
void processVertex(VERTEX *vertex){
	printf("Conteúdo do vértice: %d\n",vertex->value);
}

/* 
* Processando a aresta
*/
void processEdge(EDGE *edge){
	printf("Conteúdo da aresta: %d\n",edge->value);
}

/*
* Retorna o vértice oposto a aresta
*/
VERTEX *opposite(GRAPH *graph, VERTEX *vertex, EDGE *edge){
	
	/*Verificando qual o vértice oposto*/
	if(edge->vertex1 == vertex){
		return edge->vertex2;
	}
	else{
		return edge->vertex1;
	}
}

/*
* Retorna uma lista de arestas incidentes no vértice
*/
EDGE **incidentEdge(GRAPH *graph, VERTEX *vertex){
	
	int counter = 0;
	EDGE **edge;
	INCIDENT_EDGE *incidentEgde;

	/*Percorrendo as arestas incidentes para saber quantas são*/
	incidentEgde = vertex->incidentEgde->right;
	while(incidentEgde != vertex->incidentEgde){
		incidentEgde = incidentEgde->right;
		counter++;
	}	
	
	/*Alocando a quantidade exata de arestas*/
	edge = (EDGE**) malloc(sizeof(EDGE*) * (counter + 1));
	
	/*Armazenando as referências para o vértice*/
	incidentEgde = vertex->incidentEgde->right;
	counter = 0;
	while(incidentEgde != vertex->incidentEgde){
		edge[counter++] = incidentEgde->edge;
		incidentEgde = incidentEgde->right;
	}	
	edge[counter] = NULL;	
		
	return edge;
}

/*
* Retorna uma lista de vértices do grafo
*/
VERTEX **vertices(GRAPH *graph){
	
	int i = 0;
	VERTEX *v;
	
	/*Criação da lista de vértices*/	
	VERTEX **vertex = (VERTEX**) malloc(sizeof(VERTEX*) * graph->nVertex);
	
	/*Populando a lista com os vértices*/	
	v = graph->listVertex->right;
	while(v != graph->listVertex){
		vertex[i++] = v;
		v =  v->right;
	}	

	return vertex;
}

/*
* Retorna o valor contido no vértice
*/
int getVertex(VERTEX *vertex){
	return vertex->value;
}

/*
* Remove o grafo
*/
void removeGraph(GRAPH *graph){
	
	if(graph == NULL){
		return;
	}
	
	VERTEX *remVertex = graph->listVertex->right;
	VERTEX *prem;
	
	/*Removendo todas as estruturas do grafo*/
	while(remVertex != graph->listVertex){
		prem = remVertex;
		remVertex = remVertex->right;
		removeVertex(graph,prem);
	}
	
	/*Zerando a quantidade de vértices e arestas*/	
	graph->nEdge = 0;
	graph->nVertex = 0;
	
	/*Removendo os nós cabeças*/
	free(graph->listVertex);
	free(graph->listEdge);
	free(graph);

	/*Arrumando o ponteiro*/
	graph = NULL;
}
