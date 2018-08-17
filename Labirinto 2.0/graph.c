#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
//#include "fila.h"

#define MAX_VERTICES 1000
#define MAX_EDGES 10000

#define FALSE 0
#define TRUE 1

#define DESCOBERTO 1
#define NAODESCOBERTO -1
#define EXPLORADO 0

typedef struct fila{

	int *fila;	
	int topo;
	int inicio;

} FILA;


/* Vertex */
struct vertex {
    /* marcador que indica se o vértice está sendo usado (used == TRUE) ou não
    ** (used==FALSE) */
    int used;
   	int rotulo; 
    /* objeto armazenado pelo vértice */
	int value;
};

/* Edge */
struct edge {
    /* marcador que indica se a aresta está sendo usada (used == TRUE) ou não
    ** (used == FALSE) */
    int used;
    
    /* primeiro vértice da aresta */
    int v1;
    
    /* segundo vértice da aresta */
    int v2;
    
    /* objeto armazenado pela aresta */
    int value;
};

/* Graph
** implementado utilizando-se a estrutura: LISTA DE ARESTAS */
struct graph {
    /* vetor estático que armazena os vértices */
    Vertex vertices[MAX_VERTICES];
    
    /* vetor estático que armazena as arestas */
    Edge edges[MAX_EDGES];
    
    /* armazena o número de vértices e o número de arestas do grafo*/
    int n_vertices, n_edges;
};

/* Cria um grafo */
Graph* createGraph(void) {
    int i, j;
    Graph* g;
    
    /* Aloca dinamicamente um grafo que é retornado para o usuário */
    g = (Graph*) malloc(sizeof(Graph));

    /* Marca todos os vértices como livres (i.e., não utilizadas) */
    for (i = 0; i < MAX_VERTICES; i++) { 
	g->vertices[i].used = FALSE; 
	g->vertices[i].rotulo = NAODESCOBERTO;
     }
    
    /* Marca todas as arestas como livres (i.e., não utilizadas) */
    for (j = 0; j < MAX_EDGES; j++) { g->edges[j].used = FALSE; }
    
    g->n_vertices = 0;
    g->n_edges = 0;
    
    return g;
}

/* Apaga um grafo */
void eraseGraph(Graph* g) {
    /* Libera o espaço em memória alocado pela função createGraph() */
    free(g);
}

/* Função para adicionar um vértice ao grafo */
int insertVertex(Graph* g, int o) {
    int i;
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == FALSE) break;
    }
    
    if (i < MAX_VERTICES) {
        g->n_vertices++;
        g->vertices[i].value = o;
        g->vertices[i].used = TRUE;
    } else {
        printf("ERRO: Número máximo de vértices já foi atingido!\n");
    }
    return i;
}

/* Função para adicionar uma aresta não direcionada ao grafo */
int insertEdge(Graph* g, int v, int w, int o) {
    int j;
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == FALSE) break;
    }
    
    if (j < MAX_EDGES) {
        g->n_edges++;
        g->edges[j].v1 = v;
        g->edges[j].v2 = w;
        g->edges[j].value = o;
        g->edges[j].used = TRUE;
    } else {
        printf("ERRO: Número máximo de arestas já foi atingido!\n");
    }
    return j;
}

/* Função para substituir o elemento armazenado no vértice 'v' por 'o' */
void replaceVertex(Graph* g, int v, int o) {
    g->vertices[v].value = o;
}

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(Graph* g, int e, int o) {
    g->edges[e].value = o;
}

/* Função para remover um vértice do grafo */
int removeVertex(Graph* g, int v) {
    int j;
    
    g->vertices[v].used = FALSE;
    g->n_vertices--;
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used != FALSE && (g->edges[j].v1 == v || g->edges[j].v2 == v)) {
            g->edges[j].used = FALSE;
            g->n_edges--;
        }
    }
    return g->vertices[v].value;
}

/* Função para remover uma aresta do grafo */
int removeEdge(Graph* g, int e) {
    g->edges[e].used = FALSE;
    g->n_edges--;
    return g->edges[e].value;
}


/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(Graph* g) {
    return g->n_vertices;
}

/* Função para acessar o número de arestas de um grafo */
int numEdges(Graph* g) {
    return g->n_edges;
}

/* Função para acessar o grau de um vértice de um grafo */
int degree(Graph* g, int v) {
    int j, dg;
    
    dg = 0;
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
             if (g->edges[j].v1 == v) dg++;
             if (g->edges[j].v2 == v) dg++;
        }
    }
    return dg;
}

/* Função para verificar se dois vértices são ou não adjacentes */
int areAdjacent(Graph* g, int v, int w) {
    int j;
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
             if (g->edges[j].v1 == v && g->edges[j].v2 == w) return TRUE;
             if (g->edges[j].v1 == w && g->edges[j].v2 == v) return TRUE;
        }
    }
    return FALSE;
}


/* MÉTODOS DE IMPRESSÃO */

/* ATENÇÃO: Caso o grafo não seja direcionado, as funções de impressão das
   arestas ordenará de forma ascendente os identificadores dos vértices. */

/* Imprime a quantidade de vértices de um grafo seguido de uma lista ordenada
   de forma ascendente pelo identificador de cada vértice contendo os valores
   armazenados nestes, i.e., imprime os pares ordenados (identificador(v), valor(v))*/
void printVertices(Graph* g) {
    int i, num_vertices;
    
    num_vertices = numVertices(g);
    printf("%d\n", num_vertices);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("%d %d\n", i, g->vertices[i].value);
    }
}

/* Imprime a quantidade de arestas de um grafo seguido de uma lista ordenada
   de forma ascendente pelo identificador de cada aresta contendo as tuplas
   (identificador(e), identificador(v1), identificador(v2), valor(e)), onde os
   identificadores de v1 e v2 também são ordenados de forma ascendente caso o
   grafo não seja direcionado */
void printEdges(Graph* g) {
    int j, num_edges;
    
    num_edges = numEdges(g);
    printf("%d\n", num_edges);
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("%d %d %d %d\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %d\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
            }
        }
    }
}

/* Imprime a quantidade de vértices, a quantidade de arestas, a lista de vértices
   e a lista de arestas de um grafo */
void printGraph(Graph* g) {
    int i, j, num_vertices, num_edges;
    
    num_edges = numEdges(g);
    num_vertices = numVertices(g);
    printf("%d\n%d\n", num_vertices, num_edges);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("%d %d\n", i, g->vertices[i].value);
    }
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("%d %d %d %d\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %d\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
            }
        }
    }
}

/* Imprime a quantidade de vértices de um grafo seguido de uma lista ordenada de
   forma ascendente pelo identificador de cada vértice contendo o grau deste, i.e.,
   imprime os pares ordenados (identificador(v), grau(v))*/
void printDegree(Graph* g) {
    int i, dg, num_vertices;
    
    num_vertices = numVertices(g);
    printf("%d\n", num_vertices);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE) {
            dg = degree(g, i);
            printf("%d %d\n", i, dg);
        }
    }
}

/* Imprime TRUE se dois vértices são adjacentes ou FALSE caso contrário */
void printAdjacent(Graph* g, int v, int w) {
    if (areAdjacent(g, v, w)) printf("TRUE\n");
    else printf("FALSE\n");
}

//Criação de uma fila
FILA *criarFila(){

	FILA *fila = (FILA*) malloc(sizeof(FILA));
	
	fila->fila = (int*) malloc(sizeof(int) * 15 * 15);
	fila->topo = 0;
	fila->inicio = 0;

	return fila;
}

//Desalocando a fila
void desalocarFila(FILA *fila){
	free(fila->fila);
	free(fila);
}

//Enfileirando um vértice
void enfileirar(FILA *fila, int v){
	fila->fila[fila->topo] = v;
	fila->topo++;
}

//Desenfileirando um vértice
int desenfileirar(FILA *fila){
	fila->inicio++;
	return fila->fila[fila->inicio-1];
}

//Retorna as arestas incidentes de um vértice
int *incidentEdge(Graph *g, int v){
	
	int i,j;
	int *arestas = (int*) malloc(sizeof(int) * g->n_edges);
	
	//Inicia todas as posições com -1 para indicar que não há uma aresta nessa posição
	for(i=0;i<g->n_edges;i++){
		arestas[i] = -1;
	}
		
	//Verificando quais arestas são adjascentes
	j = 0;	
	for(i=0;i<g->n_edges;i++){
		if(g->edges[i].used == TRUE && (g->edges[i].v1 == v || g->edges[i].v2 == v)){
			arestas[j] = i;
			j++;
		} 
	}

	return arestas;
}

//Retorna o vértice oposto da aresta
int opposite(Graph *g, int v, int e){

	if(g->edges[e].v1 == v){
		return g->edges[e].v2;
	}
	else{
		return g->edges[e].v1;
	}
}

//Procurando o menor caminho
int menorCaminho(int *pai, int v, int w, int contador){
		
	//Armazenando o pai do vértice
	int p = pai[w];
	
	//Aumentando o contador de caminho
	contador++;
	
	//Caso seja encontrado o início o caminho é retornado
	if(p == v){
		return contador;
	}
	//Caso não seja encontrado a função é chamada novamente
	else{
		menorCaminho(pai,v,p,contador);
	}
}

void bfs_labirinto(Graph* g, int v, int w) {
	
	int i;
	int contador = 0, encontrei = 0;
	int *arestas;	
	int vertice, y;
	
	if(v == w){
		printf("0");
		return;
	}
	
	//Criando um vetor que conterá as referências para os pais dos vértices	
	int *pai = (int*) malloc(sizeof(int) * g->n_vertices);
	for(i=0;i<g->n_vertices;i++){
		pai[i] = -1;
	}
	
	//Criar fila
	FILA *fila = criarFila();	
	
	//Enfileira o primeiro vértice
	enfileirar(fila,v);

	//Mudando rótulo do vértice
	g->vertices[v].rotulo = DESCOBERTO;

	while(fila->inicio != fila->topo){
		
		//Desenfileirar
		vertice = desenfileirar(fila);

		//Mudando rotulo
		g->vertices[vertice].rotulo = EXPLORADO;

		//Arestas incidentes
		arestas = incidentEdge(g,vertice);
	
		i = 0;
		while(arestas[i++] != -1){
			
			//Vertice oposto
			y = opposite(g,vertice,arestas[i-1]);	
			
			if(g->vertices[y].rotulo == NAODESCOBERTO && g->vertices[y].value != 1){
				//Mudar rotulo
				g->vertices[y].rotulo = DESCOBERTO;

				//Enfileirar
				enfileirar(fila,y);

				//Armazenando o pai
				pai[y] = vertice;
				
				//Verificando se é o vértice final
				if(y == w && encontrei == 0){
					contador =  menorCaminho(pai,v,w,contador);
					printf("%d\n",contador);
					encontrei = 1;
				}
			}
		}
		
		free(arestas);	
	} 

	if(encontrei == 0) printf("NO EXIT\n");
	
	desalocarFila(fila);
	free(pai);
}
