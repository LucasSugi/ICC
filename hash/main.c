#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#define TAM 1000000

int main(int argc, char *argv){
	
	int i;

	//Criando tabela	
	TABLE *table = create_hash(TAM);
	
	//Alocando vetor
	int *vector = (int*) malloc(sizeof(int) * TAM);

	//Populando vetor
	for(i=0;i<TAM;i++){
		vector[i] = i+1;	
	}
	
	//Adicionando elementos na tabela
	for(i=0;i<TAM;i++){
		add_hash(table,vector[i]);
	}	
	
	//Procurando por elementos
	for(i=0;i<TAM;i++){
		search_hash(table,i+1);
	}	
	
	//Destruindo tabela
	destroy_hash(table);
	
	//Desalocando vetor
	free(vector);

	return 0;
}
