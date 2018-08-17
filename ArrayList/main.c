/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include "ArrayList.h"
#include "item.h"
#include "opcao.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int option_program(char name[50]){

	int option;

	if( strcmp(name,"sair") == 0 ){
		option = 0;
	}
	else if( strcmp(name,"tamanho") == 0 ){
		option = 1;
	}
	else if( strcmp(name,"add") == 0 ){
		option = 2;
	}
	else if( strcmp(name,"sub") == 0 ){
		option = 3;
	}
	else if( strcmp(name,"set") == 0 ){
		option = 4;
	}
	else if( strcmp(name,"print") == 0 ){
		option = 5;
	}
	else if( strcmp(name,"contem") == 0 ){
		option = 6;
	}
	else if( strcmp(name,"indice") == 0 ){
		option = 7;
	}
	else if( strcmp(name,"vazia") == 0 ){
		option = 8;
	}
	else if( strcmp(name,"remover") == 0 ){
		option = 9;
	}
	else if( strcmp(name,"get") == 0 ){
		option = 10;
	}
	return option;
}

enum{
	
	SAIR,
	TAMANHO,
	ADD,
	SUB,
	SET,
	PRINT,
	CONTEM,
	INDICE,
	VAZIA,
	REMOVER,
	GET
};

//Função principal - main
int main(int argc, char *argv[]){
	
	int option = -1;
	char name[50];
	
	ArrayList *list = new_ArrayList();

	while(option != 0){

		//Lendo a opção
		scanf("%s",name);	
	
		//Analisando a opção digitada pelo usuário
		option = option_program(name);		
		
		//Menu com as opções do programa	
		switch(option){
			case SAIR:
				destruct_ArrayList(&list);
				break;
			case TAMANHO:
				size_ArrayList(list);
				break;
			case ADD:
				add(list);
				break;
			case SUB:
				sub(list);
				break;
			case SET:
				set(list);
				break;
			case PRINT:
				print_ArrayList(list);
				break;
			case CONTEM:
				contains(list);
				break;
			case INDICE:
				index_array(list);
				break;	
			case VAZIA:
				printf("%d\n",(isEmpty_ArrayList(list)));
				break;
			case REMOVER:
				remover(list);
				break;
			case GET:
				get(list);
				break;
		}	
	}

	return 0;
}
