#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include <limits.h>

#define MAX_VERTICES 1000
#define MAX_EDGES 10000

#define FALSE 0
#define TRUE 1

#define FORA 0
#define DENTRO 1

typedef struct fila{

	int *filaV;
	double *dist;
	int n;
	int size;

} FILA;

typedef struct parent{
	
	int *p1;
	int *p2;
	double *pDist;
	int n;

} PARENT;

/* Vertex */
struct vertex {
    /* marcador que indica se o vértice está sendo usado (used == TRUE) ou não
    ** (used==FALSE) */
    int used;
    /* objeto armazenado pelo vértice */
	double value1;
	double value2;
	double value3;
	double dist;
	int rotulo;
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
    double value;
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
int insertVertex(Graph* g, double o, double u, double t) {
    int i;
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == FALSE) break;
    }
    
    if (i < MAX_VERTICES) {
        g->n_vertices++;
        g->vertices[i].value1 = o;
        g->vertices[i].value2 = u;
        g->vertices[i].value3 = t;
        g->vertices[i].used = TRUE;
    } else {
        printf("ERRO: Número máximo de vértices já foi atingido!\n");
    }
    return i;
}

/* Função para adicionar uma aresta não direcionada ao grafo */
int insertEdge(Graph* g, int v, int w, double o) {
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
void replaceVertex(Graph* g, int v, double o, double u) {
    g->vertices[v].value1 = o;
    g->vertices[v].value2 = u;
}

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(Graph* g, int e, double o) {
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
    return 1;
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
            printf("%d %lf %lf\n", i, g->vertices[i].value1,g->vertices[i].value2);
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
                printf("%d %d %d %lf\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %lf\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
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
            printf("%d %lf %lf\n", i, g->vertices[i].value1,g->vertices[i].value2);
    }
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("%d %d %d %lf\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %lf\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
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

int *vertices(Graph *g){

	int i,j;
	int *listV = NULL;
		
	//Criação da estrutura que conterá todos os vértices
	listV = (int*) malloc(sizeof(int) * g->n_vertices);
	
	j = 0;
	for(i=0;i<MAX_VERTICES;i++){
		if(g->vertices[i].used == TRUE){
			listV[j++] = i;			
		}
	}

	return listV;
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

//Atualização da fila
void sortFila(FILA *fila){
	
	double aux;
	int n = fila->size;
	int i,j;

	for(i=1;i<n;i++){
		for(j=0;j<n-1;j++){
			if(fila->dist[j] > fila->dist[j+1]){
				aux = fila->dist[j];			
				fila->dist[j] = fila->dist[j+1];
				fila->dist[j+1] = aux;

				aux = fila->filaV[j];
				fila->filaV[j] = fila->filaV[j+1];
				fila->filaV[j+1] = aux;
			}	
		}
	}
}

//Criação da fila de prioridade
FILA *criarFila(Graph *g){
	
	FILA *fila = (FILA*) malloc(sizeof(FILA));
	fila->filaV = (int*) malloc(sizeof(int) * g->n_vertices);
	fila->dist = (double*) malloc(sizeof(double) * g->n_vertices);
	fila->n = 0;
	fila->size = g->n_vertices;

	return fila;
}

//Desalocando fila de prioridade
void desalocarFila(FILA *fila){

	free(fila->filaV);
	free(fila->dist);
	free(fila);
}

//Adicionar um elemento na fila de prioridade
void add(FILA *fila, int v, double dist, int i){
	fila->filaV[i] = v;
	fila->dist[i] = dist;
}

//Atualização da distância do vértice armazenada na fila
void replace(FILA *fila, double dist, int i){

	int j;
	
	//Procura pela referência no vértice e atualiza a distância	
	for(j=0;j<fila->size;j++){
		if(fila->filaV[j] == i){
			fila->dist[j] = dist;
			break;	
		} 	
	}

	sortFila(fila);
}

//Remoção lógica de um vértice da fila
int remover(FILA *fila){
 	
	int ret;

	fila->n++;
	ret = fila->filaV[0];
	fila->dist[0] = INT_MAX;
	sortFila(fila);
	return ret;
}

//Criação da estrutura que armazena os pais dos vértices
PARENT *createParent(Graph *g){

	int i;
	
	//Alocação	
	PARENT *parent = (PARENT*) malloc(sizeof(PARENT));
	parent->p1 = (int*) malloc(sizeof(int) * g->n_vertices);
	parent->p2 = (int*) malloc(sizeof(int) * g->n_vertices);
	parent->pDist = (double*) malloc(sizeof(double) * g->n_vertices);
	parent->n = g->n_vertices;		
	
	//Inicialização	
	for(i=0;i<g->n_vertices;i++){
		parent->p1[i] = -1;
		parent->p2[i] = -1;
		parent->pDist[i] = 0;
	}

	return parent;
}

//Desalocando estrutura de pais dos vértices
void desalocaParent(PARENT *parent){
	free(parent->p1);
	free(parent->p2);
	free(parent->pDist);
	free(parent);
}

//Adicionando vértices a estrutura
void addParent(PARENT *parent, int vertice1, int vertice2, int z, double dist){
	
	//Os pares já são inseridas de maneira ordenada
	if(vertice2 > vertice1){
		parent->p1[z] = vertice1;
		parent->p2[z] = vertice2;
		parent->pDist[z] = dist;
	}else{
		parent->p1[z] = vertice2;
		parent->p2[z] = vertice1;
		parent->pDist[z] = dist;
	}
}

//Impressão da soma das arestas da árvore geradora mínima
void printTotalDist(PARENT *parent){

	int  i;
	double total = 0;

	for(i=0;i<parent->n;i++){
		total += parent->pDist[i]; 			
	}	

	printf("%.3lf\n",total);
}

//Função auxiliar responsável por trocar os vértices
void swap(PARENT *parent, int i, int j){
	
	int aux = parent->p1[i];
	parent->p1[i] = parent->p1[j];
	parent->p1[j] = aux;
	
	aux = parent->p2[i];
	parent->p2[i] = parent->p2[j];
	parent->p2[j] = aux;
}

//Ordenação do vetor de pais dos vértices
void sortParent(PARENT *parent){
	
	int i,j;
	int n;

	n = parent->n;

	for(i=1;i<n;i++){
		for(j=0;j<n-1;j++){
			if(parent->p1[j] > parent->p1[j+1]){
				swap(parent,j,j+1);	
			}
			else if(parent->p1[j] == parent->p1[j+1]){
				if(parent->p2[j] > parent->p2[j+1]){
					swap(parent,j,j+1);
				}	
			}	
		}
	}
}

//Impressão dos pares de vértices da árvore geradora mínima
void printParent(PARENT *parent){
	
	int i;
	
	for(i=0;i<parent->n;i++){
		if(parent->p1[i] != -1){
			printf("%d %d\n",parent->p1[i],parent->p2[i]);
		}
	}
}

//Execução do algoritmo PrimJarnik para procurar pela árvore geradora mínima
void PrimJarnik(Graph* g, int v, int op) {
	
	int u,z;
	int i,j,counter = 0;
	int *listV = NULL, *listEdge = NULL;
	double v1,v2,w1,w2,d;
	FILA *fila;
	PARENT *parent = NULL;

	//Recebe uma fila de prioridade vazia		
	fila = criarFila(g);	
	
	//Recebe uma lista com as referências para todos os vértices
	listV = vertices(g);

	//Vetor de pais dos vértices
	parent = createParent(g);
	
	//Criação das aretas do grafo
	for(i=0;i<g->n_vertices;i++){
		v1 = g->vertices[listV[i]].value1;
		v2 = g->vertices[listV[i]].value2;

		for(j=i+1;j<g->n_vertices;j++){
			w1 = g->vertices[listV[j]].value1;
			w2 = g->vertices[listV[j]].value2;
			//Calculo da distancia
			d = sqrt((v1-w1)*(v1-w1) + (v2-w2)*(v2-w2));
			//Insercao da aresta
			insertEdge(g,listV[i],listV[j],d);
		}
	}	

	//Inicialmente todos os vértices possuem distância infinita e estao fora da nuvem 
	for(i=0;i<g->n_vertices;i++){
		g->vertices[listV[i]].dist = INT_MAX;
		g->vertices[listV[i]].rotulo = FORA;
		//Inserção na fila de prioridade
		add(fila,listV[i],INT_MAX,i);
		
	}
	//O vértice inicial tem distância zero
	g->vertices[v].dist = 0;
	replace(fila,0,v);	
	
	//Enquanto houver vértices na fila de prioridade rode
	while(fila->n != g->n_vertices){
		u = remover(fila);		
		g->vertices[u].rotulo = DENTRO;

		//Arestas incidentes de u
		listEdge = incidentEdge(g,u);
		
		//Enquanto houver arestas incidentes rode
		while(listEdge[counter++] != -1){
			z = opposite(g,u,listEdge[counter-1]);
			
			//Verifica se a distância da aresta precisa de atualização	
			if(g->vertices[z].rotulo == FORA && g->vertices[z].dist > g->edges[listEdge[counter-1]].value){
				g->vertices[z].dist = g->edges[listEdge[counter-1]].value;
				replace(fila,g->edges[listEdge[counter-1]].value,z);
				addParent(parent,g->vertices[z].value3,g->vertices[u].value3,z,g->vertices[z].dist);
			}	
		}

		//Desalocando lista de arestas incidentes
		free(listEdge);
		counter = 0;
	}
	
	//Verificando qual o tipo de opção selecionada	
	if(op == 1){
		sortParent(parent);	
		printParent(parent);
	}
	else{
		printTotalDist(parent);	
	}

	//Desalocar todas as estruturas 
	desalocarFila(fila);
	desalocaParent(parent);
	free(listV);
}
