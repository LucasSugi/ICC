/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */
#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include "item.h"

typedef struct ArrayList ArrayList;

//Cria a ArrayList e aloca toda memória necessária
ArrayList *new_ArrayList();

//Adiciona um elemento na ArrayList
int add_ArrayList(ArrayList *, ITEM *);

//Verifica na ArrayList se existe um elemento com a chave informada
int contains_ArrayList(ArrayList *, int);

//Recupera um item na posição informada
ITEM *get_ArrayList(ArrayList *, int);

//Retorna qual a posição do primeiro elemento com a chave informada
int index_ArrayList(ArrayList *, int);

//Verifica se a ArrayList está vazia
int isEmpty_ArrayList(ArrayList *);

//Remove um elemento da ArrayList
int remove_ArrayList(ArrayList *, int);

//Modifica um elemento da ArrayList
int set_ArrayList(ArrayList *, int, ITEM*);

//Retorna o tamanho do ArrayList
int size_ArrayList(ArrayList *);

//Recupera um novo subArray no intervalo dado
ArrayList *sub_ArrayList(ArrayList *, int, int);

//Desaloca a memória alocada pelo ArrayList
int destruct_ArrayList(ArrayList **);

//Desaloca a memória alocada pela sublist
void destruct_newList(ArrayList **);

//Imprime toda a lista
void print_ArrayList(ArrayList *);

#endif
