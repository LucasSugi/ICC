/*
* Algoritmo responsável por conter as referências para os pais dos vértices
* author Sugi
*/

#include "parent.h"
#include <stdlib.h>

/*Estrutura que irá conter os pais dos vértices*/
struct parent{

        VERTEX **listVertex;
        VERTEX **parent;

};

/*
*  Criação da estrutura que irá armazenar os pais dos vértices
*/
PARENT *createParent(GRAPH *graph){

        /*Alocando*/
        PARENT *parent = (PARENT*) malloc(sizeof(PARENT));

        /*Criando a lista*/
        parent->parent = (VERTEX**) malloc(sizeof(VERTEX*) * nVertex(graph));
                 
	/*Recebendo a lista de vértices do grafo*/
        parent->listVertex = vertices(graph);
}

/*
* Desalocando a lista de pais dos vértices
*/

void destroyParent(PARENT *parent){
 
        free(parent->parent);
        free(parent->listVertex);
        free(parent);
}

/*
* Inserindo o pai do vértice
*/
void insertParent(PARENT *parent, VERTEX *v1, VERTEX *v2){

        int i = 0;

        /*Procurando a posição do filho*/
        while(parent->listVertex[i] != v1){
                i++;
        }       

        /*Armazenando o pai no lugar correto*/
        parent->parent[i] = v2;
}
