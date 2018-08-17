#include <stdio.h>
#include "graph.h"

int main(int argc, char *argv[]){
	
	GRAPH *graph = createGraph();

	VERTEX *v1 = insertVertex(graph,1);
	VERTEX *v2 = insertVertex(graph,2);
	VERTEX *v3 = insertVertex(graph,3);
	VERTEX *v4 = insertVertex(graph,4);
	VERTEX *v5 = insertVertex(graph,5);
	VERTEX *v6 = insertVertex(graph,6);
	VERTEX *v7 = insertVertex(graph,7);
	
	EDGE *e = insertEdge(graph,v1,v2,0);
	insertEdge(graph,v1,v3,0);
	insertEdge(graph,v1,v7,0);
	insertEdge(graph,v2,v4,0);
	insertEdge(graph,v2,v5,0);
	insertEdge(graph,v3,v5,0);
	insertEdge(graph,v3,v6,0);
	insertEdge(graph,v4,v5,0);
	insertEdge(graph,v5,v6,0);
	insertEdge(graph,v3,v7,0);
	insertEdge(graph,v6,v7,0);
	
	removeVertex(graph,v3);	
	removeEdge(graph,e);	
	
	removeGraph(graph);

	return 0;
}
