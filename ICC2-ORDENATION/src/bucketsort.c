#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <float.h>
#include "insertion.h"

#define EPSILON 1e-7

typedef struct {

	int *pointer;
	int n;

} NODE;

void bucketsort(int *vector, int n, int nbuckets){

	double real_key;
	double min,max;
	int i, bk, offset = 0;

	min = DBL_MAX;
	max = DBL_MIN;

	for(i=0;i<n;i++){
		if(vector[i] > max) max = vector[i];
		if(vector[i] < min) min = vector[i];
	}

	NODE *bucket = (NODE*) calloc(nbuckets,sizeof(NODE));

	max += EPSILON;
	for(i=0;i<n;i++){
		real_key = (vector[i] - min)/(max - min);
		bk = (int) (real_key * nbuckets);
		bucket[bk].pointer = (int*) realloc(bucket[bk].pointer, sizeof(int) * (bucket[bk].n + 1));
		bucket[bk].pointer[bucket[bk].n] = vector[i];
		bucket[bk].n++;
	}

	for(i=0;i<nbuckets;i++){
		if(bucket[i].n > 0){
			insertion(bucket[i].pointer,bucket[i].n);
		}
	}
	
	for(i=0;i<nbuckets;i++){
		memcpy(vector+offset,bucket[i].pointer,sizeof(int) * bucket[i].n);
		offset += bucket[i].n;
	}

	for(i=0;i<nbuckets;i++){
		if(bucket[i].pointer != NULL){
			free(bucket[i].pointer);
		}
	}
	free(bucket);
}
