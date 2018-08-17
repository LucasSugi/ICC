#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void counting(int *vector, int n){

	int *aux  = NULL, *res = NULL;
	int i,min,max,aux_size;

	min = INT_MAX;
	max = INT_MIN;

	for(i=0;i<n;i++){
		if(vector[i] < min) min = vector[i];
		if(vector[i] > max) max = vector[i];
	}

	aux_size = (max-min+1);
	
	aux = (int*) calloc(aux_size,sizeof(int));

	for(i=0;i<n;i++){
		aux[vector[i]-min]++;
	}
	
	for(i=1;i<aux_size;i++){
		aux[i] += aux[i-1];		
	}
	
	res = (int*) malloc(sizeof(int) * n);

	for(i=0;i<n;i++){
		res[--aux[vector[i]-min]] = vector[i];
	}
	
	memcpy(vector,res,n*sizeof(int));

	free(aux);	
	free(res);
}
