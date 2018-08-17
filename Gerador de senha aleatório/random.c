#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define NUM_NUMBER 10
#define MIN_LETTER 26
#define MAX_LETTER 26
#define MAX_SIMBOL 32
#define LIMIT_SIMBOL1 15
#define LIMIT_SIMBOL2 7
#define LIMIT_SIMBOL3 6
#define LIMIT_SIMBOL4 4

//Estrutura contendo as informações dos caracteres
typedef struct {
	
	//Informa qual o tipo de cartere utilizado antes	
	int previous;
	//Informa o tamanho da senha
	int size;
	//Armazena quais tipos de carteres deverão compor a senha
	int *vector;
	//Vetor contendo a senha
	int *password;

} OPTION;

//Função responsável por gerar símbolos de forma aleatória
int generate_random_simbol(){
	
	int i,j;
	int value;
	int limits;
	int *vector = (int*) malloc(sizeof(int) * MAX_SIMBOL);
	
	//Populando o vetor
	j = 33;
	limits = LIMIT_SIMBOL1;
	for(i=0;i<LIMIT_SIMBOL1;i++){
		vector[i] = j++;
	}
	j = 58;
	limits += LIMIT_SIMBOL2;
	for(;i<limits;i++){
		vector[i] = j++;
	}
	j = 91;
	limits += LIMIT_SIMBOL3;
	for(;i<limits;i++){
		vector[i] = j++;
	}
	j = 123;
	limits += LIMIT_SIMBOL4;
	for(;i<limits;i++){
		vector[i] = j++;
	}

	//Sorteio do número
	i = rand() % MAX_SIMBOL;
	value = vector[i];
	
	//Desalocando vetor
	free(vector);


	return value;
}

//Função responsável por gerar uma letra maiúscula aleatória
int generate_random_max_letter(){

	int i,j;
	int value;
	int *vector = (int*) malloc(sizeof(int) * MAX_LETTER);
	
	//Populando o vetor
	j = 65;
	for(i=0;i<MAX_LETTER;i++){
		vector[i] = j++;
	}

	//Sorteio do número
	i = rand() % MAX_LETTER; 
	value = vector[i];

	//Desalocando o vetor
	free(vector);

	//Retorno do valor
	return value;

}

//Função responsável por gerar uma letra minúscula aleatória
int generate_random_min_letter(){

	int i,j;
	int value;
	int *vector = (int*) malloc(sizeof(int) * MIN_LETTER);
	
	
	//Populando o vetor
	j = 97;
	for(i=0;i<MIN_LETTER;i++){
		vector[i] = j++;
	}

	//Sorteio do número
	i = rand() % MIN_LETTER; 
	value = vector[i];

	//Desalocando o vetor
	free(vector);

	//Retorno do valor
	return value;

}

//Função responsável por gerar um valor aleatório
int generate_random_number(){
	
	int i,j;
	int value;
	int *vector = (int*) malloc(sizeof(int) * NUM_NUMBER);

	
	//Populando o vetor
	j = 48;
	for(i=0;i<NUM_NUMBER;i++){
		vector[i] = j++;
	}

	//Sorteio do número
	i = rand() % NUM_NUMBER; 
	value = vector[i];

	//Desalocando o vetor
	free(vector);

	//Retorno do valor
	return value;
}

//Analisando o tamanho da senha e distruindo os caracteres a partir dessa informação
OPTION *create_option(int size_password){
	
	int i;
	int number,maxLetter,minLetter,simbol;
	int remainder;
	OPTION *option = (OPTION*) malloc(sizeof(OPTION));	

	//Tamanho da senha
	option->size = size_password;
		
	//Caracter anterior
	option->previous = 0;
	
	//Vetor contendo as opções
	option->vector = (int*) malloc(sizeof(int) * size_password);
		
	//Flag indicando se a opção já foi usada ou não
	option->password = (int*) malloc(sizeof(int) * size_password);

	//Inicializando
	for(i=0;i<size_password;i++){
		option->password[i] = 0;
	}

	//40% da senha será composta por números
	number = 0.4 * size_password;

	//30% da senha será composta por letras minúsculas
	minLetter = 0.3 * size_password;

	//20% da senha será composta por letras maiúsculas
	maxLetter = 0.2 * size_password;

	//10% da senha será composta por símbolos 
	simbol = 0.1 * size_password;

	//Pelo fato de termos que usar valores inteiros, haverá casos em que irá sobrar um resto
	remainder = size_password - (minLetter + maxLetter + number + simbol); 
	
	//Distribuição do resto
	while(remainder>0){
		if(remainder>0){
			simbol++;
			remainder--;
		}
		if(remainder>0){
			number++;
			remainder--;
		}
		if(remainder>0){
			maxLetter++;
			remainder--;
		}
		if(remainder>0){
			minLetter++;
			remainder--;
		}
	}

	//Zerando valores
	i = 0;

	//Armazenando as porcentagens
	while(number>0){
		option->vector[i++] = 1;
		number--;
	}
	while(minLetter>0){
		option->vector[i++] = 2;
		minLetter--;
	}
	while(maxLetter>0){
		option->vector[i++] = 3;
		maxLetter--;
	}
	while(simbol>0){
		option->vector[i++] = 4;
		simbol--;
	}
	
	return option;
}

//Desalocando as opções
void destroy_option(OPTION *option){

	free(option->password);
	free(option->vector);
	free(option);

}

//Randomizando a senha
void random_password(OPTION *option){

	int i,j;
	int swap;	
	
	//Para randomizar a senha, as posições dos caracteres são trocadas randomicamente
	for(i=0;i<option->size;i++){
		j = rand() % option->size;
		swap = option->vector[j];
		if(option->vector[i] != swap){
			option->vector[j] = option->vector[i];
			option->vector[i] = swap;
			swap = option->password[j];
			option->password[j] = option->password[i];
			option->password[i] = swap;
		}
		else{
			i--;	
		}
	}	
}

//Função responsável por verificar se o caracter já existe na senha
void verify_character(int *k,int value,int *j,OPTION *option){

	int i;
	int flag = 0;	

	//Verificação
	for(i=0;i<*j;i++){
		//Verificação a parte para letras, para que não haja minúsculas e nem maiusculas iguais
		if(isalpha(option->password[i])){
			if(toupper(option->password[i]) == toupper(value)){
				flag = 1;
			}	
		}
		//Verificação para números e símbolos
		else{
			if(option->password[i] == value){
				flag = 1;
			}	
		}
	}
		
	//Flag utilizado para saber se existe caracteres iguais ou não	
	if(flag == 0){
		option->password[*j] = value;
		(*j)++;
	}
	else{
		(*k)--;	
	}
}


//Função principal
int main(){
	
	int i,j;	
	int size_password;
	int op;
	int value;
	int counter = 0;
	int amount_password;
	OPTION *option;

	//Definição da semente
	srand(time(NULL));
	
	//Informando o usuário que digite os dados necessários para criar a senha
	printf("Informe o tamanho da sua senha(Observação: senhas com 10 dígitos são o suficiente para serem seguras):\n");

	//Armazenando o tamanho da senha
	scanf("%d",&size_password);
	
	//Senhas maiores que 24 caracteres ou menores que 6 caracteres não serão permitidas
	if(size_password>24 || size_password<6){
		printf("O programa não aceita senhas com mais de 24 caracteres ou com menos de 6 caracteres\n");
		return 0;	
	}
	
	//Usuário informa quantas senhas quer gerar
	printf("Informe quantas senhas você quer gerar:\n");
	scanf("%d",&amount_password);
	
	//Criação das opções contendo as chamdas das funções
	option = create_option(size_password);
	
	while(counter++<amount_password){
		//Chamada das funções que irão construir a senha
		i = j = 0;
		while(j != size_password){
			op = option->vector[i++];
			switch(op){
	
				case 1:
					value = generate_random_number();
					verify_character(&i,value,&j,option);
					break;
				case 2:
					value = generate_random_min_letter();
					verify_character(&i,value,&j,option);
					break;
				case 3:
					value = generate_random_max_letter();
					verify_character(&i,value,&j,option);
					break;
				case 4:
					value = generate_random_simbol();
					verify_character(&i,value,&j,option);
					break;
				default:
					break;
			};
		}
	
		//Randomizar a senha
		random_password(option);
	
		//Imprimindo na tela a senha
		for(i=0;i<size_password;i++){
			printf("%c",option->password[i]);
		}
		printf("\n");
	}
	
	//Desalocação da estrutura
	destroy_option(option);
	
	return 0;
}
