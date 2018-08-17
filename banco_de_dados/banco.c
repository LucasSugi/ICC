#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD 1
#define TYPE 2

enum{

	OPTION,
	EXIT,
	DUMP_SCHEMA,
	DUMP_DATA,
	DUMP_INDEX,
	INSERT,
	SELECT,
	UPDATE_INDEX

};

typedef struct data_schema{

	char *field;
	char type;
	int order;
	int amount;

} DATA_SCHEMA;

typedef struct info{
	
	DATA_SCHEMA *schema;	
	char *filename_data;
	int tam;
	int total;

} INFO;

typedef struct data{
	
	void *file;
	char *filename_data;
	int amount_reg;

} DATA;

typedef struct file_idx{

	char *name;
	int read;

} FILE_IDX;

typedef struct index{

	FILE_IDX *file_idx;
	int amount_reg;
	int amount_idx;

} INDEX;


//Função responsável pela leitura do nome do arquivo e das opções requeridas
char *read_filename(){

	char *filename = NULL;
	size_t tam;
	
	//Leitura do nome com a função getline
	getline(&filename,&tam,stdin);

	//Eliminando o caracter '\n'
	tam = strlen(filename);
	filename[tam-1] = '\0';

	return filename;
}

//Função responsável pela leitura do conteúdo do arquivo schema
INFO *read_contentfile(char *filename){
	
	//Alocando a estrutura de dados que será utilizada para armanezar todas as informações do arquivo schema
	INFO *info = (INFO*) malloc(sizeof(INFO));

	FILE *fp = NULL;
	char  *aux = NULL;
	int tam, j, i, control = FIELD;

	fp = fopen(filename,"r");
	
	//Inicializando o tamanho da estrutura como 0
	info->tam = 0;
	
	//Alocando memória dinâmica para a variável aux
	aux = (char*) malloc(sizeof(char)*50);
	
	//Contando a quantidade de '\n' será possível saber quantos campos terão que ser armazenados
	while ( !feof(fp) ){
		aux[0] = fgetc(fp);
		if( aux[0] == '\n'){
			info->tam++;				
		}
	}	
	
	//Alocando a quantidade de campos necessária	
	info->schema = (DATA_SCHEMA*) malloc(sizeof(DATA_SCHEMA)*(info->tam));	

	//Inicializando as variáveis do conteúdo schema
	for(i=0;i<info->tam;i++){
		info->schema[i].order = 0;
		info->schema[i].amount = 0;
		info->schema[i].type = '\0';	
	}
	info->total = 0;

	//Colocando o cursor no início do arquivo
	fseek(fp,0,SEEK_SET);

	//Lendo o nome do arquivo .data (A primeira leitura ocorre e será ignorada)
	fscanf(fp,"%s",aux);
	fscanf(fp,"%s",aux);
	
	//Copiando o nome do arquivo .data para info->filename_data
	tam = strlen(aux);
	info->filename_data = (char*) malloc(sizeof(char)*(tam + 1));
	strcpy(info->filename_data,aux);

	//Inicializando as variáveis que serão usadas no laço while
	i = j = 0;

	//Leitura do conteúdo do arquivo
	while( !feof(fp) && i<info->tam ){
		//Armazenando a string em uma variável auxiliar
		fscanf(fp,"%s",aux);
	
		//Controle para que se alterne entre campo e tipo
		if(control == FIELD){
			//Se a string em aux for diferente de "order" então ela pode ser armazenada
			if( strcmp(aux,"order")  != 0){
				tam = strlen(aux);
				info->schema[i].field = (char*) malloc(sizeof(char)*(tam + 1)); 
				strcpy(info->schema[i].field,aux);
				control = TYPE;
				//Se a string em aux for igual a "order" então é setado 1
			} else {
				info->schema[i-1].order = 1;
				control = FIELD;
			}

		//Controle para que se alterne entre controle e tipo
		} else if(control == TYPE){
			
			//Se a string for inteiro será armazenado 'i'
			if( strcmp(aux,"int") == 0 ){
				info->schema[i].type = 'i';
				info->schema[i].amount = sizeof(int);

			//Se a string for double será armazenado 'd'
			} else if (strcmp(aux,"double") == 0 ){
				info->schema[i].type = 'd';
				info->schema[i].amount = sizeof(double);
			
			//Se a string não nenhum dos dois é porque ela é do tipo char 'c'
			} else {	
				while( aux[j] != '['){
		 			j++;
				}
				tam = j + 1;
				while( aux[j] != ']'){
					j++;	
				}
				aux[j] = '\0';
				info->schema[i].type = 'c';
				info->schema[i].amount = atoi(aux + tam);
				j = 0;
			}
			control = FIELD;
			i++;
		}	
	}

	//Armazenando a quantidade total de bytes
	for(i=0;i <info->tam; i++){
		info->total += info->schema[i].amount;
	}
	
	//Desalocando a variável aux
	free(aux);	

	//Fechando o arquivo
	fclose(fp);

	return info;
}

//Função responsável por imprimir na tela o arquivo schema
void dump_schema(INFO *info){

	int i;

	printf("table %s(%d bytes)\n",info->filename_data,info->total);

	for(i=0;i<info->tam;i++){
		printf("%s ",info->schema[i].field);	
	
		if(info->schema[i].type == 'i'){
			printf("int");
			if(info->schema[i].order == 0){
				printf("(%d bytes)\n",info->schema[i].amount);	
			} else {
				printf(" order(%d bytes)\n",info->schema[i].amount);
			}
		}

		else if(info->schema[i].type == 'd'){
			printf("double");
			if(info->schema[i].order == 0){
				printf("(%d bytes)\n",info->schema[i].amount);	
			} else {
				printf(" order(%d bytes)\n",info->schema[i].amount);
			}
		}

		else if(info->schema[i].type == 'c'){
			printf("char");
			if(info->schema[i].order == 0){
				printf("[%d](%d bytes)\n",info->schema[i].amount,info->schema[i].amount);	
			} else {
				printf("[%d] order(%d bytes)\n",info->schema[i].amount,info->schema[i].amount);
			}
		}
	}	
}

//Função responsável por desalocar todos os elementos da estrutura de informações do arquivo schema
void destroy_schema(INFO *info){

	int i;
	
	//Liberando o nome do arquivo .data
	free(info->filename_data);
	
	//Liberando os campos
	for(i=0;i<info->tam;i++){
		free(info->schema[i].field);	
	}	

	//Liberando o ponteiro schema e a estrutura de dados info
	free(info->schema); 
	free(info);
}

//Função responsável por ler o conteúdo do arquivo de dados
DATA *read_content_data(INFO *info){


	DATA *data = NULL;
	FILE *fp = NULL;
	int tam;
	
	//Alocando a estrutura de dados DATA
	data = (DATA*) malloc(sizeof(DATA));
	
	//Armazenando na estrutura DATA o nome do arquivo(filename).data
	tam = strlen(info->filename_data);
	data->filename_data = (char*) malloc(sizeof(char)*(tam + 6));		
	strcpy(data->filename_data,info->filename_data);
	strcat(data->filename_data,".data");
	
	//Abrindo o arquivo binário .data
	fp = fopen(data->filename_data,"rb");

	//Colocando o cursor do arquivo para o final
	fseek(fp,0,SEEK_END);	

	//Tamanho do arquivo em bytes
	tam = ftell(fp);

	//Ao divir o tamanho do arquivo em bytes pelo tamanho de cada registro é possível saber quantos registros há no arquivo
	data->amount_reg = tam / info->total;

	//Fechando o arquivo
	fclose(fp);
	
	return data;	

}

//Função responsável por fazer o dump do arquivo data
void dump_data(DATA *data, INFO *info){

	int i,j,tam,counter = 0;
	FILE *fp = NULL;

	fp = fopen(data->filename_data,"rb");

	//Colocando o cursor do arquivo para o final
	fseek(fp,0,SEEK_END);	

	//Tamanho do arquivo em bytes
	tam = ftell(fp);

	//Alocando a quantidade de bytes necessária para armazenar o arquivo binário	
	data->file = malloc(tam);

	//Colocando cursor no início
	fseek(fp,0,SEEK_SET);

	//Armazenado todo o arquivo em um ponteiro void*
	fread(data->file,tam,1,fp);
	
	//Fechando o arquivo
	fclose(fp);
	
	/*Uma variável counter permite o deslocamento no vetor void*. Como sabemos o os campos existentes no registro, podemos ler
	a quantidade certa de bytes por ver*/
	for(i=0;i<data->amount_reg;i++){
		for(j=0;j<info->tam;j++){
			printf("%s =",info->schema[j].field);
			if(info->schema[j].type == 'i'){
				printf(" %d\n",*(int*)(data->file + counter));
				counter += info->schema[j].amount;
			} 
			else if(info->schema[j].type == 'd'){
				printf(" %.2lf\n",*(double*)(data->file + counter));
				counter += info->schema[j].amount; 
			}
			else if(info->schema[j].type == 'c'){
				printf(" %s\n",(char*)(data->file + counter));
				counter += info->schema[j].amount;
			}
		} 
	}
	
	free(data->file);
	data->file = NULL;
}

//Função que desaloca a estrutura de dados DATA
void destroy_data(DATA *data){

	free(data->filename_data);
	free(data);
}

//Função que cria o nome do arquivo idx
void create_name_idx(INFO *info, INDEX *index, int i){
	
	int tam;

	//Armazenando o tamanho da alocação necessária
	tam = strlen(info->filename_data);			
	tam += strlen(info->schema[i].field);
	//O número seis é armazenado pois há os caracteres (-.idx) mais o '\0'
	tam += 6;

	//Alocando a quantidade de nome necessária
	index->file_idx[i].name = (char*) malloc(sizeof(char)*tam);

	//Concatenando com as strings campo e nome da tabela
	strcpy(index->file_idx[i].name,info->filename_data);
	strcat(index->file_idx[i].name,"-");
	strcat(index->file_idx[i].name,info->schema[i].field);
	strcat(index->file_idx[i].name,".idx");
}

//Função responsável por criar o arquivo de indíces
void transfer_data(INDEX *index,DATA *data,INFO *info, int i, int j){
	
	FILE *fp = NULL;
	FILE *idx = NULL;
	int counter = 0, k, offset = 0;
	
	//Abertura do arquivo .data
	fp = fopen(data->filename_data,"rb");
		
	//Criando o arquivo .idx
	idx = fopen(index->file_idx[i].name,"wb");	
	
	//Alocando a quantidade necessária de bytes que precisam ser lidos	
	data->file = malloc(index->file_idx[j].read);	
	
	//Laço utilizado para saber a partir de quantos bytes deve ser lido o arquivo	
	for(k=0;k<i;k++){
		if(info->schema[j].type == 'i'){
			counter += info->schema[k].amount;
		}
	}
	
	//Tranferindo dados do arquivo .data para o arquivo .idx	
	k = 0;		
	while(k<data->amount_reg){
		fseek(fp,counter,SEEK_SET);
		fread(data->file,index->file_idx[j].read,1,fp);
		counter += info->total;
		fwrite(data->file,index->file_idx[j].read,1,idx);
		fwrite(&offset,sizeof(int),1,idx);
		offset += info->total;
		k++;
	}
	
	//Liberando o ponteiro void*
	free(data->file);
	data->file = NULL;

	//Fechando o arquivo .data
	fclose(fp);

	//Fechando arquivo .idx
	fclose(idx);
}

//Função que cria o arquivo de indíces
INDEX *create_index(DATA *data, INFO *info){

	int i, j,counter = 0;
	INDEX *index = NULL;

	//O primeiro laço é utilizado para saber quantos arquivos index devem ser criados
	for(i=0;i<info->tam;i++){
		if(info->schema[i].order == 1){
			counter++;
		}
	}
	
	//Alocando a estrutura que será utilizada para os índices
	index = (INDEX*) malloc(sizeof(INDEX));

	//Armazenando a quantidade de arquivos .idx
	index->amount_idx = counter;
	
	//Alocando a quantidade necessária para armazenar os nomes
	index->file_idx = (FILE_IDX*) malloc(sizeof(FILE_IDX)*(index->amount_idx));

	//Armazena a quantidade de registros presentes em index
	index->amount_reg = data->amount_reg;
	
	j = 0;
	for(i=0;i<info->tam;i++){
		if(info->schema[i].order == 1){
			if(info->schema[i].type == 'i'){
				//Armazenando na estrutura index a quantidade de bytes que deverá ser lido o arquivo
				index->file_idx[j].read = info->schema[i].amount;
				
				//Função responsável por criar o nome do arquivo de índice	
				create_name_idx(info,index,j);

				//Transferindo dados do arquivo .data para o arquivo .idx
				transfer_data(index,data,info,i,j);
				j++;

			}
			else if(info->schema[i].type == 'd'){
				//Armazenando na estrutura index a quantidade de bytes que deverá ser lido o arquivo
				index->file_idx[j].read = info->schema[i].amount;

				//Função responsável por criar o nome do arquivo de índice	
				create_name_idx(info,index,j);

				//Transferindo dados do arquivo .data para o arquivo .idx
				transfer_data(index,data,info,i,j);
				j++;
			}
			else if(info->schema[i].type == 'c'){
				//Armazenando na estrutura index a quantidade de bytes que deverá ser lido o arquivo
				index->file_idx[j].read = info->schema[i].amount;

				//Função responsável por criar o nome do arquivo de índice	
				create_name_idx(info,index,j);

				//Transferindo dados do arquivo .data para o arquivo .idx
				transfer_data(index,data,info,i,j);
				j++;
			}	
		}
	}
	return index;
}

//Função que faz o dump do arquivo .idx
void dump_index(INDEX *index, DATA *data){
	
	FILE *fp = NULL;
	int i,j;

	//Primeiro laço para imprimir todos os arquivos
	for(i=0;i<index->amount_idx;i++){
		//Abertura do arquivo
		fp = fopen(index->file_idx[i].name,"rb");
		
		//Alocando a quantidade necessária para poder ler do arquivo
		data->file = malloc(index->file_idx[i].read);
		
		//Imprime todos os indíces dos registros setados como order	
		for(j=0;j<index->amount_reg;j++){

			//Impressão do índice - É carregado um índice por ver em um ponteiro void*
			fread(data->file,index->file_idx[i].read,1,fp);	
			if(index->file_idx[i].read == sizeof(int)){
				printf("%d = ",*(int*)data->file);
			} 
			else if(index->file_idx[i].read == sizeof(double)){
				printf("%lf = ",*(double*)data->file);
			} else{
				printf("%s = ",(char*)data->file);
			}
			
			//Impressão do ofsset
			fread(data->file,sizeof(int),1,fp);
			printf("%d\n",*(int*)data->file);
		}
		//Fechando o arquivo e desalocando a memória dinamica caso seja necessário ler outro arquivo
		fclose(fp);
		free(data->file);
		data->file = NULL;
	}
}

//Função que desaloca a estrutura index
void destroy_index(INDEX *index){

	int i;
	
	//Desaloca os nomes
	for(i=0;i<index->amount_idx;i++){
		free(index->file_idx[i].name);	
	}
	
	free(index->file_idx);
	free(index);
}

//Subfunção da ordenação do arquivo index - Ordenação de char
void ordChar(void *file, int counter, int aux,int tam){

	void *swap = malloc(tam);
	
	/*Com a função strcmp é feito uma comparação entre as strings. Caso seja necessário a troca é feito a troca de memória com memcpy*/
	if(strcmp((char*)(file + counter - aux),(char*)(file + counter)) > 0){
		memcpy(swap,(file + counter - aux),tam);
		memcpy((file + counter - aux),(file + counter),tam);
		memcpy((file + counter),swap,tam);

		memcpy(swap,(file + counter - aux + tam),sizeof(int));
		memcpy((file + counter - aux + tam),(file + counter + tam),sizeof(int));
		memcpy((file + counter + tam),swap,sizeof(int));
	}
		
	free(swap);
}

//Subfunção da ordenação do arquivo index - Ordenação de doubles
void ordDouble(void *file, int counter, int aux){

	double swap;
		
	//Comparação entre dois dubles. Caso seja necessário há uma troca com a função memcpy	
	if( *(double*)(file + counter - aux) > *(double*)(file + counter) ){
		memcpy(&swap,(file + counter - aux),sizeof(double));
		memcpy((file + counter - aux),(file + counter),sizeof(double));
		memcpy((file + counter),&swap,sizeof(double));

		memcpy(&swap,(file + counter - aux + sizeof(double)),sizeof(int));
		memcpy((file + counter - aux + sizeof(double)),(file + counter + sizeof(double)),sizeof(int));
		memcpy((file + counter + sizeof(double)),&swap,sizeof(int));
	}
}

//Subfunção da ordenação do arquivo index - Ordenação de inteiros
void ordInt(void *file, int counter, int aux){

	int swap;
	
	//Comparação entre dois int. Caso seja necessário há uma troca com a função memcpy	
	if( *(int*)(file + counter - aux) > *(int*)(file + counter) ){
		memcpy(&swap,(file + counter - aux),sizeof(int));
		memcpy((file + counter - aux),(file + counter),sizeof(int));
		memcpy((file + counter),&swap,sizeof(int));

		memcpy(&swap,(file + counter - aux + sizeof(int)),sizeof(int));
		memcpy((file + counter - aux + sizeof(int)),(file + counter + sizeof(int)),sizeof(int));
		memcpy((file + counter + sizeof(int)),&swap,sizeof(int));
	}
}

//Função que ordena o arquivo de índices
void ordenation_index(INDEX *index, DATA *data, void *file, int pos){

	int i, j, counter, aux;
	
	/*Com a possibilidades de haver várias arquivos .idx na qual eles terão que ser lidos de forma diferente(int,double,char),
	um laço for é utilizado para percorrer os nomes de todos os arquivos verificando como eles devem ser lidos. Com isso será,
	chamado a função subfunção correta pare realizar a ordenação*/	
	for(i=1;i<data->amount_reg;i++){
		aux = counter = index->file_idx[pos].read + sizeof(int);
		for(j=0;j<data->amount_reg-i;j++){
			if(index->file_idx[pos].read == sizeof(int)){
				ordInt(file,counter,aux);
			}
			else if(index->file_idx[pos].read == sizeof(double)){
				ordDouble(file,counter,aux);
			}
			else {
				ordChar(file,counter,aux,index->file_idx[pos].read);
			}
			counter += aux;
		}
	}
}

//Função que atualiza os índices do arquivo .idx
void update_index(INDEX *index, DATA *data){

	FILE *fp = NULL;
	void *file = NULL;
	int tam, i;

	//Atualizando a quantidade de índices
	index->amount_reg = data->amount_reg;
	
	for(i=0;i<index->amount_idx;i++){
		//Abertura do arquivo de índices
		fp = fopen(index->file_idx[i].name,"rb");
			
		//Colocando cursor no final
		fseek(fp,0,SEEK_END);
		
		//Armazenando o tamanho do arquivo
		tam = ftell(fp);

		//Alocar a quantidade necessária para o ponteiro void*
		file = malloc(tam);
	
		//Colocando o cursor no início novamente
		fseek(fp,0,SEEK_SET);

		//Carregando todo o arquivo para a memória
		fread(file,tam,1,fp);
		
		//Fechando o arquivo
		fclose(fp);
		
		//Ordenação do arquivo de índices	
		ordenation_index(index,data,file,i);	
		
		//Sobreescrevendo o arquivo
		fp = fopen(index->file_idx[i].name,"wb");
			
		//Escrevendo no arquivo
		fwrite(file,tam,1,fp);

		//Fechando o arquivo
		fclose(fp);
		
		//Desaloca o ponteiro void*	
		free(file);
		file = NULL;
	}
}

//Subfunção da opção insert na qual é adicionado um novo índice no arquivo .idx
void insert_idx(INDEX *index,DATA *data, INFO *info,int tam, void *insert, int pos){

	FILE *fp = NULL;
	int offset;
	
	//Abertura do arquivo idx
	fp = fopen(index->file_idx[pos].name,"a + b");

	//Escrevendo o índice no arquivo
	fwrite(insert,tam,1,fp);
	
	//Pegando o offset do novo índice
	offset = (data->amount_reg - 1) * info->total;

	//Escrevendo o novo offset
	fwrite(&offset,sizeof(int),1,fp);

	//Fechando do arquivo idx
	fclose(fp);
}


//Função que insere um novo registro
void insert(INFO *info, DATA *data, INDEX *index){

	int i, pos = 0;
	char aux;
	void *insert = NULL;
	FILE *fp = NULL;
	
	//Abrindo o arquivo binário .data para adicionar um registro
	fp = fopen(data->filename_data,"a + b");

	//A quantidade de registros aumenta
	data->amount_reg++;	
	
	/*Um laço for é utilizado para percorrer todos os campos a fim de saber como deve ser feita a leitura. Sabendo isso,
	lemos do stdin o valor armazenando-o em um ponteiro void* que depois será escrito no arquivo .data e no arquivo .idx*/
	for(i=0;i<info->tam;i++){
		if(info->schema[i].type == 'i'){
			insert = malloc(sizeof(int));
			scanf("%d",&(*(int*)insert));
			fwrite(insert,sizeof(int),1,fp);
			if(info->schema[i].order == 1){
				insert_idx(index,data,info,sizeof(int),insert,pos);
				pos++;
			}
			free(insert);
			insert = NULL;
		}
		else if(info->schema[i].type == 'd'){
			insert = malloc(sizeof(double));
			scanf("%lf",&(*(double*)insert));
			fwrite(insert,sizeof(double),1,fp);
			if(info->schema[i].order == 1){
				insert_idx(index,data,info,sizeof(double),insert,pos);
				pos++;
			}
			free(insert);
			insert = NULL;
		}
		else if(info->schema[i].type == 'c'){
			insert = calloc(1,info->schema[i].amount);
			scanf("%s",(char*)insert);
			fwrite(insert,info->schema[i].amount,1,fp);
			if(info->schema[i].order == 1){
				insert_idx(index,data,info,info->schema[i].amount,insert,pos);
				pos++;
			}
			free(insert);
			insert = NULL;
		}
	}
		
	/*Observação: Note que confome são adicionados novos registros, eles são armazenados nos dois arquivos(.data e .idx), contudo
	o arquivo .idx não têm a quantidade de indíces atualizados, então para ele é como se não houvesse mais índices*/ 

	//Scanf necessária para pegar o último \n	
	scanf("%c",&aux);

	//Fechando o arquivo .data
	fclose(fp);
}

//Busca binária - Char
int search_binary_char(FILE *fp, void *key, int tam, int start, int end, int *counter, int *offset){
	
	char *cmp = malloc(tam-sizeof(int));
	int middle;
	
	//Condição de parada da recursão
	if(start<=end){	
		//Pegando o meio do vetor
		middle = (start + end) / 2;
	
		//Mudando o cursor para o meio
		fseek(fp,middle*tam,SEEK_SET);
		
		//Lendo a string
		fread(cmp,tam-sizeof(int),1,fp);
		
		//Caso o valor seja encontrado é retornado 1 para indicar sucesso - Caso contrário é feito a chamada recursiva	
		if( strcmp(cmp,(char*)key) == 0 ){
			fread(offset,sizeof(int),1,fp);
			free(cmp);
			cmp = NULL;
			printf("%d\n",*counter);
			return 1;
		}
		else if( strcmp((char*)key,cmp) < 0  && start != end){
			free(cmp);
			cmp = NULL;
			(*counter)++;
			return search_binary_char(fp,key,tam,start,middle-1,counter,offset);	
		}
		else if( strcmp((char*)key,cmp) > 0 && start != end){
			free(cmp);
			cmp = NULL;
			(*counter)++;
			return search_binary_char(fp,key,tam,middle + 1,end, counter,offset);	
		}
	}
	if(cmp != NULL){
		free(cmp);
		cmp = NULL;
	}
	
	return 0;
}

//Busca binária - Double
int search_binary_double(FILE *fp, void *key, int tam, int start, int end, int *counter, int *offset){
	
	double cmp;
	int middle;
	
	//Condição de parada da recursão
	if(start<=end){	
		//Pegando o meio do vetor
		middle = (start + end) / 2;
	
		//Mudando o cursor para o meio
		fseek(fp,middle*tam,SEEK_SET);
		
		//Lendo o double	
		fread(&cmp,sizeof(double),1,fp);
		
		//Caso o valor seja encontrado é retornado 1 para indicar sucesso - Caso contrário é feito a chamada recursiva	
		if( cmp == *(double*)key ){
			fread(offset,sizeof(int),1,fp);
			printf("%d\n",*counter);
			return 1;
		}
		else if( *(double*)key < cmp && start != end){
			(*counter)++;
			return search_binary_double(fp,key,tam,start,middle-1,counter,offset);	
		}
		else if( *(double*)key > cmp && start != end){
			(*counter)++;
			return search_binary_double(fp,key,tam,middle + 1,end, counter,offset);	
		}
	}
	return 0;
}

//Busca binária - Int
int search_binary_int(FILE *fp, void *key, int tam, int start, int end, int *counter, int *offset){
	
	int cmp;
	int middle;
	
	//Condição de parada da recursão
	if(start<=end){	
		//Pegando o meio do vetor
		middle = (start + end) / 2;
	
		//Mudando o cursor para o meio
		fseek(fp,middle*tam,SEEK_SET);
		
		//Lendo o inteiro	
		fread(&cmp,sizeof(int),1,fp);

		//Caso o valor seja encontrado é retornado 1 para indicar sucesso - Caso contrário é feito a chamada recursiva	
		if( cmp == *(int*)key ){
			fread(offset,sizeof(int),1,fp);
			printf("%d\n",*counter);
			return 1;
		}
		else if( *(int*)key < cmp && start != end){
			(*counter)++;
			return search_binary_int(fp,key,tam,start,middle-1,counter,offset);	
		}
		else if( *(int*)key > cmp && start != end){
			(*counter)++;
			return search_binary_int(fp,key,tam,middle + 1,end,counter,offset);	
		}
	}
	return 0;
}

//Busca sequencial - Char
int sequential_search_char(DATA *data, INDEX *index,FILE *fp, void *key, int *counter, int pos, int *offset){

	int i, j, stop;
	void *cmp = malloc(index->file_idx[pos].read);
	
	/*A variável stop é a condição de parada do laço for. Ela recebe a diferença entre a quantidade dos indícices atualizados
	e os índices desatualizados. Com isso é possível saber quantas vezes o laço for precisa "rodar"*/
	stop = data->amount_reg - index->amount_reg;
	
	//O j a quantidade do primeiro indíce do arquivo .idx que está desatualizado para começar a busca
	j = index->amount_reg;
	
	//Caso não tenhamos mais índices o laço nem é executado	
	if(stop > 0){
		/*Nesse laço percorremos o arquivo .idx a procura da chave digitada pelo usuário, para isso lemos um valor por vez
		e percorremos o arquivo com a função fseek*/
		for(i=0;i<stop;i++,j++){
			fseek(fp,j*(index->file_idx[pos].read + sizeof(int)),SEEK_SET);
			fread(cmp,index->file_idx[pos].read,1,fp);
			(*counter)++;					
			if( strcmp((char*)cmp,(char*)key) == 0){
				fread(offset,sizeof(int),1,fp);
				free(cmp);
				printf("%d\n",*counter);
				return 1;
			}
		}	
	}
	
	free(cmp);

	return 0;
}

//Busca sequencial - Double
int sequential_search_double(DATA *data, INDEX *index,FILE *fp, void *key, int *counter, int pos, int *offset){

	int i, j, stop;
	void *cmp = malloc(sizeof(double));

	/*A variável stop é a condição de parada do laço for. Ela recebe a diferença entre a quantidade dos indícices atualizados
	e os índices desatualizados. Com isso é possível saber quantas vezes o laço for precisa "rodar"*/
	stop = data->amount_reg - index->amount_reg;

	//O j a quantidade do primeiro indíce do arquivo .idx que está desatualizado para começar a busca
	j = index->amount_reg;
	
	//Caso não tenhamos mais índices o laço nem é executado	
	if(stop > 0){
		/*Nesse laço percorremos o arquivo .idx a procura da chave digitada pelo usuário, para isso lemos um valor por vez
		e percorremos o arquivo com a função fseek*/
		for(i=0;i<stop;i++,j++){
			fseek(fp,j*(index->file_idx[pos].read + sizeof(int)),SEEK_SET);
			fread(cmp,sizeof(double),1,fp);
			(*counter)++;
			if( *(double*)cmp == *(double*)key){
				fread(offset,sizeof(int),1,fp);
				free(cmp);
				printf("%d\n",*counter);
				return 1;
			}					
		}	
	}
	
	free(cmp);

	return 0;
}

//Busca sequencial - Int
int sequential_search_int(DATA *data, INDEX *index,FILE *fp, void *key, int *counter, int pos, int *offset){

	int i, j, stop;
	void *cmp = malloc(sizeof(int));

	/*A variável stop é a condição de parada do laço for. Ela recebe a diferença entre a quantidade dos indícices atualizados
	e os índices desatualizados. Com isso é possível saber quantas vezes o laço for precisa "rodar"*/
	stop = data->amount_reg - index->amount_reg;

	//O j a quantidade do primeiro indíce do arquivo .idx que está desatualizado para começar a busca
	j = index->amount_reg;
	
	//Caso não tenhamos mais índices o laço nem é executado	
	if(stop > 0){
		/*Nesse laço percorremos o arquivo .idx a procura da chave digitada pelo usuário, para isso lemos um valor por vez
		e percorremos o arquivo com a função fseek*/
		for(i=0;i<stop;i++,j++){
			fseek(fp,j*(index->file_idx[pos].read + sizeof(int)),SEEK_SET);
			fread(cmp,sizeof(int),1,fp);
			(*counter)++;					
			if( *(int*)cmp == *(int*)key){
				fread(offset,sizeof(int),1,fp);
				free(cmp);
				printf("%d\n",*counter);
				return 1;
			}
		}	
	}
	
	free(cmp);

	return 0;
}

//Função que imprime o valor do campo correspondente ao registro pedido pelo usuário
void print_search(INFO *info, DATA *data, char *field, int offset){

	int counter = 0, i = 0, pos;
	FILE *fp = NULL;
	void *value = NULL;

	//Percorrendo os campos para saber iniciar o cursor no arquivo na posição correta	
	pos = i;
	while( strcmp(field,info->schema[i].field) != 0 && i<info->tam){
		if(info->schema[i].type == 'i'){
			counter += sizeof(int);
		}
		else if(info->schema[i].type == 'd'){
			counter += sizeof(double);
		} 
		else {
			counter += info->schema[i].amount;
		}		
		i++;
		pos = i;
	}
	

	//Aloca em value a quantidade necessária para ler o valor do arquivo
	value = malloc(info->schema[pos].amount);

	//Abrindo o arquivo .data
	fp = fopen(data->filename_data,"rb");
	
	//Posionando o cursor no arquivo no campo que deve ser lido - É utilizado o offset do registro + o valor do campo inicial
	fseek(fp,counter + offset,SEEK_SET);
	
	//Lendo o campo no arquivo
	fread(value,info->schema[pos].amount,1,fp);
	
	//Imprimindo o valor do campo encontrado
	if(info->schema[pos].type == 'i'){
		printf("%d\n",*(int*)value);
	}
	else if(info->schema[pos].type == 'd'){
		printf("%.2lf\n",*(double*)value);
	}
	else {
		printf("%s\n",(char*)value);
	}

	//Fechando o arquivo e liberando memória
	fclose(fp);	
	free(value);
}

//Realizando a busca
/*A função funcionará da seguinte maneira:
-O arquivo .idx será aberto e por meio de testes condicionais será chamada a busca binária
-A busca binária é reaoizada de acordo com o modo que se deve ler o arquivo(int,double,char)
-Caso o valor seja encontrado na busca binária é retornado 1, se não é retornado  0
-O valor não sendo encontrado é realizado então uma busca sequencial
-Caso encontre o valor é chamado a função que imprime o campo do registro encontrado se não é impresso que o valor não foi encontrado
*/
void search(INFO *info, DATA *data,INDEX *index,int pos, void *key, char *field){

	FILE *fp = NULL;
	int counter = 1, ret, offset;

	//Abrindo arquivo .idx
	fp = fopen(index->file_idx[pos].name,"rb");
	
	if(index->file_idx[pos].read == sizeof(int)){
		ret = search_binary_int(fp,key,index->file_idx[pos].read + sizeof(int),0,index->amount_reg - 1,&counter,&offset);
		if(ret == 0){
			ret = sequential_search_int(data,index,fp,key,&counter,pos,&offset);
			if(ret == 0){
				printf("%d\n",counter);
				printf("value not found\n");
			} else {
				print_search(info,data,field,offset);
			}
		} else {
			print_search(info,data,field,offset);	
		}
	} 	
	else if(index->file_idx[pos].read == sizeof(double)){
		ret = search_binary_double(fp,key,index->file_idx[pos].read + sizeof(int),0,index->amount_reg -1,&counter,&offset);
		if(ret == 0){
			ret = sequential_search_double(data,index,fp,key,&counter,pos,&offset);
			if(ret == 0){
				printf("%d\n",counter);
				printf("value not found\n");
			} else {
				print_search(info,data,field,offset);
			}
		} else {
			print_search(info,data,field,offset);
		}
	}
	else {
		ret = search_binary_char(fp,key,index->file_idx[pos].read + sizeof(int),0,index->amount_reg - 1,&counter,&offset);		      if(ret == 0){
			ret = sequential_search_char(data,index,fp,key,&counter,pos,&offset);
			if(ret == 0){
				printf("%d\n",counter);
				printf("value not found\n");
			} else {
				print_search(info,data,field,offset);
			}
		} else {
			print_search(info,data,field,offset);
		}
	}

	//Fechando arquivo .idx
	fclose(fp);
}

//Função que faz uma busca no arquivo de índices
void select_idx(INFO *info,DATA *data,INDEX *index){

	int i, pos, counter = 0;
	char *field_idx = NULL, *field = NULL, aux;
	void *key = NULL;
	
	//Usuário digita o campo na qual será realizado a busca no arquivo de índices
	field_idx = read_filename();	
	
	//O campo é comparado com o arquivo schema para saber se o valor a ser armazenado é do tipo int,double ou char	
	for(i=0;i<info->tam;i++){
		if(strcmp(field_idx,info->schema[i].field) == 0){
			key = calloc(1,info->schema[i].amount);
			pos = i;	
			break;
		}
		if(info->schema[i].order == 1){
			counter++;
		}	
	}

	//Armazenando o valor a ser buscando no arquivo .idx	
	if(info->schema[pos].amount == sizeof(int)){
		scanf("%d",&(*(int*)key));	
	}
	else if(info->schema[pos].amount == sizeof(double)){
		scanf("%lf",&(*(double*)key));	
	}
	else {
		scanf("%s",(char*)key);
	}

	//Pegando o caracter \n
	scanf("%c",&aux);
	
	//Usuário digita o campo do registro que quer saber o valor
	field = read_filename();
	
	/*Caso o campo possua um arquivo de índices corresponde é então realizado uma busca. Caso contrário é informado ao usuário
	que o arquivo não existe e a busca não é efetuada*/
	if(info->schema[pos].order == 1){
		search(info,data,index,counter,key,field);
	} else {
		printf("index not found\n");
	}

	free(field_idx);
	free(field);
	free(key);
}
	
//Função principal
int main(int argc, char *argv[]){

	char *filename_schema = NULL;
	char *optionChr = NULL;
	int optionInt = 0;
	INFO *info = NULL;
	DATA *data = NULL;
	INDEX *index = NULL;

	
	//Lendo o nome do arquivo de dados(schema)
	filename_schema = read_filename();

	//Lendo o conteúdo do arquivo de dados (schema)
	info = read_contentfile(filename_schema);
	
	//O nome do arquivo schema já não é mais necessário logo será desalocado
	free(filename_schema);

	//Função que lê o conteúdo de dados do arquivo .data
	data = read_content_data(info);

	//Função responsável por criar o arquivo de indíces
	index = create_index(data,info);

	//Atualizando os índices
	update_index(index,data);

	//Menu contendo as opções que o usuário pode requerir	
	while(optionInt != 1){
		//Armazena a opção que o usuário deseja
		optionChr = read_filename();
	
		//Com a função strcmp fazemos uma comparação com as opções e setamos em "optionInt" o valor adequado para o switch
		if(strcmp(optionChr,"exit") == 0){
			optionInt = 1;	
		} 
		else if( strcmp(optionChr,"dump_schema") == 0 ){
			optionInt = 2;
		}
		else if( strcmp(optionChr,"dump_data") == 0){
			optionInt = 3;
		}
		else if( strcmp(optionChr,"dump_index") == 0){
			optionInt = 4;
		}
		else if( strcmp(optionChr,"insert") == 0){
			optionInt = 5;
		}
		else if( strcmp(optionChr,"select") == 0){
			optionInt = 6;
		}
		else if( strcmp(optionChr,"update_index") == 0){
			optionInt = 7;
		}
		
		//Realiza a opção requerida pelo usuário
		switch(optionInt){
			//Opção "EXIT" - Sair do programa desalocando toda memória dinâmica
			case EXIT:
			destroy_schema(info);
			destroy_data(data);
			destroy_index(index);
			break;

			//Opção "DUMP_SCHEMA" - Faz o dump do arquivo schema
			case DUMP_SCHEMA:
			dump_schema(info);
			break;
			
			//Opção "DUMP_DATA" - Faz o dump do arquivo de dados
			case DUMP_DATA:
			dump_data(data,info);
			break;
			
			//Opção "DUMP_INDEX" - Faz o dump do arquivo index
			case DUMP_INDEX:
			dump_index(index,data);
			break;

			//Opção "INSERT" - Insere um novo registro
			case INSERT:
			insert(info,data,index);
			break;

			case SELECT:
			select_idx(info,data,index);
			break;
			
			//Opção "UPDATE_INDEX" - Atualiza os indíces do arquivo .idx			
			case UPDATE_INDEX:
			update_index(index,data);
			break;

		}
		//Libera a string armazenada
		free(optionChr);
		optionChr = NULL;
	}

	return 0;
}
