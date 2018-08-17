#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define M 500000 

struct hash{
	int chave;
	int flag;
	HASH *dir;
};

struct table{

	HASH *hash;
	int n;
};

//Criação da tabela tabel de tamanho n
TABLE *create_hash(int n){
	
	int i;
	
	//Alocação
	TABLE *table = (TABLE*) malloc(sizeof(TABLE));
	
	if(table != NULL){
		//Alocação
		table->hash = (HASH*) malloc(sizeof(HASH) * n);
	}

	//Armazenano o tamanho da tabela
	table->n = n;

	if(table != NULL){
		for(i=0;i<n;i++){
			table->hash[i].chave = -1;
			table->hash[i].flag = 0;
			table->hash[i].dir = NULL;
		}
	}
	
	return table;
}

//Setando um item
void add_hash(TABLE *table, int chave){
		
	HASH *aux, *pant,*pnovo;

	//Cálculo da posição da chave
	int pos = chave % M;
	
	//Verificando se a posição encontrada está dentro do vetor
	if(pos < table->n){
		//0 indica que está disponível
		if(table->hash[pos].flag == 0){
			table->hash[pos].chave = chave;
			table->hash[pos].flag = 1;
		}
		else{	
			//Procurando pela posição
			pant = &(table->hash[pos]);
			aux = pant->dir;
			while(aux != NULL){
				pant = aux;
				aux = aux->dir;
			}
			//Setando
			pnovo = (HASH*) malloc(sizeof(HASH));
			pnovo->chave = chave;
			pnovo->flag = 1;
			pnovo->dir = NULL;
			pant->dir = pnovo;
		}
	}	
}

//Procurando pela chave
void search_hash(TABLE *table, int chave){
	
	HASH *aux;
		
	//Cálculo da posição da chave	
	int pos = chave % M;

	if(table->hash[pos].chave == chave){
		printf("Encontrei a chave: %d\n",chave);
	}	
	else{
		aux = table->hash[pos].dir;
		while(aux != NULL && aux->chave != chave){
			aux = aux->dir;
		}
		if(aux == NULL){
			printf("Não encontrei\n");
		}
		else {
			printf("Encontrei a chave: %d\n",chave);	
		}
	}
}

//Desalocando tabela hash
void destroy_hash(TABLE *table){
	
	int i;
	HASH *aux, *prem;

	for(i=0;i<table->n;i++){
		aux = table->hash[i].dir;
		while(aux != NULL){
			prem = aux;
			aux = aux->dir;	
			free(prem);
		}
	}

	free(table->hash);
	free(table);
}
