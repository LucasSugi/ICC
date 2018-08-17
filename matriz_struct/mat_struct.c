#include <stdio.h>
#include <stdlib.h>

typedef struct PESSOA {
	
	int idade;
	int altura;
	int peso;


} pessoa;

int main(int argc, char *argv[]){

	pessoa *cadastro;

	cadastro = (pessoa*) malloc(sizeof(pessoa)*4);	

	cadastro[2].idade = 66;

	printf("%d\n",cadastro[2].idade);


	return 0;
}
