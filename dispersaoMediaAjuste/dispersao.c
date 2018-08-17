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


	while(counter++<N){
		scanf("%lf %lf",&x,&y);
		sum += ((a*x)+b-y) * ((a*x)+b-y);
	}
	
	deltaY = sum/(N-2);
	deltaY = sqrt(deltaY);
	
	printf("Resultado: %lf\n",deltaY);

	return 0;
}
