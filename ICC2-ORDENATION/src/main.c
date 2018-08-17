#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "bubble.h"
#include "insertion.h"
#include "merge.h"
#include "heapsort.h"
#include "quicksort.h"
#include "countingsort.h"
#include "radixsort.h"
#include "bucket.h"

#define TAM 100
#define max(a,b) a > b ? a : b

enum{
	
	BUBBLE,
	INSERTION,
	MERGE,
	HEAPSORT,
	QUICKSORT,
	COUNTING,
	RADIX,
	BUCKET
};

int main(int argc, char *argv[]){

	int option;
	int *vectorAsc = NULL, *vectorDesc = NULL, *vectorRdm = NULL;
	double timeAsc, timeDesc, timeRdm;
	clock_t start, end;

	scanf("%d",&option);

	vectorAsc = produce_asc_vector(TAM);	
	vectorDesc = produce_desc_vector(TAM);	
	vectorRdm = produce_random_vector(TAM);	

	switch(option){
		case BUBBLE: 
			start = clock();
			bubble(vectorAsc,TAM);
			end = clock();
			timeAsc = (end - start) / (CLOCKS_PER_SEC * 1.0);

			start = clock();
			bubble(vectorDesc,TAM);
			end = clock();
			timeDesc = (end - start) / (CLOCKS_PER_SEC * 1.0);

			start = clock();
			bubble(vectorRdm,TAM);
			end = clock();
			timeRdm = (end - start) / (CLOCKS_PER_SEC * 1.0);

			printf("%lf\n%lf\n%lf\n",timeAsc,timeDesc,timeRdm);
			break;

		case INSERTION:
			start = clock();
			insertion(vectorAsc,TAM);
			end = clock();
			timeAsc = (end - start) / (CLOCKS_PER_SEC * 1.0);

			start = clock();
			insertion(vectorDesc,TAM);
			end = clock();
			timeDesc = (end - start) / (CLOCKS_PER_SEC * 1.0);

			start = clock();
			insertion(vectorRdm,TAM);
			end = clock();
			timeRdm = (end - start) / (CLOCKS_PER_SEC * 1.0);

			printf("%lf\n%lf\n%lf\n",timeAsc,timeDesc,timeRdm);
			break;

		case MERGE:
			start = clock();
			mergesort(vectorAsc,0,TAM-1);
			end = clock();
			timeAsc = (end - start) / (CLOCKS_PER_SEC * 1.0);

			start = clock();
			mergesort(vectorDesc,0,TAM-1);
			end = clock();
			timeDesc = (end - start) / (CLOCKS_PER_SEC * 1.0);

			start = clock();
			mergesort(vectorRdm,0,TAM-1);
			end = clock();
			timeRdm = (end - start) / (CLOCKS_PER_SEC * 1.0);

			printf("%lf\n%lf\n%lf\n",timeAsc,timeDesc,timeRdm);
			break;
		case HEAPSORT:
			start = clock();
			heapsort(vectorAsc,TAM);
			end = clock();
			timeAsc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			heapsort(vectorDesc,TAM);
			end = clock();
			timeDesc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			heapsort(vectorRdm,TAM);
			end = clock();
			timeRdm = (end - start) / (CLOCKS_PER_SEC * 1.0);

			printf("%lf\n%lf\n%lf\n",timeAsc,timeDesc,timeRdm);
			break;
		case QUICKSORT:
			start = clock();
			quicksort(vectorAsc,0,TAM-1);
			end = clock();
			timeAsc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			quicksort(vectorDesc,0,TAM-1);
			end = clock();
			timeDesc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			quicksort(vectorRdm,0,TAM-1);
			end = clock();
			timeRdm = (end - start) / (CLOCKS_PER_SEC * 1.0);

			printf("%lf\n%lf\n%lf\n",timeAsc,timeDesc,timeRdm);
			break;
		case COUNTING:
			start = clock();
			counting(vectorAsc,TAM);
			end = clock();
			timeAsc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			counting(vectorDesc,TAM);
			end = clock();
			timeDesc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			counting(vectorRdm,TAM);
			end = clock();
			timeRdm = (end - start) / (CLOCKS_PER_SEC * 1.0);

			printf("%lf\n%lf\n%lf\n",timeAsc,timeDesc,timeRdm);
			break;
		case RADIX:
			start = clock();
			radixsort(vectorAsc,TAM);
			end = clock();
			timeAsc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			radixsort(vectorDesc,TAM);
			end = clock();
			timeDesc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			radixsort(vectorRdm,TAM);
			end = clock();
			timeRdm = (end - start) / (CLOCKS_PER_SEC * 1.0);

			printf("%lf\n%lf\n%lf\n",timeAsc,timeDesc,timeRdm);
			break;
		case BUCKET:
			start = clock();
			bucketsort(vectorAsc,TAM,max(TAM/10,8));
			end = clock();
			timeAsc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			bucketsort(vectorDesc,TAM,max(TAM/10,8));
			end = clock();
			timeDesc = (end - start) / (CLOCKS_PER_SEC * 1.0);
			
			start = clock();
			bucketsort(vectorRdm,TAM,max(TAM/10,8));
			end = clock();
			timeRdm = (end - start) / (CLOCKS_PER_SEC * 1.0);

			printf("%lf\n%lf\n%lf\n",timeAsc,timeDesc,timeRdm);
			break;
	}

/*	print_vector(vectorAsc,TAM);
	print_vector(vectorDesc,TAM);
	print_vector(vectorRdm,TAM);*/
	
	free(vectorAsc);
	free(vectorDesc);
	free(vectorRdm);

	return 0;
}
