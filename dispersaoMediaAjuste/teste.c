#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Define o número total de dados aqui
#define N 13

int main(){

	int counter = 0;
	double x,y;
	double a,b;	
	double deltaY = 0 , sum = 0;
	
	//Define os valores de "a" e "b" aqui
	a = 0.181043956;	
	b = 0.146538461;	

	double x1 = 18.2;	
	double y1 = 5.2;
	double sum2, sum3;
	sum2 = sum3 = 0;	

	while(counter++<N){
		scanf("%lf %lf",&x,&y);
		//sum += ((a*x)+b-y) * ((a*x)+b-y);
		sum += (x - x1) * (y - y1);
		sum2 += (x - x1) * (x - x1);
		sum3 += (y - y1) * (y - y1);
	}
	
	sum2 = sqrt(sum2);
	sum3 = sqrt(sum3);
	deltaY = sum / (sum2 * sum3);
	
	printf("Resultado: %lf\n",deltaY);

	return 0;
}
