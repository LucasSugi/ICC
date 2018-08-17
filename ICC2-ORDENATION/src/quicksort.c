#include "quicksort.h"
#include "utils.h"

int partition(int *vector,int left, int right){
	
	int i,j;
	
	i = left;
	for(j =left+1;j<=right;j++){
		if(vector[j] < vector[left]){
			i++;
			swap(vector,i,j);
		}
	}
	swap(vector,left,i);
	
	return i;
}


void quicksort(int *vector,int start, int end){
	
	int q;

	if(start>end) return;
	q = partition(vector,start,end);
	quicksort(vector,start,q-1);
	quicksort(vector,q+1,end);
}
