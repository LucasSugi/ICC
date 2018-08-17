/*Programa que simula um quadro de medalhas de países
 *Autor: Lucas Yudi Sugi
 *Número USP: 9293251
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definando uma estrutura de dados para armazenar as informações dos países
typedef struct pais{

	char *name; 
	int gold;
	int silver;
	int bronze;
	int total;
	int pos;
} PAIS;

//Função responsável pela leitura do nome do arquivo
char *read_file_name(){
	
	char *file_name = NULL;
	size_t tam;	
	
	//Lendo o nome do arquivo com a função getline
	getline(&file_name,&tam,stdin);

	//Eliminando o caracter enter ('\n')
	tam = strlen(file_name);
	file_name[tam-1] = '\0';

	return file_name;
}

//Função responsável pela leitura do conteúdo do arquivo
PAIS *read_content_file(char *file_name, int *tam){
	
	FILE *fp = NULL;
	PAIS *info = NULL;
	int counter = 0, i = 0, j = 0;
	char value;

	//Abrindo o arquivo para leitura
	fp = fopen(file_name,"r");

	/*Contando a quantidade de países que há no arquivo para criar um tamanho certo de estrutura
	a cada '\n' encontrado, sabemos que há um novo país, desse modo a variável tam aumenta*/
	while(!feof(fp)){
		value = fgetc(fp);
		if(value == '\n'){
			(*tam)++;
		}
	}

	//Alocando a quantidade certa de estruturas
	info = (PAIS*) malloc(sizeof(PAIS)*(*tam));

	//Zerando as variáveis char* das estruturas
	for(i=0;i<*tam;i++){
		info[i].name = NULL;
	}
		
	//Colocando o "i" no início
	i = 0;

	//Colocando o cursor para o início do arquivo já que já realizamos uma leitura nele para saber a quantidade de países
	fseek(fp,0,SEEK_SET);
	
	//Leitura do conteúdo do arquivo
	while(!feof(fp)){
		//Armazenando cada caracter em uma variável chamada value para depois testá-la
		value = fgetc(fp);
		
		/*Caso value seja um espaço significa que a string acabou logo o contador recebe 1 para passar essa informação
		em uma condiçã abaixo*/
		if(value == ' '){
			counter = 1;
		}

		//Caso a variável value não seja nem um espaço e um enter, então o caracter da string é armazenado na estrutura
		if(value != ' ' && value != '\n'){
			//Sempre que há um novo caracter, a memória é realoca-da para recebê-lo
			info[i].name = realloc(info[i].name,sizeof(char)*(j+2));
			info[i].name[j] = value;
			j++;		
		}

		//Caso o contador seja 1, significa que a string acabou logo é possível ler as medalhas
		if(counter == 1){
			//Terminador colocado na string
			info[i].name[j] = '\0';

			//Lendo as medalhas e armazenando na estrutura
			fscanf(fp,"%d %d %d\n",&info[i].gold,&info[i].silver,&info[i].bronze);

			//Armazenando o total de medalhas
			info[i].total = info[i].gold + info[i].silver + info[i].bronze;

			/*'i' é incrementado para que a próxima string e medalhas possam ser armazenadas
			em uma nova estrutura, consequentemente o contador e o 'j' são zerados*/
			i++;
			j = 0;
			counter = 0;
		}
	}

	//Fechando o arquivo
	fclose(fp);	

	return info;
}

//Subfunção da opção 1 - Aqui são feitas as comparações para realizar a ordenação

/*As comparações nessa função serão realizadas da seguinte maneira:

-Na comparação entre medalhas, portanto, com inteiros. Será realizada entre a variável swp (troca) e o elemento
da posição seguinte(serão comparados todos os elementos a fim de achar o menor ou maior dependendo da escolha)
caso o swp não respeite a condição do if, então ele será trocado e a posição do elemento será armazenada na variável
índice a fim de realizar a troca de estruturas na função "ord_struct2".

-Na comparação entre palavras (strings) será realizada com outro variável denominada string_aux, mas a comparação
e a troca de elementos assim como a troca de índices será realizada igualmente como as medalhas. Observação: para
comparar as strings teve que se usar a função strcmp.

-Critério de desempate:

	 Ouro - Comparar a quantidade de prata.
	      - Se for igual, comparar bronze.
	      - Se for igual, comparar os nomes.

	Prata - Comparar a quantidade de ouro
	      - Se for igual comparar bronze
              - Se for igual comparar nome

        Bronze- Comparar a quantidade de ouro
	      - Se for igual comparar prata
              - Se for igual comparar nome

	Total - Comparar a quantidade de ouro
	      - Se for igual comparar prata
              - Se for igual comparar nome

	Nome  - Não há critério
*/

void ord_struct2(PAIS *info,int *swp, char **string_aux, int *indice, int j, char cmp, int option){
	
	if(cmp == 'g'){
		//Opção 1 - Ordem crescente
		if(option == 1){
			if(*swp>info[j].gold){
				*swp = info[j].gold;
				*indice = j;
			}
			else if(*swp == info[j].gold){
				if(info[*indice].silver > info[j].silver){
					*swp = info[j].gold;
					*indice = j;
				}
				else if(info[*indice].silver == info[j].silver){
					if(info[*indice].bronze > info[j].bronze){
						*swp = info[j].gold;
						*indice = j;
					}
					else if(info[*indice].bronze == info[j].bronze){
						if(strcmp(info[*indice].name,info[j].name) > 0){
							*swp = info[j].gold;
							*indice = j;
						}
					}		
				}	
			}
		}
		//Caso não seja a opção 1 então será ordenado na ordem decrescente(Opção 2)	
		else {
			if(*swp<info[j].gold){
				*swp = info[j].gold;
				*indice = j;
			}
			else if(*swp == info[j].gold){
				if(info[*indice].silver < info[j].silver){
					*swp = info[j].gold;
					*indice = j;
				}
				else if(info[*indice].silver == info[j].silver){
					if(info[*indice].bronze < info[j].bronze){
						*swp = info[j].gold;
						*indice = j;
					}		
					else if(info[*indice].bronze == info[j].bronze){
						if(strcmp(info[*indice].name,info[j].name) < 0){
							*swp = info[j].gold;
							*indice = j;
						}
					}
				}	
			}

		}
	}
		
	else if(cmp == 's'){
		//Opção 1 - Ordem crescente
		if(option == 1){
			if(*swp>info[j].silver){
				*swp = info[j].silver;
				*indice = j;
			}
			else if(*swp == info[j].silver){
				if(info[*indice].gold > info[j].gold){
					*swp = info[j].silver;
					*indice = j;
				}
				else if(info[*indice].gold == info[j].gold){
					if(info[*indice].bronze > info[j].bronze){
						*swp = info[j].silver;
						*indice = j;
					}
					else if(info[*indice].bronze == info[j].bronze){
						if(strcmp(info[*indice].name,info[j].name) > 0){
							*swp = info[j].silver;
							*indice = j;
						}
					}		
				}	
			}
		}	
		//Caso não seja a opção 1 então será ordenado na ordem decrescente(Opção 2)	
		else {
			if(*swp<info[j].silver){
				*swp = info[j].silver;
				*indice = j;
			}
			else if(*swp == info[j].silver){
				if(info[*indice].gold < info[j].gold){
					*swp = info[j].silver;
					*indice = j;
				}
				else if(info[*indice].gold == info[j].gold){
					if(info[*indice].bronze < info[j].bronze){
						*swp = info[j].silver;
						*indice = j;
					}		
					else if(info[*indice].bronze == info[j].bronze){
						if(strcmp(info[*indice].name,info[j].name) < 0){
							*swp = info[j].gold;
							*indice = j;
						}
					}
				}	
			}

		}
	}

	else if(cmp == 'b'){
		//Opção 1 - Ordem crescente
		if(option == 1){
			if(*swp>info[j].bronze){
				*swp = info[j].bronze;
				*indice = j;
			}
			else if(*swp == info[j].bronze){
				if(info[*indice].gold > info[j].gold){
					*swp = info[j].bronze;
					*indice = j;
				}
				else if(info[*indice].gold == info[j].gold){
					if(info[*indice].silver > info[j].silver){
						*swp = info[j].bronze;
						*indice = j;
					}
					else if(info[*indice].silver == info[j].silver){
						if(strcmp(info[*indice].name,info[j].name) > 0){
							*swp = info[j].bronze;
							*indice = j;
						}
					}		
				}	
			}
		}	
		//Caso não seja a opção 1 então será ordenado na ordem decrescente(Opção 2)	
		else {
			if(*swp<info[j].bronze){
				*swp = info[j].bronze;
				*indice = j;
			}
			else if(*swp == info[j].bronze){
				if(info[*indice].gold < info[j].gold){
					*swp = info[j].bronze;
					*indice = j;
				}
				else if(info[*indice].gold == info[j].gold){
					if(info[*indice].silver < info[j].silver){
						*swp = info[j].bronze;
						*indice = j;
					}		
					else if(info[*indice].silver == info[j].silver){
						if(strcmp(info[*indice].name,info[j].name) < 0){
							*swp = info[j].bronze;
							*indice = j;
						}
					}
				}	
			}

		}
	}
	
	else if(cmp == 't'){
		//Opção 1 - Ordem crescente
		if(option == 1){
			if(*swp>info[j].total){
				*swp = info[j].total;
				*indice = j;
			}
			else if(*swp == info[j].total){
				if(info[*indice].gold > info[j].gold){
					*swp = info[j].total;
					*indice = j;
				}
				else if(info[*indice].gold == info[j].gold){
					if(info[*indice].silver > info[j].silver){
						*swp = info[j].total;
						*indice = j;
					}
					else if(info[*indice].silver == info[j].silver){
						if(strcmp(info[*indice].name,info[j].name) > 0){
							*swp = info[j].total;
							*indice = j;
						}
					}		
				}	
			}
		}	
		//Caso não seja a opção 1 então será ordenado na ordem decrescente(Opção 2)	
		else {
			if(*swp<info[j].total){
				*swp = info[j].total;
				*indice = j;
			}
			else if(*swp == info[j].total){
				if(info[*indice].gold < info[j].gold){
					*swp = info[j].total;
					*indice = j;
				}
				else if(info[*indice].gold == info[j].gold){
					if(info[*indice].silver < info[j].silver){
						*swp = info[j].total;
						*indice = j;
					}		
					else if(info[*indice].silver == info[j].silver){
						if(strcmp(info[*indice].name,info[j].name) < 0){
							*swp = info[j].total;
							*indice = j;
						}
					}
				}	
			}

		}
	}

	else if(cmp == 'n'){
		//Opção 1 - Ordem crescente
		if(option == 1){
			if(strcmp(*string_aux,info[j].name) > 0){
				strcpy(*string_aux,info[j].name);
				*indice = j;
			}
		} 
		//Caso não seja a opção 1 então será ordenado na ordem decrescente(Opção 2)	
		else {
			if(strcmp(*string_aux,info[j].name) < 0){
				strcpy(*string_aux,info[j].name);
				*indice = j;
			}
		}	
	}
}

//Opção 1 e 2 - Ordena os paises de acordo com o critério requerido pelo usuário
void ord_struct(PAIS *info,char cmp, int tam, int option, void (*ord_struct2)(PAIS*,int*,char**,int*,int,char,int)) {
	
	int i,j,swp,indice;
	char *string_aux = NULL;
	PAIS aux;

	if(cmp == 'n'){
		//Alocando uma variavel char para comparar com as strings
		string_aux = (char*) malloc(sizeof(char)*20);
	}


	for(i=0;i<tam-1;i++){
		
		indice = i;

		if(cmp == 'g'){
			//Armazenando um elemento para comparação
			swp = info[i].gold;
		}
			
		else if(cmp == 's'){
			//Armazenando um elemento para comparação
			swp = info[i].silver;	
		}
	
		else if(cmp == 'b'){
			//Armazenando um elemento para comparação
			swp = info[i].bronze;	
		}
		
		else if(cmp == 't'){
			//Armazenando um elemento para comparação
			swp = info[i].total;	
		}
	
		else if(cmp == 'n'){
			//Armazenando um elemento para comparação
			strcpy(string_aux,info[i].name);
		}
		
		for(j=i+1;j<tam;j++){
			//Ponteiro para a função ord_struct2
			ord_struct2(info,&swp,&string_aux,&indice,j,cmp,option); 	
		}
		
		//Troca dos elementos
		memcpy(&aux,&info[i],sizeof(PAIS));
		memcpy(&info[i],&info[indice],sizeof(PAIS));
		memcpy(&info[indice],&aux,sizeof(PAIS));
	}

	if(cmp == 'n'){
		//Desalocando string auxiliar
		free(string_aux);
	}
	
	printf("%20s %20s %20s %20s %20s\n","Pais","Ouros","Pratas","Bronzes","Total");

	for(i=0;i<tam;i++){
		printf("%20s %20d %20d %20d %20d\n",info[i].name,info[i].gold,info[i].silver,info[i].bronze,info[i].total);
	}			
}

//Opção 3 do menu de opções - Leitura do nome do pais a ser buscado
char *read_country_name(){

	size_t tam;
	char *country_name = NULL;

	//Armazenando o nome do pais
	getline(&country_name,&tam,stdin);

	//Eliminando o caracter \n
	tam = strlen(country_name);
	country_name[tam-1] = '\0';

	return country_name;
}

//Opção 3 - Busca pelo país na estrutura de dados
int search_country(PAIS *info,char *country_name,int tam){

	int i, cmp;
	
	for(i=0;i<tam;i++){
		if( strcmp(info[i].name,country_name) == 0 ){
			printf("Nome: %s\nOuros: %d\nPratas: %d\nBronzes: %d\nTotal: %d\n",info[i].name,info[i].gold,info[i].silver,info[i].bronze,info[i].total);
			return 0;
		}
	}
	
	printf("Nao ha um pais chamado %s.\n",country_name);	
	return 0;
}

//Opção 4 - Buscar pelos países que se encontram especificados no intervalo requerido pelo usuário
void search_country_range(PAIS *info,char start,char end,int tam){
	
	int i;
	
	printf("%20s %20s %20s %20s %20s\n","Pais","Ouros","Pratas","Bronzes","Total");

	for(i=0;i<tam;i++){
		if(info[i].name[0]>=start && info[i].name[0]<=end){
			printf("%20s %20d %20d %20d %20d\n",info[i].name,info[i].gold,info[i].silver,info[i].bronze,info[i].total);			}
	}
}

//Opção 5 - Buscar pelas medalhas de ouro que se encontram especificados no intervalo requerido pelo usuário
void search_medals_range(PAIS *info,int start, int end, int tam){
	
	int i;
	
	printf("%20s %20s %20s %20s %20s\n","Pais","Ouros","Pratas","Bronzes","Total");

	for(i=0;i<tam;i++){
		if(info[i].gold>=start && info[i].gold<=end){
			printf("%20s %20d %20d %20d %20d\n",info[i].name,info[i].gold,info[i].silver,info[i].bronze,info[i].total);
		}
	}
}

//Função que liberar a struct da memória heap
void free_struct(PAIS *info,int tam){

	int i;
	
	//Liberando as strings
	for(i=0;i<tam;i++){
		free(info[i].name);
	}

	free(info);
}

//MAIN - função principal
int main(int argc, char *argv[]){
	
	PAIS *info;
	int tam = 0, option = 1, start2, end2;
	char *file_name = NULL, *country_name = NULL, aux, start1, end1;
	
	//Chama a função que retorna o nome do arquivo
 	file_name = read_file_name();

	//Chama a função que retorna o conteúdo do arquivo em uma estrututa de dados
	info = read_content_file(file_name,&tam);

	//Menu de opções na qual cada uma realiza uma função específica no quadro de medalhas	
	while(option != 0){
		//Armazenando a opção
		scanf("%d",&option);
		switch(option){	
			//Opção 0 - Sai do programa
			case 0: option = 0; 
				break;
			
			//Opção 1 - Ordenada as medalhas de acordo com o critério do usuário(Ordem Crescente)
			case 1:	
				/*A primeira variável "aux" recebe o caracter '\n' a segunda recebe uma letra que informa
				como o usuário quer ordenar as medalhas*/
				scanf("%c%c",&aux,&aux);
				//Função que irá ordenar
				ord_struct(info,aux,tam,option,ord_struct2);
				break;

			//Opção 2 - Ordenada as medalhas de acordo com o critério do usuário(Ordem Decrescente)
			case 2:	
				/*A primeira variável "'aux" recebe o caracter '\n' a segunda recebe uma letra que informa
				como o usuário quer ordenar as medalhas*/
				scanf("%c%c",&aux,&aux);
				ord_struct(info,aux,tam,option,ord_struct2);
				break;

			//Opção 3 - Busca no quadrado de medalhas por um país requerido pelo usuário
			case 3:	
				//Variável aux necessária para pegar o caracter '\n'	
				scanf("%c",&aux);
				//Função que le o nome do país a ser procurado
				country_name = read_country_name();
				//Função que busca pelo país no quadro de medalhas
				search_country(info,country_name,tam);
				//Liberando o nome do país que foi alocado dinamicamente
				free(country_name); 
				break;

			//Opção 4 - Busca em um intervalo informado pelo usuário os países no quadro de medalhas
			//Intervalo entre letras
			case 4:
				/*Nos três scanfs abaixo a variável aux foi necessária para pegar o caracter '\n'
				já as variáveis "start1" e "end1" pegam ,respectivamente, o início do intervalo 
				e o fim*/
				scanf("%c",&aux);	
				scanf("%c%c",&start1,&aux);
				scanf("%c%c",&end1,&aux);
				//Função que busca os países no intervalo requerido
				search_country_range(info,start1,end1,tam);
				break;
			
			//Opção 5 - Busca em um intervalo informado pelo usuário os países no quadro de medalhas
			//Intervalo entre número de medalhas 
			case 5:	
				//Variável "start2" e "end2" pegam ,respectivamente, o início do intervalo e o fim
				scanf("%d%d",&start2,&end2);
				//Função que busca os países no intervalo requerido
				search_medals_range(info,start2,end2,tam);
				break;
		}
	}

	//Chama a função que libera a estrutura de dados
	free_struct(info,tam);		

	//Liberar o nome do arquivo
	free(file_name);

	return 0;
}
