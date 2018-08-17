#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"

void swap(int *vector, int i, int j){
	int aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

int *produce_asc_vector(int n){

	int i;
	int *vector = (int*) malloc(sizeof(int) * n);

	for(i=0;i<n;i++){
		vector[i] = i + 1;
	}

	return vector;
}

int *produce_desc_vector(int n){

	int i;
	int *vector = (int*) malloc(sizeof(int) * n);
	
	for(i=0;i<n;i++){
		vector[i] = n - i;
	}
	
	return vector;
}

int *produce_random_vector(int n){
	
	int i,new_pos;
	int *vector = produce_asc_vector(n); 
	
	srand(time(NULL));

	for(i=0;i<n;i++){
		new_pos = (int) (rand() % n);
		swap(vector,i,new_pos);	
	}
	
	return vector;
}

void print_vector(int *vector, int n){

	int i;

	for(i=0;i<n;i++){
		printf("%d\n",vector[i]);	
	}
}
