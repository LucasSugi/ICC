/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ocr.h"
#include "data.h"
#include "knn.h"

enum{
	EXIT,	
	DUMP_SCHEMA,
	DUMP_DATA,
	MEM_DIST,
	MEM_OP,
	OCR_DUMP_NN,
	OCR_KNN
};

//Função principal
int main(){
	
	int optionInt = 1;
	char name[50];
	INFO_SCHEMA *info_schema = NULL;
	INFO_DATA *info_data = NULL;
	IMAGE *img = NULL;
	
	//Leitura da primeira opção para saber se é necessário tratar os arquivos em memória ou em disco
	scanf("%s",name);	

	//Analisando a opção
	if( strcmp(name,"none") != 0 ){
		info_schema = read_file_schema(name);
		info_data = create_data(info_schema);
	}

	//Menu de opções
	while(optionInt != 0){
	
		//Leitura da ação requerida pelo usuário
		scanf("%s",name);
				
		if( strcmp(name,"exit") == 0 ){
			optionInt = 0;
		}
		else if( strcmp(name,"dump_schema") == 0){
			optionInt = 1;
		}
		else if( strcmp(name,"dump_data") == 0){
			optionInt = 2;
		}
		else if( strcmp(name,"mem_dist") == 0){
			optionInt = 3;
		}
		else if( strcmp(name,"mem_op") == 0){
			optionInt = 4;
		}
		else if( strcmp(name,"ocr_dump_nn") == 0){
			optionInt = 5;
		}
		else if( strcmp(name,"ocr_knn") == 0){
			optionInt = 6;
		}

		//Executando a opção	
		switch(optionInt){
			case EXIT:
				destroy_info_schema(info_schema);
				destroy_data(info_data);
				break;
			case DUMP_SCHEMA:
				dump_schema(info_schema);
				break;
			case DUMP_DATA:
				dump_data(info_schema,info_data);
				break;
			case MEM_DIST:
				mem_dist();
				break;
			case MEM_OP:
				mem_op(1,1);
				break;
			case OCR_DUMP_NN:
				img = mem_op(2,1);
				ocr_dump_nn(info_schema,info_data,img,1);
				break;
			case OCR_KNN:
				img = mem_op(2,2);
				ocr_dump_nn(info_schema,info_data,img,2);
				break;
			default:
				printf("Opção digitada inválida\n");
		}
	}

	return 0;
}
