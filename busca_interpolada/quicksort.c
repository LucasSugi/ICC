#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

// p(n) = a*n + b
//
// n = right - (left+1) + 1
// a = c4 + c5 + c6 + c7
// b = c1 + c2 + c3 + c7 + c8
int partition(int *vector, int left, int right) {	// c1	24 bytes
	int i, j;					// c2	8 bytes

	i = left;					// c3
	for (j = left+1; j <= right; j++) { 		// c4
		if (vector[j] < vector[left]) {		// c5
			++i;				// c6
			swap(vector, i, j);		// c7
		}
	}
	swap(vector, left, i);				// c7

	return i;					// c8
}

// vetor
// 	
// 	1 2 3 4 5
// 	1|2 3 4 5
// 	1|2|3 4 5
// 	1|2|3|4 5
// 	1|2|3|4|5
//
void quicksort(int *vector, int start, int end) {	// 24 bytes
	int q;						// 4 bytes

	if (start > end) return;
	q = partition(vector, start, end);
	quicksort(vector, start, q-1);
	quicksort(vector, q+1, end);
}








