/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */


#ifndef _DATA_H_
#define _DATA_H_

#include "conversion.h"

typedef struct data_schema{

	char *filename_field;
	char type;
	int tam;
}DATA_SCHEMA;

typedef struct info_schema{
	
	DATA_SCHEMA *data_schema;	
	char *filename;	
	int amount_field;
	int total;
}INFO_SCHEMA;

typedef struct info_data{

	char *filename_data;
	int amount_reg;
}INFO_DATA;

//Leityra do arquivo schema
INFO_SCHEMA *read_file_schema(char *);

//Dump do arquivo schema
void dump_schema(INFO_SCHEMA *);

//Desalocação do arquivo schema
void destroy_info_schema(INFO_SCHEMA *);

//Criação do arquivo de dados
INFO_DATA *create_data(INFO_SCHEMA *);

//Dump do data
void dump_data(INFO_SCHEMA *, INFO_DATA *);

//Desalocação do data
void destroy_data(INFO_DATA *);

#endif
