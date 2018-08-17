#include "insertion.h"

void insertion(int *vector, int n){

	int i,j,key;

	for(j=1;j<n;j++){
		key = vector[j];
		i = j-1;
		
		while(i>=0 && vector[i] > key){
			vector[i+1] = vector[i];	
			i--;
		}		
		vector[i+1] = key;
	}
}
