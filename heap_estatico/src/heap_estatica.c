#include <stdio.h>
#include <stdlib.h>

#include "heap_estatica.h"

#define TAM 100

//Construção de uma max_heapfy

struct heap_estatica{

	ITEM *vetor[TAM];
	int fim;
};

HEAP_ESTATICA *criar_heap(){
	
	HEAP_ESTATICA *heap = (HEAP_ESTATICA*) malloc(sizeof(HEAP_ESTATICA));
	if(heap != NULL){
		heap->fim = -1;
	}
	return heap;
}

void apagar_heap(HEAP_ESTATICA **heap){

	int i;

	if(heap != NULL && *heap != NULL){
		for(i=0;i<=(*heap)->fim;i++){
			apagar_item(&((*heap)->vetor[i]));
		}
		free(*heap);
	}
}

void swap(HEAP_ESTATICA *heap, int i, int j){

	ITEM *aux = heap->vetor[i];
	heap->vetor[i] = heap->vetor[j];
	heap->vetor[j] = aux;
}

void fix_up(HEAP_ESTATICA *heap, int filho){

	int pai;

	if(filho == 0) return;

	pai = (filho-1)/2;

	if(heap->vetor[filho]->chave > heap->vetor[pai]->chave){
		swap(heap,filho,pai);
		fix_up(heap,pai);
	}
}

int enfileirar(HEAP_ESTATICA *heap, ITEM *item){

	if(!cheia(heap)){
		heap->fim++;
		heap->vetor[heap->fim] = item;
		fix_up(heap,heap->fim);
		return 1;
	}
	return 0;
}

void fix_down(HEAP_ESTATICA *heap, int index){

	int left = 2*index + 1;
	int right = 2*index + 2;
	int largest = index;

	if(left <= heap->fim && heap->vetor[largest]->chave < heap->vetor[left]->chave){
		largest = left;
	}
	if(right <= heap->fim && heap->vetor[largest] < heap->vetor[right]){
		largest = right;
	}

	if(largest != index){
		swap(heap,largest,index);
		fix_down(heap,largest);
	}
}

ITEM *desenfileirar(HEAP_ESTATICA *heap){

	if(!vazia(heap)){
		ITEM *item = heap->vetor[0];
		heap->vetor[0] = heap->vetor[heap->fim];
		heap->fim--;
		fix_down(heap,0);
		return item;
	}
	return NULL;
}

int cheia(HEAP_ESTATICA *heap){
	return heap->fim == TAM - 1;
}

int vazia(HEAP_ESTATICA *heap){
	return heap->fim == -1;
}

int tamanho(HEAP_ESTATICA *heap){
	return heap->fim + 1;
}

void imprimir_heap(HEAP_ESTATICA *heap){

	int i;

	for(i=0;i<=heap->fim;i++){
		imprimir_item(heap->vetor[i]);
	}	
}