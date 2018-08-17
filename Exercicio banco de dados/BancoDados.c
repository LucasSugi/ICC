#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FLAG -1
#define TAM_REGISTRO 118
#define TRUE 1
#define FALSE 0

/*
Nome: Lucas Yudi Sugi
Número USP: 9293251
*/

/*
N USP: 4 bytes
Nome: 30  bytes
Sobrenome: 30 bytes
Departamento: 50 bytes
Ano: 4 bytes
Total: 118 bytes
*/

/*
Leitura de palavras/frases/valores do stdin
Parâmetros: char* => irá armazenar as strings do stdin
*/
void leituraStdin(char *leitura){
	
	int pos = 0;	
	char letra;
	
	/*Leitura das palavras via stdin*/
	do{

		letra = getc(stdin);
		leitura[pos++] = letra;

	} while(letra != '\n');
	
	/*Armazenando o final da string e eliminando o '\n'*/
	leitura[pos-1] = '\0';
}

/*
Função para escrever dados dos alunos no arquivo
Parâmetros: char* => nome do arquivo a ser criado
*/
void escreverArquivo(char *nomeArquivo){
	
	int armazenarInt = 0, executar = TRUE;
	char *armazenarChar = NULL;
	FILE *fp = NULL;

	/*Criação do arquivo bińario caso já exista ou abertura do arquivo para adicao de registros*/
	fp = fopen(nomeArquivo,"ab");
	
	/*Verificando se o arquivo foi aberto*/
	if(fp == NULL){
		printf("Não foi possível abrir o aquivo");
		return;
	}
	
	/*Alocando a variável char para armazenarmento(Alocação terá referência para a maior string)*/
	armazenarChar = (char*) calloc(50,sizeof(char));

	/*Escrita no arquivo*/
	while(executar == TRUE){

		/*Informanado o usuário*/
		printf("Digite o número USP ou -1 para finalizar:\n");

		/*Leitura do número USP ou do flag indicando se acaba a entrada de dados*/
		leituraStdin(armazenarChar);

		/*Conversão da strig para inteiro*/
		armazenarInt = atoi(armazenarChar);

		/*Verificando se é o flag para finalizar a entrada de dados*/
		if(armazenarInt == FLAG){
			executar = FALSE;
		}
		else{
			/*Escrita do número USP no arquivo*/
			fwrite(&armazenarInt,sizeof(int),1,fp);
				
			/*Informando o usuário*/
			printf("Digite o seu nome:\n");	
	
			/*Leitura do nome*/
			leituraStdin(armazenarChar);

			/*Escrita do nome no arquivo*/
			fwrite(armazenarChar,30,1,fp);
		
			/*Informando o usuário*/
			printf("Digite seu sobrenome:\n");
	
			/*Leitura do sobrenome*/
			leituraStdin(armazenarChar);

			/*Escrita do nome no arquivo*/
			fwrite(armazenarChar,30,1,fp);
			
			/*Informando o usuário*/
			printf("Digite o seu departamento:\n");
		
			/*Leitura do departamento*/
			leituraStdin(armazenarChar);

			/*Escrita do nome no arquivo*/
			fwrite(armazenarChar,50,1,fp);
		
			/*Informando o usuário*/
			printf("Digite o seu ano:\n");

			/*Leitura do ano*/
			leituraStdin(armazenarChar);
			
			/*Conversão da strig para inteiro*/
			armazenarInt = atoi(armazenarChar);

			/*Escrita no arquivo*/
			fwrite(&armazenarInt,sizeof(int),1,fp);

		}	
	}
	
	/*Desalocando a variável que armazena char*/
	free(armazenarChar);
	
	/*Fechando o arquivo*/
	fclose(fp);	

}

/*
Permite a recuperação dos registros 
Parâmetro: char*(nome do arquivo)
Retorno: nenhum
*/
void recuperarDados(char *nomeArquivo){

	FILE *fp = NULL;
	int leInt = 0;
	char *leChar = NULL;

	/*Abertura do arquivo*/
	fp = fopen(nomeArquivo,"r");
	
	/*Verificando se o arquivo foi aberto*/
	if(fp == NULL){
		printf("Não foi possível abrir o aquivo");
		return;
	}
	
	/*Alocando variável char para armazenar os dados lidos do arquivo*/
	leChar = (char*) malloc(sizeof(char) * 50 );
	
	/*Leitura até o fim do arquivo*/
	while(!feof(fp)){

		printf("-----------------------------------------\n");

		/*Leitura do número USP*/
		fread(&leInt,sizeof(int),1,fp);
		
		/*Caso seja o fim do arquivo e ele não pare no laço while, entao "matamos" ele aqui*/
		if(feof(fp)){
			free(leChar);
			fclose(fp);
			return;
		}

		/*Impressão na tela do número USP*/
		printf("Número USP: %d\n",leInt);
		
		/*Leitura do nome*/
		fread(leChar,30,1,fp);

		/*Impressão na tela do nome*/
		printf("Nome: %s\n",leChar);

		/*Leitura do sobrenome*/
		fread(leChar,30,1,fp);

		/*Impressão na tela do sobrenome*/
		printf("Sobrenome: %s\n",leChar);

		/*Leitura do departamento*/
		fread(leChar,50,1,fp);

		/*Impressão do departamento*/
		printf("Departamento: %s\n",leChar);

		/*Leitura do ano de ingresso*/
		fread(&leInt,sizeof(int),1,fp);

		/*Impressao do ano de ingresso na tela*/
		printf("Ano de ingresso: %d\n",leInt);
		
	}
	printf("-----------------------------------------\n");
	
	/*Desalocando variável leChar*/
	free(leChar);

	/*Fechando o arquivo*/
	fclose(fp);	

}

/*
Recuperar um registro
Parâmetro: char*(nome correspondente do arquivo)
Retorno: nehum
*/
void recuperarRRN(char *nomeArquivo, int RRN){
	
	int pos,leInt,tam;
	char *leChar = NULL;
	FILE *fp = NULL;

	/*Abertura do arquivo*/
	fp = fopen(nomeArquivo,"r");
	
	/*Verificando se o arquivo foi aberto*/
	if(fp == NULL){
		printf("Não foi possível abrir o aquivo");
		return;
	}
	
	/*Movendo cursor para o final do arquivo*/
	fseek(fp,0,SEEK_END);

	/*Armazenadno o tamanho do arquivo*/
	tam = ftell(fp);

	/*Calculando número máximo de registros*/
	tam /= TAM_REGISTRO;	
	
	/*Verificando se o RRN passado existe*/
	if(RRN >= tam){
		fclose(fp);
		return;
	}
	
	/*Cálculo do registro no arquivo*/
	pos = RRN * TAM_REGISTRO;	
	
	/*Alocando variável char para armazenar os dados lidos do arquivo*/
	leChar = (char*) malloc(sizeof(char) * 50 );
	
	/*Movendo cursor do arquivo para a posição desejada*/
	fseek(fp,pos,SEEK_SET);

	/*Leitura do registro*/
	printf("-----------------------------------------\n");

	/*Leitura do número USP*/
	fread(&leInt,sizeof(int),1,fp);

	/*Impressão na tela do número USP*/
	printf("Número USP: %d\n",leInt);
		
	/*Leitura do nome*/
	fread(leChar,30,1,fp);

	/*Impressão na tela do nome*/
	printf("Nome: %s\n",leChar);

	/*Leitura do sobrenome*/
	fread(leChar,30,1,fp);

	/*Impressão na tela do sobrenome*/
	printf("Sobrenome: %s\n",leChar);

	/*Leitura do departamento*/
	fread(leChar,50,1,fp);

	/*Impressão do departamento*/
	printf("Departamento: %s\n",leChar);

	/*Leitura do ano de ingresso*/
	fread(&leInt,sizeof(int),1,fp);

	/*Impressao do ano de ingresso na tela*/
	printf("Ano de ingresso: %d\n",leInt);
		
	printf("-----------------------------------------\n");
	
	/*Desalocando memória*/
	free(leChar);
		
	/*Fechando o arquivo*/
	fclose(fp);
}

/*Função principal*/
int main(){
	
	int op,executar = TRUE;
	char *nomeArquivo = NULL;	
	char *opChar = NULL;
	
	/*Alocando a variável que irá armazenar o nome do arquivo*/
	nomeArquivo = (char*) malloc(sizeof(char) * 20);
	
	/*Alocando a variável que irá armazenar as nome do arquivo*/
	opChar = (char*) malloc(sizeof(char) * 20);
	
	/*Informando o usuário para informar o nome do arquivo*/
	printf("Informe o nome do arquivo a ser manipulado\n");

	/*Armazenando o nome do arquivo*/
	leituraStdin(nomeArquivo);

	/*Controle da execução do programa*/
	while(executar == TRUE){
		/*Informando as opções do programa para o usuário*/
		printf("Opções do programa:\n0 - Escrever no arquivo\n1 - Recuperar dados do arquivo\n2 - Recuperar RRN\n3 - Sair do programa\n");

		/*Armazenando a opção digitada*/
		leituraStdin(opChar);

		/*Conversão para int*/
		op = atoi(opChar);

		/*Menu das opções*/
		switch(op){
			case 0:
				escreverArquivo(nomeArquivo);
				break;
			case 1:
				recuperarDados(nomeArquivo);
				break;
			case 2:
				/*Informando o usuário para digitar o RRN*/
				printf("Digite o RRN que deseja buscar\n");
				/*Lendo o RRN*/
				leituraStdin(opChar);
				/*Conversão da string para int*/
				op = atoi(opChar);
				recuperarRRN(nomeArquivo,op);
				break;
			case 3:
				executar = FALSE;				
				break;
	
		}

		/*Quebra de linha*/
		printf("\n");
	}	
	
	/*Desalocando memória*/
	free(nomeArquivo);
	free(opChar);	

	return 0;
}
