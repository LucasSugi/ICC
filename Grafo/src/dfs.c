/*
* Algoritmo responsável por realizar a busca em profundidade em um grafo
* São implementadas a busca utilizando recursividade e uma pilha
* author Sugi
*/

#include "grafo.h"
#include "parent.h"
#include <stdio.h>
#include <stdlib.h>

#define EXPLORED 0
#define DISCOVERED 1
#define NODISCOVERED -1
#define CROSSING 0

/*Estrutura da pilha*/
typedef struct stack{

	VERTEX **stackVertex;
	EDGE ***listEdge;
	int *pos;
	int top;

} STACK;

/*Empilha um vértice*/
void stacking(STACK *stack, VERTEX *vertex){
	stack->stackVertex[stack->top++] = vertex;
}

/*Desempilha um vértice*/
VERTEX *pops(STACK *stack){
	return stack->stackVertex[--stack->top];
}

/*Retorna o último vértice*/
VERTEX *pop(STACK *stack){
	if(stack->top > 0)return stack->stackVertex[stack->top-1];
}

/*Criação da pilha*/
STACK *createStack(GRAPH *graph){
	
	int i;
	
	/*Alocando a estrutura*/
	STACK *stack = (STACK*) malloc(sizeof(STACK));
	
	/*Criando o vetor de referências*/
	stack->stackVertex = (VERTEX**) malloc(sizeof(VERTEX*) * nVertex(graph) );
	
	/*Criando o vetor de lista de arestas*/
	stack->listEdge = (EDGE***) malloc(sizeof(EDGE**) * nVertex(graph) );
	stack->pos = (int*) malloc(sizeof(int) * nVertex(graph));

	/*Inicialmente não há vértices na pilha*/
	for(i=0;i<nVertex(graph);i++){
		stack->pos[i] = 0;
	}
	stack->top = 0;
}

/*Desaloca a pilha da memória*/
void destroyStack(STACK *stack){
	free(stack->stackVertex);
	free(stack->listEdge);
	free(stack->pos);
	free(stack);
}

/*Busca em profundidade usando recursividade*/
void dfsRecursion(GRAPH *graph, VERTEX* vertex){
	
	PARENT *parent;
	VERTEX *v;	
	EDGE **listEdge;
	int i = 0;

	/*Mudando o rótulo do vértice*/
	setLabelVertex(vertex,DISCOVERED);
	
	/*Processando o vértice*/
	processVertex(vertex);
	
	/*Criação da estrutura que conterá os pais dos vértices*/
	parent = createParent(graph);

	/*Recebendo uma lista de arestas incidentes no vértice*/
	listEdge = incidentEdge(graph,vertex);

	/*Enquanto houver arestas incidentes o laco ira continuar*/
	while(listEdge[i++] != NULL){
		
		/*Recebendo o vértice oposto da aresta*/
		v = opposite(graph,vertex,listEdge[i-1]);

		/*Verificando o rótulo do vértice*/
		if(getLabelVertex(v) == NODISCOVERED){
			/*Armazenando o pai do vértice*/
			insertParent(parent,v,vertex);
			
			dfsRecursion(graph,v);
		}
		else if(getLabelVertex(v) == DISCOVERED){
			/*Processando o vértice*/
			//processEdge(listEdge[i-1]);
		}
	}

	/*Mudando o rótulo do vértice*/
	setLabelVertex(v,EXPLORED);

	/*Desalocando*/
	destroyParent(parent);
	free(listEdge);
}



/*Busca em profundidade usando pilha*/
void dfsStack(GRAPH *graph, VERTEX* vertex){
	
	VERTEX *v;
	STACK *stack;

	/*Recebendo uma pilha*/
	stack = createStack(graph);
		
	/*Empilhando o vértice*/
	stacking(stack,vertex);
		
	/*Processando o vértice*/
	processVertex(vertex);
	
	/*Mudando o rótulo do vértice*/
	setLabelVertex(vertex,DISCOVERED);
	
	/*Recendo a lista de arestas incidentes no vértice*/
	stack->listEdge[stack->top-1] = incidentEdge(graph,vertex);

	/*Enquanto houver vértices na pilha o laco deve continuar*/
	while(stack->top > 0){
		
		/*Enquanto houver arestas a execucao do laco de continuar*/
		while(stack->listEdge[stack->top-1][stack->pos[stack->top-1]++] != NULL){
			
			/*Vértice oposto*/
			v = opposite(graph,vertex,stack->listEdge[stack->top-1][stack->pos[stack->top-1]-1]);

			/*Verificando o rótulo do vértice oposto*/
			if(getLabelVertex(v) == NODISCOVERED){
				/*Empilhando*/
				stacking(stack,v);	

				/*Processando o vértice*/
				processVertex(v);

				/*Mudando o rótulo*/
				setLabelVertex(v,DISCOVERED);
			
				/*Recebendo nova lista de arestas incidentes no vértice*/
				stack->listEdge[stack->top-1] = incidentEdge(graph,v);

				/*Alterando o vértice*/
				vertex = v;
			}
			else if( getLabelVertex(v) == DISCOVERED){
				/*Processa a aresta*/
				//processEdge(stack->listEdge[stack->top-1][stack->pos[stack->top-1]]);
			}
		}
		
		/*Desalocando a lista*/
		free(stack->listEdge[stack->top-1]);
	
		/*Arrumando a pilha*/
		stack->pos[stack->top-1] = 0;
	
		/*Desempilha*/
		pops(stack);

		/*Retorna o vértice*/
		vertex = pop(stack);
	}

	/*Desalocando*/
	destroyStack(stack);
}

