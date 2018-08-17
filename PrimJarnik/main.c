#include <stdio.h>
#include "graph.h"

int main(void) {
    	
	int n, counter = 0, op, vertice;
	double latitute,longitude;

	//Criação do grafo
	Graph* grafo = createGraph();

	//Leitura do número de cidades
	scanf("%d",&n);
   	
	//Leitura das n cidades	
       	while(counter++<n){	
		//Leitura das coordendas
		scanf("%d %lf %lf",&vertice,&latitute,&longitude);
		insertVertex(grafo,latitute,longitude,vertice);	
	}
   	
	//Leitura da opção
	scanf("%d",&op);

	//Execução do algoritmo PrimJarnik
	PrimJarnik(grafo,vertice-1,op);

   	//Desalocando grafo 
	eraseGraph(grafo);
	
	return 0;
}
