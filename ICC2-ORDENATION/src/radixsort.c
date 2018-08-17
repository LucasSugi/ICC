#include <stdlib.h>
#include <string.h>

#define MAX_HEX 0xF+1
#define MAX_DIGIT (sizeof(int) * 8) / 4

int extract_digit(int value, int d){
	return (value >> (4*d)) & 0xF;
}

void radix_counting_sort(int *vector, int n, int digit){

	int i;
	int *Aux, *R;

	Aux = (int*) calloc(MAX_HEX,sizeof(int));
	for(i=0;i<n;i++){
		Aux[extract_digit(vector[i],digit)]++;
	}

	for(i=1;i<MAX_HEX;i++){
		Aux[i] += Aux[i-1];
	}
	
	
	R = (int*) malloc(sizeof(int) * n);
	for(i = n-1;i>=0;i--){
			R[--Aux[extract_digit(vector[i],digit)]] = vector[i];
	}

	memcpy(vector,R,n*sizeof(int));

	free(Aux);
	free(R);	
}

void radixsort(int *vector, int n){

	int i;

	for(i=0;i<MAX_DIGIT;i++){
		radix_counting_sort(vector,n,i);
	}
}
