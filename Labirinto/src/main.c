#include "grafo.h"
#include "bfs.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	int n,m,vertice,start,end, counter;
	int Istart,Jstart,Iend,Jend;
	int i,j;

	/*Criação do grafo*/	
	GRAPH *graph = createGraph();
	
	/*Leitura do tamanho do labirinto*/
	scanf("%d",&n);	
	scanf("%d",&m);

	/*Vetor de vértices*/
	VERTEX ***v = (VERTEX***) malloc(sizeof(VERTEX**) * n); 
	for(i=0;i<n;i++){
		v[i] = (VERTEX**) malloc(sizeof(VERTEX*) * m);
	}
	
	/*Lendo o labirinto*/
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%d",&vertice);
			/*Criando os vértices*/
			v[i][j] = insertVertex(graph,vertice);
		}
	}
	
	/*Leitura do ponto de partida*/
	scanf("%d",&start);

	/*Leitura do final*/
	scanf("%d",&end);

	/*Cálculo da posição do início do vértice*/
	counter = 0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(counter == start){
				Istart = i;
				Jstart = j;
				i = n;
				break;
			}	
			counter++;
		}
	}

	/*Cálculo da posição do fim do vértice*/
	counter = 0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(counter == end){
				Iend = i;
				Jend = j;
				i = n;
				break;
			}
			counter++;
		}
	}
	
	/*Criando as arestas nas horizontais*/	
	for(i=0;i<n;i++){
		for(j=0;j<m-1;j++){
			insertEdge(graph,v[i][j],v[i][j+1],0);
		}
	}	
	/*Criando as arestas nas verticais*/	
	for(i=0;i<m;i++){
		for(j=0;j<n-1;j++){
			insertEdge(graph,v[j][i],v[j+1][i],0);
		}
	}
	
	/*Busca no gráfica para achar o menor caminho*/
	//bfs(graph,v[Istart][Jstart],v[Iend][Jend]);	
	
	/*Desalocando*/
	for(i=0;i<n;i++){
		free(v[i]);
	}
	free(v);
	
	/*Remoção do grafo*/
	removeGraph(graph);
	
	printf("ok\n");

	return 0;
}
