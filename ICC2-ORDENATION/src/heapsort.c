#include "heapsort.h"
#include "utils.h"

#define left_child(id) id*2 + 1
#define right_child(id) id*2 + 2

void max_heapify(int *vector, int position, int n){

	int largest = position;
	int left = left_child(position);
	int right = right_child(position); 

	if(left<n && vector[left] > vector[largest]){
		largest = left;
	}
	if(right<n && vector[right] > vector[largest]){
		largest = right;
	}

	if(largest != position){
		swap(vector,position,largest);
		max_heapify(vector,largest,n);
	}
}

void build_max_heap(int *vector,int n){

	int i;

	for(i=(n/2)-1;i>=0;i--){
		max_heapify(vector,i,n);	
	}
}

void heapsort(int *vector, int n){
	
	int i;

	build_max_heap(vector,n);

	for(i=n-1;i>=1;i--){
		swap(vector,i,0);
		max_heapify(vector,0,i);
	}	
}
