/*
* Algoritmo responsável por realizar busca em largura dado um grafo
* author Sugi
*/

#include "grafo.h"
#include "parent.h"
#include <stdlib.h>
#include <stdio.h>

#define EXPLORED 0
#define DISCOVERED 1
#define NODISCOVERED -1
#define CROSSING 0

/*Estrutura da fila*/
typedef struct queue{
	
	VERTEX **queueV;
	int pointer;
	int n;

} QUEUE;

/*
* Criação de uma fila de prioridades
*/
QUEUE *createQueue(int n){
	
	int i;

	/*Criação da fila*/
	QUEUE *queue = (QUEUE*) malloc(sizeof(QUEUE));
	queue->queueV = (VERTEX**) malloc(sizeof(VERTEX*) * n);
	
	/*Inicialização da fila*/
	queue->pointer = 0;
	queue->n = 0;
	
	return queue;
}

/*
* Enfileirar um vértice
*/
void toqueue(QUEUE *queue, VERTEX *vertex){
	
	/*Enfileirando*/
	queue->queueV[queue->n++] = vertex;
}

/*
* Desenfileirar um vértice
*/

VERTEX *dequeue(QUEUE *queue){
	
	/*Verificando se há vértices na fila*/
	if(queue->n != queue->pointer){
		return queue->queueV[queue->pointer++]; 
	}
	else{
		return NULL;
	}
}

/*
* Desalocação da fila
*/
void destroyQueue(QUEUE *queue){
	
	free(queue->queueV);	
	free(queue);
}

/*Busca em largura no grafo dado um vértice inicial*/
void bfs(GRAPH *graph, VERTEX *vertex){

	int i;
	VERTEX *v;
	VERTEX *y;
	EDGE **listEdge;

	/*Recebendo uma fila vazia*/
	QUEUE *queue = createQueue(nVertex(graph));	
	
	/*Enfileirando o vértice*/
	toqueue(queue,vertex);	

	/*Mudando o rótulo do vértice para descoberto*/
	setLabelVertex(vertex,DISCOVERED);	
	
	/*Criação dos pais dos vértices*/
	PARENT *parent  = createParent(graph);

	/*O primeiro vértice não possui pai*/
	insertParent(parent,vertex,NULL);	

	/*Executando a busca em largura*/
	/*Enquanto existir vértices na fila, o algoritmo irá executar*/
	while(queue->n != queue->pointer){
		
		/*Desenfileirando o vértice a ser manipulado*/	
		v = dequeue(queue);
		
		/*Processando o vértice*/
		processVertex(v);

		/*O vértice passa a ser explorado*/
		setLabelVertex(v,EXPLORED);

		/*Recebendo uma lista de arestas incidentes no vértice*/
		listEdge = incidentEdge(graph,v);
		
		/*Enquanto houver arestas a busca por vértices irá continuar*/
		i = 0;
		while(listEdge[i++] != NULL){
			
			/*Recebendo o vértice oposto*/
			y = opposite(graph,v,listEdge[i-1]);

			/*Verificando o rótulo do vértice*/		
			if(getLabelVertex(y) == NODISCOVERED){
				/*Enfileirar o vértice*/
				toqueue(queue,y);

				/*Mudar seu rótulo para descoberto*/
				setLabelVertex(y,DISCOVERED);

				/*Armazena o pai do vértice*/
				insertParent(parent,y,v);

				/*Processando a aresta
				processEdge(listEdge[i-1]);*/

				/*Alterando o rótulo da aresta*/
				setLabelEdge(listEdge[i-1],DISCOVERED);			
			}
			else if(getLabelVertex(y) == DISCOVERED){
				/*Processando a aresta
				processEdge(listEdge[i-1]);*/

				/*Alterando o rótulo da aresta*/
				setLabelEdge(listEdge[i-1],CROSSING);
			}
		}
		
		/*Desalocando a lista de arestas incidentes no vértice*/
		free(listEdge);
	}

	/*Desalocando*/
	destroyQueue(queue);
	destroyParent(parent);
}
