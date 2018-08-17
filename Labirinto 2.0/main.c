#include <stdio.h>
#include "graph.h"

#define N 15
#define M 15

int main(void) {
    int i, j;
    int row, col;
    int inicio, fim;
    
    int labirinto[N][M];
    int indices[N][M];
    Graph* grafo = createGraph();
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            labirinto[i][j] = 1;
        }
    }
    
    scanf("%d", &row);
    scanf("%d", &col);
    
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            scanf("%d", &labirinto[i][j]);
            indices[i][j] = insertVertex(grafo,labirinto[i][j]);
        }
    }
    
    /* IMPLEMENTAR: LIGAÇÃO OS VÉRTICES QUE REPRESENTAM POSIÇÕES VÁLIDAS */
    for(i=0;i<row;i++){
       for(j=0;j<col-1;j++){
	    insertEdge(grafo,indices[i][j],indices[i][j+1],-1);
	}	
    }	
    
    for(i=0;i<col;i++){
       for(j=0;j<row-1;j++){
	    insertEdge(grafo,indices[j][i],indices[j+1][i],-1);
	}	
    }	

    scanf("%d", &inicio);
    scanf("%d", &fim);
    
    bfs_labirinto(grafo, inicio, fim);
    
	eraseGraph(grafo);
	
	return 0;
}
