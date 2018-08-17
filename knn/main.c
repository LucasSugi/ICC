/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FIELD 1
#define TYPE 2


enum{
	OPTION,
	EXIT,
	DUMP_SCHEMA,
	DUMP_DATA,
	DUMP_NN,
	KNN
};

typedef struct data_schema{
	
	char *field;
	char type;
	int amount;

} DATA_SCHEMA;

typedef struct info_schema{
	
	DATA_SCHEMA *data_schema;
	char *filename_data;
	int amount_field;
	int total;

} INFO_SCHEMA;

typedef struct info_data{
	
	char *filename_data;
	int amount_reg;

} INFO_DATA;

typedef struct class{

	void *cmp;
	int amount;

} CLASS;

/*
Leitura do nome do arquivo schema
Parâmetros: nenhum
Retorno: char*
*/
char *read_name(){

	char *filename = NULL;
	size_t tam;
		
	//Lendo o nome do stdin com getline
	getline(&filename,&tam,stdin);
	
	//Eliminando o caracter '\n'
	tam = strlen(filename);
	filename[tam-1] = '\0';

	return filename;
}

/*
Leitura do conteúdo do arquivo schema
Parâmetros char*
Retorno
*/
INFO_SCHEMA *read_content_file_schema(char *filename){
	
	INFO_SCHEMA *info_schema = (INFO_SCHEMA*) malloc(sizeof(INFO_SCHEMA));
	FILE *fp = NULL;	
	int i, j, control = FIELD, tam;
	char *aux;
		
	//Abrindo arquivo schema para leitura
	fp = fopen(filename,"r");

	//Alocando a variável aux que será utilizada para contar os \n e ler o nome do arquivo.data
	aux = (char*) malloc(sizeof(char)*50);

	//Inicializando a quantidade de campos como 2, já que o nome do arquivo.data será armazenado em outro lugar
	info_schema->amount_field = 2;
	
	//While utilizado para saber quantos campos existem no arquivo schema
	while( !feof(fp) ){
		aux[0] = fgetc(fp);
		if(aux[0] == '\n'){
			info_schema->amount_field++;
		}
	}

	//Alocando a quantidade certa de estruturas que irão armazenar os campos
	info_schema->data_schema = (DATA_SCHEMA*) malloc(sizeof(DATA_SCHEMA)*info_schema->amount_field);
	
	//Inicializando a variável total
	info_schema->total = 0;
	
	//Inicializar os campos
	info_schema->filename_data = NULL;
	for(i=0;i<info_schema->amount_field;i++){
		info_schema->data_schema[i].field = NULL;
		info_schema->data_schema[i].type = '\0';
		info_schema->data_schema[i].amount = 0;
	}

	//Armazenando o campo id
	info_schema->data_schema[0].field = (char*) malloc(sizeof(char)*3);
	strcpy(info_schema->data_schema[0].field,"id");
	info_schema->data_schema[0].type = 'i';
	info_schema->data_schema[0].amount = sizeof(int);
	
	//Armazenando o campo dist	
	i = info_schema->amount_field-1;
	info_schema->data_schema[i].field = (char*) malloc(sizeof(char)*5);
	strcpy(info_schema->data_schema[i].field,"dist");
	info_schema->data_schema[i].type = 'd';
	info_schema->data_schema[i].amount = sizeof(double);

	//Movendo o cursor do arquivo para o início
	fseek(fp,0,SEEK_SET);
	
	//Leitura do nome do arquivo data, a primeira leitura armazenada "table" e será ignorada	
	fscanf(fp,"%s",aux);
	fscanf(fp,"%s",aux);

	//Copiando o nome do arquivo.data para a estrutura de dados
	tam = strlen(aux);	
	info_schema->filename_data = (char*) malloc(sizeof(char) * (i + 1));
	strcpy(info_schema->filename_data,aux);

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
				info_schema->data_schema[i].field = (char*) malloc(sizeof(char) * (tam + 1));
				strcpy(info_schema->data_schema[i].field,aux);			
				control = TYPE;
				break;
			case TYPE:
				if( strcmp(aux,"int") == 0 ){
					info_schema->data_schema[i].type = 'i';
					info_schema->data_schema[i].amount = sizeof(int);
				} 
				else if ( strcmp(aux,"double") == 0){
					info_schema->data_schema[i].type = 'd';
					info_schema->data_schema[i].amount = sizeof(double);
				} else {
					//O while irá até a primeira chave do char[*]	
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
					info_schema->data_schema[i].type = 'c';
					/*Como o ponteiro está posicionado no número e como a última chave é um '\0' podemos
					converter a string para inteiro*/
					info_schema->data_schema[i].amount = atoi(aux + tam);
					j = 0;
				}
				control = FIELD;
				i++;	
				break;
		}	
	}
	
	//Armazenando a quantidade total de bytes que o schema irá ter
	for(i=0;i<info_schema->amount_field;i++){
		info_schema->total += info_schema->data_schema[i].amount;
	}

	//Liberando variável aux
	free(aux);

	//Fechando o arquivo schema
	fclose(fp);
	
	return info_schema;	
}

/*
Imprimir o arquivo .schema
Parâmetro: INFO_SCHEMA* 
Retorno: nenhum
*/
void dump_schema(INFO_SCHEMA* info_schema){

	int i;

	//Impressão do nome da tabela
	printf("table %s(%d bytes)\n",info_schema->filename_data,info_schema->total);
	
	//Impressão dos campos com seus respectivos tipos e quantidade de bytes
	for(i=0;i<info_schema->amount_field;i++){
		printf("%s ",info_schema->data_schema[i].field);
		
		if(info_schema->data_schema[i].type == 'i'){
			printf("int(%d bytes)\n",info_schema->data_schema[i].amount);
		}	
		else if(info_schema->data_schema[i].type == 'd'){
			printf("double(%d bytes)\n",info_schema->data_schema[i].amount);
		}	
		else {
			printf("char[%d](%d bytes)\n",info_schema->data_schema[i].amount,info_schema->data_schema[i].amount);
		}
	}

}

/*
Desalocar a estrutura schema
Parâmetros: INFO_SCHEMA*
Retorno: nenhum
*/
void destroy_schema(INFO_SCHEMA* info_schema){
	
	int i;

	for(i=0;i<info_schema->amount_field;i++){
		free(info_schema->data_schema[i].field);
	}

	free(info_schema->filename_data);
	free(info_schema->data_schema);
	free(info_schema);
}
/*
Criação do arquivo de dados .data - Os dados serão entregues ao programa via stdin
Parâmetros: INFO_SCHEMA*
Retorno: INFO_DATA*
*/
INFO_DATA *create_data(INFO_SCHEMA *info_schema){

	INFO_DATA *info_data = (INFO_DATA*) malloc(sizeof(INFO_DATA));
	FILE *fp = NULL;
	char aux, *insertChar = NULL;
	double insertDouble;
	int i, insertInt;
	
	//Criação do nome do arquivo .data
	i = strlen(info_schema->filename_data);
	info_data->filename_data = (char*) malloc(sizeof(char) * (i + 6));	
	strcpy(info_data->filename_data,info_schema->filename_data);
	strcat(info_data->filename_data,".data");

	//Criando o arquivo binário .data
	fp = fopen(info_data->filename_data,"wb");

	//Alocando o char*
	insertChar = (char*) calloc(50,sizeof(char));

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
				fwrite(&insertInt,sizeof(int),1,fp);
			} else if(info_schema->data_schema[i].type == 'd'){
				scanf("%lf",&insertDouble);
				fwrite(&insertDouble,sizeof(double),1,fp);
			} else {
				scanf("%s",insertChar);
				fwrite(insertChar,info_schema->data_schema[i].amount,1,fp);
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

	//Scanf utilizado para pegar o último '\n'
	scanf("%c",&aux);
	
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
	int i,j,printInt;
	double printDouble;
	char *printChar = (char*) malloc(sizeof(char) * 50);
	
	//Abrindo o arquivo .data para leitura
	fp = fopen(info_data->filename_data,"rb");
	
	//Imprimindo o arquivo .data	
	for(i=0;i<info_data->amount_reg;i++){
		for(j=0;j<info_schema->amount_field;j++){
			if(info_schema->data_schema[j].type == 'i'){
				printf("%s = ",info_schema->data_schema[j].field);	
				fread(&printInt,sizeof(int),1,fp);
				printf("%d\n",printInt);
			} 
			else if(info_schema->data_schema[j].type == 'd'){
				printf("%s = ",info_schema->data_schema[j].field);	
				fread(&printDouble,sizeof(double),1,fp);
				printf("%.2lf\n",printDouble);
			}
			else {
				printf("%s = ",info_schema->data_schema[j].field);	
				fread(printChar,info_schema->data_schema[j].amount,1,fp);
				printf("%s\n",printChar);
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

	free(info_data->filename_data);
	free(info_data);
}

/*
Parâmetros: INFO_SCHEMA*, INFO_DATA*, void*
Retorno: nenhum
*/
void sub_knn(INFO_SCHEMA *info_schema, INFO_DATA *info_data,void *new){
	
	int i,j, counter = 4, pos;
	void *cmp = NULL;
	double dist = 0;
	
	//Alocando o ponteiro void* que servirá de comparação
	cmp = malloc(50);	

	//Abertura do arquivo .data para leitura e escrita
	FILE *fp = fopen(info_data->filename_data,"r+b");
	
	//Armazenando a posição do dist
	pos = info_schema->total - sizeof(double);
	
	//Movendo o ponteiro para o primeiro campo a ser comparado	
	fseek(fp,counter,SEEK_SET);	
	
	//Executando o knn
	for(i=0;i<info_data->amount_reg;i++){
		for(j=1;j<info_schema->amount_field-2;j++){
			if(info_schema->data_schema[j].type == 'i'){
				fread(cmp,sizeof(int),1,fp);	
				dist += pow((*(int*)(cmp) - *(int*)(new + counter)), 2);
				counter += info_schema->data_schema[j].amount;
			}
			else if(info_schema->data_schema[j].type == 'd'){
				fread(cmp,sizeof(double),1,fp);
				dist += pow((*(double*)(cmp) - *(double*)(new + counter)), 2);
				counter += info_schema->data_schema[j].amount;
			}
		}
		//Terminando de calcular a distância euclidiana
		dist = sqrt(dist);
	
		//Movendo o cursor do arquivo para alterar o dist do registro
		fseek(fp,pos,SEEK_SET);

		//Atualizando a posição para o novo dist
		pos = pos + info_schema->total;
		
		//Escrevendo o novo dist		
		fwrite(&dist,sizeof(double),1,fp);
		
		//Inicializando as variáveis para o laço "rodar" de novo
		counter = 4;
		dist = 0;

		//Movendo o cursor para comparar com o próximo campo
		fseek(fp,counter,SEEK_CUR);
	}
		
	//Desalocando o ponteiro void*
	free(cmp);

	//Fechando o arquivo
	fclose(fp);
}

/*
Ordenando os dist
Parâmetros: INFO_DATA *, double *, int *
Retorno: nenhum
*/
void ordenation(INFO_DATA *info_data, double *dist, int *offset){

	int i,j, auxI;
	double auxD;

	for(i=1;i<info_data->amount_reg;i++){
		for(j=0;j<info_data->amount_reg-i;j++){
			if(dist[j] > dist[j+1]){
				auxD = dist[j];
				dist[j] = dist[j+1];	
				dist[j+1] = auxD;

				auxI = offset[j];
				offset[j] = offset[j+1];
				offset[j+1] = auxI;	
			}
		}
	}
}

/*
Dump dos k vizinhos mais próximos
Parâmetros: FILE*, int*,int
Retorno: nenhum
*/
void dump_nn(FILE *fp,INFO_SCHEMA *info_schema,int *offset, int neighbor){

	int i,j,printInt;
	double printDouble;
	char *printChar = (char*) malloc(sizeof(char) * 50);
	
	//Imprimindo o arquivo .data	
	for(i=0;i<neighbor;i++){
		fseek(fp,offset[i],SEEK_SET);
		for(j=0;j<info_schema->amount_field;j++){
			if(info_schema->data_schema[j].type == 'i'){
				printf("%s = ",info_schema->data_schema[j].field);	
				fread(&printInt,sizeof(int),1,fp);
				printf("%d\n",printInt);
			} 
			else if(info_schema->data_schema[j].type == 'd'){
				printf("%s = ",info_schema->data_schema[j].field);	
				fread(&printDouble,sizeof(double),1,fp);
				printf("%.2lf\n",printDouble);
			}
			else {
				printf("%s = ",info_schema->data_schema[j].field);	
				fread(printChar,info_schema->data_schema[j].amount,1,fp);
				printf("%s\n",printChar);
			}
		}
	}

	//Liberando o char*
	free(printChar);
}

/*
Classificação do novo registro
Parâmetros:
Retorno: nenhum
*/
void classification_knn(FILE *fp, INFO_SCHEMA *info_schema,int *offset, int neighbor){

	int i, j, counter = 0, pos, posClass = 0, control;
	CLASS *class = NULL;
	void *aux = malloc(50);

	//Alocando a estrutura que servirá de classificação
	class = (CLASS*) malloc(sizeof(CLASS)*neighbor);
	
	//Armazenando a posição de classificação
	for(i=0;i<info_schema->amount_field-2;i++){
		counter += info_schema->data_schema[i].amount;
		pos = i+1;
	}
	
	//Pegando a primeira classe
	fseek(fp,counter + offset[0],SEEK_SET);
	if(info_schema->data_schema[pos].type == 'i'){
		class[0].cmp = malloc(sizeof(int));
		fread(class[0].cmp,sizeof(int),1,fp);					
		class[0].amount = 1;					
	} 
	else if(info_schema->data_schema[pos].type == 'd'){
		class[0].cmp = malloc(sizeof(double));
		fread(class[0].cmp,sizeof(double),1,fp);					
		class[0].amount = 1;					

	} else {
		class[0].cmp = malloc(info_schema->data_schema[pos].amount);
		fread(class[0].cmp,info_schema->data_schema[pos].amount,1,fp);
		class[0].amount = 1;					
	}
	
	//Inicializando variáveis para o laço
	j = control = 0;
	
	//Analisando as classes dos vizinhos
	for(i=1;i<neighbor;i++){
		fseek(fp,counter+offset[i],SEEK_SET);
		if(info_schema->data_schema[pos].type == 'i'){
			fread(aux,sizeof(int),1,fp);
			while(j<=posClass){
				if(*(int*)class[j].cmp == *(int*)aux){
					control = 1;
					class[j].amount++;	
					break;
				}	
				j++;
			}
			if(control != 1){
				posClass++;
				class[posClass].cmp = malloc(sizeof(int));
				*(int*)class[posClass].cmp = *(int*)aux;
				class[posClass].amount = 1;
			}	
			j = control = 0;
		} 
		else if(info_schema->data_schema[pos].type == 'd'){
			fread(aux,sizeof(double),1,fp);
			while(j<=posClass){
				if(*(double*)class[j].cmp == *(double*)aux){
					control = 1;
					class[j].amount++;	
					break;
				}	
				j++;
			}
			if(control != 1){
				posClass++;
				class[posClass].cmp = malloc(sizeof(double));
				*(double*)class[posClass].cmp = *(double*)aux;
				class[posClass].amount = 1;
			}	
			j = control = 0;
		} else {
			fread(aux,info_schema->data_schema[pos].amount,1,fp);
			while(j<=posClass){
				if( strcmp((char*)class[j].cmp,(char*)aux) == 0 ){
					control = 1;
					class[j].amount++;	
					break;
				}	
				j++;
			}
			if(control != 1){
				posClass++;
				class[posClass].cmp = malloc(info_schema->data_schema[pos].amount);
				strcpy((char*)class[posClass].cmp,(char*)aux);
				class[posClass].amount = 1;
			}	
			j = control = 0;
		}
	}

	//Classificando	
	control = class[0].amount;
	j = 0;
	for(i=1;i<posClass;i++){
		if(control < class[i].amount){
			control = class[i].amount;
			j = i;
		}
		else if(control == class[i].amount){
			if(info_schema->data_schema[pos].type == 'i'){
				if( *(int*)class[j].cmp > *(int*)class[i].cmp){
					j = i;	
				}
			} else if(info_schema->data_schema[pos].type == 'd'){
				if( *(double*)class[j].cmp > *(double*)class[i].cmp){
					j = i;
				}
			} else {
				if( strcmp( (char*)class[j].cmp,(char*)class[i].cmp) > 0 ){
					j = i;
				}
			}
		}
	}
	
	//Imprimindo a classe
	if(info_schema->data_schema[pos].type == 'i'){
		printf("%d\n",*(int*)class[j].cmp);
	}
	else if(info_schema->data_schema[pos].type == 'd'){
		printf("%.2lf",*(double*)class[j].cmp);
	}
	else {
		printf("%s\n",(char*)class[j].cmp);
	}

	free(aux);
}

/*
Armazena os dists e os ordena
Parâmetros: INFO_SCHEMA *, INFO_DATA*, int, int
Retorno: nenhum
*/
void sub2_knn(INFO_SCHEMA *info_schema, INFO_DATA *info_data, int neighbor, int option){
	
	int pos, i, *offset = NULL;
	double *dist = NULL;

	//Abrindo o arquivo .data
	FILE *fp = fopen(info_data->filename_data,"rb");

	//Alocando a quantidade certa de memória para armazenar todos os dist
	dist = (double*) malloc(sizeof(double)*info_data->amount_reg);
	
	//Alocando a quantidade certa de memória para armazenar todos os offsets
	offset = (int*) malloc(sizeof(int)*info_data->amount_reg);
	
	//Movendo cursor para o primeiro dist
	pos = info_schema->total - sizeof(double);	
	
	//Armazenando os dist
	for(i=0;i<info_data->amount_reg;i++){
		fseek(fp,pos,SEEK_SET);	
		fread(&dist[i],sizeof(double),1,fp);
		offset[i] = info_schema->total * i;
		pos = pos + info_schema->total;
	}
	
	//Ordenando os dist	
	ordenation(info_data,dist,offset);
	
	if(option == 4){
		//Dump dos k vizinhos mais próximos
		dump_nn(fp,info_schema,offset,neighbor);
	} else {
		classification_knn(fp,info_schema,offset,neighbor);	
	}
	
	//Desalocando
	free(offset);
	free(dist);

	//Fechando o arquivo
	fclose(fp);
}

/*
Realiza uma classificação para um novo registro
Parâmetros: INFO_SCHEMA*, INFO_DATA*
Retorno: nenhum
*/
void knn(INFO_SCHEMA *info_schema, INFO_DATA *info_data, int option){

	int i, counter = 0, neighbor;
	char aux;
	void *new = NULL;

	//Armazenando a quantidade de vizinhos que serão analisados
	scanf("%d",&neighbor);
	
	//Percorrendo os campos para saber quantos bytes terão que ser alocados
	for(i=0;i<info_schema->amount_field-2;i++){
		counter += info_schema->data_schema[i].amount;
	}	
	
	//Alocando em um ponteiro void* todas as informaçẽs do novo registro	
	new = malloc(counter);
	
	//Zerando o contador
	counter = 0;
	
	//Armazenando os valores que do registro que serão analisados
	for(i=0;i<info_schema->amount_field-2;i++){
		if(info_schema->data_schema[i].type == 'i'){
			scanf("%d",&(*(int*)(new + counter)));
			counter += info_schema->data_schema[i].amount;	
		}
		else if(info_schema->data_schema[i].type == 'd'){
			scanf("%lf",&(*(double*)(new + counter)));
			counter += info_schema->data_schema[i].amount;	
		}
		else{
			scanf("%s",(char*)(new + counter));
			counter += info_schema->data_schema[i].amount;	
		}
	}	
	
	//Pegando o \n
	scanf("%c",&aux);
	
	//Subfunção do knn responsável por realizar o algoritmo knn
	sub_knn(info_schema,info_data,new);	

	//Liberando o ponteiro void*
	free(new);
	
	//Subfunção do knn responsável por armazenar todos os dist e ordenálos	
	sub2_knn(info_schema,info_data,neighbor,option);
}

//Função principal - Main
int main(int argc, char *argv[]){
	
	void *new = NULL;	
	char *filename_schema;
	int optionInt = 0;
	char *optionChar;
	INFO_SCHEMA *info_schema;
	INFO_DATA *info_data;

	//Leitura do nome do arquivo schema
	filename_schema = read_name();

	//Leitura do conteúdo do arquivo schema
	info_schema = read_content_file_schema(filename_schema);	

	//O nome do arquivo schema já não é mais necessário logo será desalocado
	free(filename_schema);

	//Criação do arquivo .data
	info_data = create_data(info_schema);
	
	//Opções do programa
	while(optionInt != 1){
		
		//Leitura da opção
		optionChar = read_name();
	
		//Analizando qual é a opção
		if( strcmp(optionChar,"exit")  == 0 ){
			optionInt = 1;	
		}
		else if( strcmp(optionChar,"dump_schema") == 0 ){
			optionInt = 2;
		} 
		else if( strcmp(optionChar,"dump_data") == 0 ){
			optionInt = 3;
		}
		else if( strcmp(optionChar,"dump_nn") == 0 ){
			optionInt = 4;
		}
		else if( strcmp(optionChar,"knn") == 0 ){
			optionInt = 5;
		}
	
		//Liberando a opçãoChar
		free(optionChar);
	
		//Executando a opção digitada pelo usuário
		switch(optionInt){
	
			case EXIT:
				destroy_schema(info_schema);
				destroy_data(info_data);
				break;
			case DUMP_SCHEMA:
				dump_schema(info_schema);
				break;		
			case DUMP_DATA:
				dump_data(info_schema,info_data);
				break;
			case DUMP_NN:
				knn(info_schema,info_data,optionInt);
				break;
			case KNN:
				knn(info_schema,info_data,optionInt);
				break;
		}
	}

	return 0;
}
