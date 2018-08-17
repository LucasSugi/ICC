#include <stdio.h>
#include <stdlib.h>

double f(double x){
	return x*x;
}

int main(){
	
	int a,b;
	double x,y;
	double dx,integral;

	//Informando funcionalidade do programa
	printf("Programa que calcula a integral da função F(x) = x²\n\n");

	//Informando o usuário para digitar o intervalo da integral
	printf("Digite o intervalo da integral: ");
	
	//Armazenando o intervalo
	scanf("%d%d",&a,&b);
	
	//Inicializando variáveis	
	integral = 0;
	x = a;
	
	//Elemento infinitesimal
	dx = 0.0000001;

	//Integrando até n->"infinito"
	while(x<b){
		integral += f(x) * dx;
		x += dx;
	}
	
	printf("Integral: %lf\n",integral);
	
	return 0;
}
