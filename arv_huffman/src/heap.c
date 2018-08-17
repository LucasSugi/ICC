#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 100

struct heap{
	
	NO *vetor[TAM];
	int fim;
};

HEAP *criar_heap(){

	HEAP *heap = (HEAP*) malloc(sizeof(HEAP));

	if(heap != NULL){
		heap->fim = -1;
	}

	return heap;
}

void apagar_heap(HEAP **heap){
	free(*heap);
}

void swap(HEAP *heap, int i, int j){

	NO *swap = heap->vetor[i];
	heap->vetor[i] = heap->vetor[j];
	heap->vetor[j] = swap;
}

void fix_up(HEAP *heap, int filho){

	if(filho == 0) return;
	
	int pai = (filho - 1)/2;
		
	if(heap->vetor[pai]->frequencia > heap->vetor[filho]->frequencia){
		swap(heap,pai,filho);
		fix_up(heap,pai);
	}
}

int inserir_heap(HEAP *heap, NO *no){
	
	if(!cheia_heap(heap)){
		heap->vetor[++heap->fim] = no;
		fix_up(heap,heap->fim);
		return 1;
	}
	return 0;
}

void fix_down(HEAP *heap, int index){

	int left = 2*index + 1;
	int right = 2*index + 2;
	int min = index;

	if(left <= heap->fim && heap->vetor[left]->frequencia < heap->vetor[min]->frequencia){
		min = left;
	}
	if(right <= heap->fim && heap->vetor[right]->frequencia < heap->vetor[min]->frequencia){
		min = right;
	}
	if(min != index){
		swap(heap,min,index);
		fix_down(heap,min);
	}
}

NO *remover_heap(HEAP *heap){
	
	NO *no;
	
	if(!vazia_heap(heap)){
		
		no = heap->vetor[0];
		heap->vetor[0] = heap->vetor[heap->fim];
		heap->fim--;
		fix_down(heap,0);
		return no;
	}
	return NULL;
}

int cheia_heap(HEAP *heap){
	return heap->fim == TAM - 1;
}

int vazia_heap(HEAP *heap){
	return heap->fim == - 1;
}

int tamanho_heap(HEAP *heap){
	return heap->fim + 1;
}
