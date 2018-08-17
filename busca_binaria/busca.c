#include <stdio.h>
#include <stdlib.h>

#define TAM 1000000000

//Função que realiza a busca binária
int search_binary(int *vector,int key, int start, int end,int counter){
	
	int middle = (start + end) / 2;

	if(start > end) return 0;
	
	if(key == vector[middle]){
		printf("Encontrei a chave %d com %d iterações\n",key,counter);
		return 1;
	}
	else if(key < vector[middle]){
		search_binary(vector,key,start,middle-1,counter+1);
	}
	else if(key > vector[middle]){
		search_binary(vector,key,middle+1,end,counter+1);
	}
}

int main(int argc, char *argv[]){

	int *vector = NULL;
	int i,key,counter = 0;
	
	//Criação do vetor
	vector = (int*) malloc(sizeof(int)*TAM);	

	//Alocando elementos no vetor
	for(i=0;i<TAM;i++){
		vector[i] = i + 1;
	}

	//Usuário digita o valor que quer buscar
	scanf("%d",&key);

	//Busca binária
	search_binary(vector,key,0,TAM-1,counter);

	//Liberando o vetor
	free(vector);

	return 0;
}
