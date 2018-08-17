#include "grafo.h"
#include "bfs.h"
#include "dfs.h"

int main(int argc, char* argv[]){
	
	/*Criação do grafo*/	
	GRAPH *graph = createGraph();

	/*Inserção dos vértices*/	
	VERTEX *v1 = insertVertex(graph,1);
	VERTEX *v2 = insertVertex(graph,2);
	VERTEX *v3 = insertVertex(graph,3);
	VERTEX *v4 = insertVertex(graph,4);
	VERTEX *v5 = insertVertex(graph,5);
	VERTEX *v6 = insertVertex(graph,6);
	
	/*Inserção das arestas*/
	insertEdge(graph,v1,v2,1);
	insertEdge(graph,v2,v3,1);
	insertEdge(graph,v3,v4,1);
	insertEdge(graph,v1,v5,1);
	insertEdge(graph,v5,v6,1);
		
	/*Busca em largura*/
	dfsStack(graph,v1);
	
	/*Remoção do grafo*/
	removeGraph(graph);

	return 0;
}
