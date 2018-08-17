/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "conversion.h"

#define FIELD 1
#define TYPE 2

/*
Leitura do conteúdo do arquivo schema
Parâmetros char*
Retorno: INFO_SCHEMA *
*/
INFO_SCHEMA *read_file_schema(char *filename){
	
	int tam, i,j, control = 1;
	char *aux = NULL;
	
	//Abertura do arquivo schema patra leitura
	FILE *fp = fopen(filename,"r");
	
	//Caso não consiga abrir o arquivo a função é parada
	if(fp == NULL) return NULL;
	
	//Criando o ponteiro responsável por armazenar as informações do arquivo schema
	INFO_SCHEMA *info_schema = (INFO_SCHEMA*) malloc(sizeof(INFO_SCHEMA));

	//Inicializando variáveis - A variável já inicializada como 2 pois há os campos id e dist que devem ser alocados
	info_schema->amount_field = 1;
	
	//Inicializando o total
	info_schema->total = 0;

	//Inicializando o ponteiro que armazenará as strings temporariamente
	aux = (char*) malloc(sizeof(char) * 50);
	
	//Contando a quantidade de campos	
	while( !feof(fp) ){
		aux[0] = fgetc(fp);
		if(aux[0] == '\n'){
			info_schema->amount_field++;
		}
	}

	//Alocando a quantidade exata de campos
	info_schema->data_schema = (DATA_SCHEMA*) malloc(sizeof(DATA_SCHEMA) * info_schema->amount_field);

	//Inicializando a estrutura
	for(i=0;i<info_schema->amount_field;i++){
		info_schema->data_schema[i].filename_field = NULL;
		info_schema->data_schema[i].tam = 0;	
		info_schema->data_schema[i].type = '\0';
	}

	//Armazenando o campo id
	info_schema->data_schema[0].filename_field = (char*) malloc(sizeof(char) * 3);
	strcpy(info_schema->data_schema[0].filename_field,"id");
	info_schema->data_schema[0].type = 'i'; 
	info_schema->data_schema[0].tam = sizeof(int);

	//Armazenando o campo dist
	info_schema->data_schema[info_schema->amount_field-1].filename_field = (char*) malloc(sizeof(char) * 5);
	strcpy(info_schema->data_schema[info_schema->amount_field-1].filename_field,"dist");
	info_schema->data_schema[info_schema->amount_field-1].type = 'd'; 
	info_schema->data_schema[info_schema->amount_field-1].tam = sizeof(double);
	
	//Movendo o cursor para o início do arquivo
	fseek(fp,0,SEEK_SET);

	//A string "tabela" é ignorada e é apenas armazenado a string que contém o nome do arquivo .data
	fscanf(fp,"%s",aux);
	fscanf(fp,"%s",aux);

	//Armazenando o nome do arquivo .data
	tam = strlen(aux);
	info_schema->filename = (char*) malloc(sizeof(char) * (tam + 1));
	strcpy(info_schema->filename,aux);

	//Inicializando as variáveis que serão usadas no laço while
	j = 0;
	i = 1;
	
	//While utilizado para ler os campos e os tipos 
	while( !feof(fp) && i<info_schema->amount_field -1){
		//Variável aux recebe sempre uma string que será armazenada ou comparada
		fscanf(fp,"%s",aux);

		switch(control){
			case FIELD:
				tam = strlen(aux);
				info_schema->data_schema[i].filename_field = (char*) malloc(sizeof(char) * (tam + 1));
				strcpy(info_schema->data_schema[i].filename_field,aux);			
				control = TYPE;
				break;
			case TYPE:
				if( strcmp(aux,"int") == 0 ){
					info_schema->data_schema[i].type = 'i';
					info_schema->data_schema[i].tam = sizeof(int);
				} 
				else if ( strcmp(aux,"double") == 0){
					info_schema->data_schema[i].type = 'd';
					info_schema->data_schema[i].tam = sizeof(double);
				} else {

					//Definindo o tipo					
					if(aux[0] == 'b'){
						info_schema->data_schema[i].type = 'b';
					}
					else{
						info_schema->data_schema[i].type = 'c';
					}

					//O while irá até a primeira chave do char[*] ou bits[*]	
					while(aux[j] != '['){
						j++;
					}
					//A variável tam recebe j + 1 para se posicionar no número dentro das chaves
					tam = j + 1;
					//O while irá até a última chave para depois  colocar nela um '\0'
					while(aux[j] != ']'){
						j++;
					}
					aux[j] = '\0';
					/*Como o ponteiro está posicionado no número e como a última chave é um '\0' podemos
					converter a string para inteiro*/
					info_schema->data_schema[i].tam = atoi(aux + tam);
					
					//Zerando variável para ser utilizada novamente	
					j = 0;
				}
				control = FIELD;
				i++;	
				break;
		}	
	}
	
	//Armazenando a quantidade total de bytes que o schema irá ter
	for(i=0;i<info_schema->amount_field;i++){
		info_schema->total += info_schema->data_schema[i].tam;
	}

	//Liberando variável aux
	free(aux);

	//Fechando o arquivo
	fclose(fp);
	
	//Retorno da estrutura de informações do schema
	return info_schema;
}

/*
Imprimir o arquivo .schema
Parâmetro: INFO_SCHEMA* 
Retorno: nenhum
*/
void dump_schema(INFO_SCHEMA *info_schema){

	int i;

	//Impressão do nome da tabela
	printf("table %s(%d bytes)\n",info_schema->filename,info_schema->total);
	
	//Impressão dos campos com seus respectivos tipos e quantidade de bytes
	for(i=0;i<info_schema->amount_field;i++){
		printf("%s ",info_schema->data_schema[i].filename_field);
		
		if(info_schema->data_schema[i].type == 'i'){
			printf("int(%d bytes)\n",info_schema->data_schema[i].tam);
		}	
		else if(info_schema->data_schema[i].type == 'd'){
			printf("double(%d bytes)\n",info_schema->data_schema[i].tam);
		}	
		else if(info_schema->data_schema[i].type == 'c'){
			printf("char[%d](%d bytes)\n",info_schema->data_schema[i].tam,info_schema->data_schema[i].tam);
		}
		else{
			printf("byte[%d](%d bytes)\n",info_schema->data_schema[i].tam,info_schema->data_schema[i].tam);
		}
	}
}

/*
Desalocar a estrutura schema
Parâmetros: INFO_SCHEMA*
Retorno: nenhum
*/
void destroy_info_schema(INFO_SCHEMA *info_schema){
	
	int i;

	if(info_schema != NULL){
			
		//Desalocando o nome da tabela
		free(info_schema->filename);
		
		//Desalocando o nome dos campos
		for(i=0;i<info_schema->amount_field;i++){
			free(info_schema->data_schema[i].filename_field);
		}

		//Desalocando a estrutura dados do schema
		free(info_schema->data_schema);

		//Desalocando a estrutura de informações do schema
		free(info_schema);
	}
}

/*
Criação do arquivo de dados .data - Os dados serão entregues ao programa via stdin
Parâmetros: INFO_SCHEMA*
Retorno: INFO_DATA*
*/
INFO_DATA *create_data(INFO_SCHEMA *info_schema){

	INFO_DATA *info_data = (INFO_DATA*) malloc(sizeof(INFO_DATA));
	FILE *fp = NULL;
	char *insertChar = NULL;
	double insertDouble;
	int i, insertInt,nrow,ncol;
	
	//Criação do nome do arquivo .data
	i = strlen(info_schema->filename);
	info_data->filename_data = (char*) malloc(sizeof(char) * (i + 6));	
	strcpy(info_data->filename_data,info_schema->filename);
	strcat(info_data->filename_data,".data");

	//Criando o arquivo binário .data
	fp = fopen(info_data->filename_data,"wb");

	//Alocando o char*
	insertChar = (char*) calloc(200,sizeof(char));

	//Inicializando a quantidade de registros como 0
	info_data->amount_reg = 0;
	
	//Armazenando a primeira entrada
	scanf("%d",&insertInt);
	
	//Armazenando os dados recebidos via stdin no arquivo .data
	while(insertInt != -1){
		
		//Armazenando o id	
		fwrite(&insertInt,sizeof(int),1,fp);

		for(i=1;i<info_schema->amount_field-1;i++){
			if(info_schema->data_schema[i].type == 'i'){
				scanf("%d",&insertInt);
				if(i == 1){
					nrow = insertInt;
				}
				else{
					ncol = insertInt;
				}
				fwrite(&insertInt,sizeof(int),1,fp);
			} else if(info_schema->data_schema[i].type == 'd'){
				scanf("%lf",&insertDouble);
				fwrite(&insertDouble,sizeof(double),1,fp);
			} else if(info_schema->data_schema[i].type == 'c'){
				scanf("%s",insertChar);
				fwrite(insertChar,info_schema->data_schema[i].tam,1,fp);
			}
			else{
				conversion_string_to_int(fp,nrow,ncol,info_schema->data_schema[i].tam*8,info_schema->data_schema[i].tam);
			}
		}
	
		//Inicialmente o campo dist é 0
		insertDouble = 0;
		fwrite(&insertDouble,sizeof(double),1,fp);
	
		//Aumentando a quantidade de registros
		info_data->amount_reg++;
			
		//Armazenando o próximo id ou o terminador
		scanf("%d",&insertInt);
	}
	
	//Liberando o char*
	free(insertChar);

	//Fechando o arquivo .data
	fclose(fp);

	return info_data;
}

/*
Imprime o arquivo de dados .data
Parâmetros: INFO_SCHEMA*, INFO_DATA*
Retorno: nenhum
*/
void dump_data(INFO_SCHEMA *info_schema, INFO_DATA *info_data){

	FILE *fp = NULL;
	int i,j,printInt,nrow,ncol;
	double printDouble;
	char *printChar = (char*) malloc(sizeof(char) * 200);
	unsigned char *image = NULL;
	
	//Abrindo o arquivo .data para leitura
	fp = fopen(info_data->filename_data,"rb");
	
	//Imprimindo o arquivo .data	
	for(i=0;i<info_data->amount_reg;i++){
		for(j=0;j<info_schema->amount_field;j++){
			if(info_schema->data_schema[j].type == 'i'){
				printf("%s = ",info_schema->data_schema[j].filename_field);	
				fread(&printInt,sizeof(int),1,fp);
				if(j == 1){
					nrow = printInt;
				}
				if(j == 2){
					ncol = printInt;
				}
				printf("%d\n",printInt);
			} 
			else if(info_schema->data_schema[j].type == 'd'){
				printf("%s = ",info_schema->data_schema[j].filename_field);	
				fread(&printDouble,sizeof(double),1,fp);
				printf("%.2lf\n",printDouble);
			}
			else if(info_schema->data_schema[j].type == 'c'){
				printf("%s = ",info_schema->data_schema[j].filename_field);	
				fread(printChar,info_schema->data_schema[j].tam,1,fp);
				printf("%s\n",printChar);
			}
			else {
				printf("%s = ",info_schema->data_schema[j].filename_field);
				image = conversion_int_to_string(fp,nrow*ncol,info_schema->data_schema[j].tam*8,info_schema->data_schema[j].tam);
				printf("%s\n",image);
				free(image);
			}
		}
	}

	//Liberando o char*
	free(printChar);

	//Fechando o arquivo .data
	fclose(fp);
}

/*
Desaloca a estrutura de dados data
Parâmetros: INFO_DATA*
Retorno: nenhum
*/
void destroy_data(INFO_DATA *info_data){
	
	if(info_data != NULL){
		free(info_data->filename_data);
		free(info_data);
	}
}
