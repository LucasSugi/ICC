#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quicksort.h"

#define N 1000000000

int *produce_vector(int n){
	
	int i;
	int *vector = (int*) malloc(sizeof(int) * n);

	for(i=0;i<n;i++){
		vector[i] = i;
	}
	
	return vector;
}

int interpolation(int *vector, int start, int end, int key){

	int shattering;

	if(start>end) return -1;
	if(key < vector[start] || key > vector[end]) return -1;
	
	shattering = start + ((key - vector[start]) / (1.0*(vector[end] - vector[start]))) * (end-start);

	if(key == shattering){
		return shattering;
	}
	else if(key > vector[shattering]){
		interpolation(vector,shattering+1,end,key);
	}
	else if(key < vector[shattering]){
		interpolation(vector,start,shattering-1,key);
	}
}

int main(int argc, char *argv[]){


	int *vector = NULL;
	int key,found;

	vector = produce_vector(N);

//	quicksort(vector,0,N-1);
		
	printf("Digite uma chave\n");
	scanf("%d",&key);
	found = interpolation(vector,0,N-1,key);
	printf("Encontrei a chave: %d\n",found);

	free(vector);

	return 0;
}
