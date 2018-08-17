#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int *vector, int start, int middle, int end){

	int i,j,k;
	int *left, *right;
	int nleft, nright;

	nleft = middle - start + 2;
	nright =  end - middle + 1;
	left = (int*) malloc(sizeof(int)*nleft);
	right = (int*) malloc(sizeof(int)*nright);
	
	for(i=0;i<nleft-1;i++){
		left[i] = vector[start+i];
	}
	left[i] = INT_MAX;

	for(i=0;i<nright-1;i++){
		right[i] = vector[i+middle+1];
	}
	right[i] = INT_MAX;

	i = j = 0;

	for(k=start;k <= end ; k++){
		if( left[i] <= right[j]){
			vector[k] = left[i++];
		} else {
			vector[k] = right[j++];
		}
	}

	free(left);
	free(right);

}

void mergesort(int *vector, int start, int end){

	int middle;

	if(start < end){
		middle = (start + end) / 2;	
	
		mergesort(vector,start,middle);	
		mergesort(vector,middle+1,end);
		merge(vector,start,middle,end);
	}
}
