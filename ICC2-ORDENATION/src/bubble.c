#include "bubble.h"
#include "utils.h"

void bubble(int *vector, int n){
	
	int i,j;
	
	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if(vector[j] > vector[j+1]){
				swap(vector,j,j+1);
			}	
		}
	}
}
