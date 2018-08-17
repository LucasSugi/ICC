#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <list>

using namespace std;

typedef struct{
	char name;
	int *priorityPartner;
	int indexPriorityPartner;
	int partner;
} PEOPLE;

typedef struct{
	PEOPLE *people;
	int size;
} FEMALE;

typedef struct{
	PEOPLE *people;
	int size;
} MALE;

//Leitura dos dados
void readData(MALE *male, FEMALE *female){

	int i,j,k;	
	int numberPeople,idPerson;
	int indexPriority;
	char tempName;
	char *lineData;

	//Leitura do numero de pessoas
	scanf("%d",&numberPeople);
	
	//Alocando o numero de homens e mulheres necessarios	
	male->people = (PEOPLE*) malloc(sizeof(PEOPLE) * numberPeople);
	female->people = (PEOPLE*) malloc(sizeof(PEOPLE) * numberPeople);

	//Alocando vetor para parceiros
	for(i=0;i<numberPeople;i++){
		male->people[i].priorityPartner = (int*) malloc(sizeof(int) * numberPeople);	
		female->people[i].priorityPartner = (int*) malloc(sizeof(int) * numberPeople);	
	}

	//Inicializando
	male->size = female->size = 0;

	//Leitura da quebra de linha
	scanf("%c",&tempName);
	
	//Leitura do id das pessoas
	tempName = '\0';
	while(tempName != '\n'){
		scanf("%c",&tempName);
			if(tempName != ' ' && tempName != '\n'){
				if(islower(tempName)){
					male->people[male->size].name = tempName;
					male->people[male->size].partner = -1;
					male->people[male->size++].indexPriorityPartner = 0;
				}
				else{
					female->people[female->size].name = tempName;
					female->people[female->size].partner = -1;
					female->people[female->size++].indexPriorityPartner = 0;
				}
			}
	}
	
	//Variavel que ira conter as informacoes da linha de cada pessoa
	lineData = (char*) malloc(sizeof(char) * 100);	

	//Leitura da lista de prioridades de cada pessoa
	for(i=0;i<2*numberPeople;i++){
		scanf("%s",lineData);	
		//Primeira letra indica se eh homem ou mulher
		if(islower(lineData[0])){
			//Verificando qual eh o homem
			for(j=0;j<numberPeople;j++){
				if(male->people[j].name == lineData[0]){
					idPerson = j;
					break;
				}
			}
			//Leitura da lista
			indexPriority = 0;
			for(j=2;j<strlen(lineData);j++){
				for(k=0;k<numberPeople;k++){
					if(female->people[k].name == lineData[j]){
						male->people[idPerson].priorityPartner[indexPriority++] = k;	
						break;
					}
				}
			}
		}
		else{
			//Verificando qual eh a mulher
			for(j=0;j<numberPeople;j++){
				if(female->people[j].name == lineData[0]){
					idPerson = j;
					break;
				}
			}
			//Leitura da lista
			indexPriority = 0;
			for(j=2;j<strlen(lineData);j++){
				for(k=0;k<numberPeople;k++){
					//Para as mulheres teremos uma lista invertida
					if(male->people[k].name == lineData[j]){
						female->people[idPerson].priorityPartner[k] = indexPriority++;	
						break;
					}
				}
			}

		}
	}

	//Desalocando
	free(lineData);
}

//Impressao do resultado dos casamento
void printResult(MALE *male,FEMALE *female){
	
	int i;

	for(i=0;i<male->size;i++){
		printf("%c %c\n",male->people[i].name,female->people[male->people[i].partner].name);
	}	
}

//Algoritmo para resolver o problema do casamento estavel
void galeShapley(MALE *male, FEMALE *female){
	
	int i;
	int idMale,idPartner;

	//Lista de homens
	list<int> *listMale = new list<int>;

	//Preenchendo lista
	for(i=0;i<male->size;i++){
		listMale->push_back(i);
	}
	

	//Realizando os casamentos
	while(!listMale->empty()){
		//Homem que vai propor
 		idMale = listMale->front();

		//Removendo homem da lista
		listMale->pop_front();

		//Pretendente da sua lista de prioridades
		idPartner = male->people[idMale].priorityPartner[male->people[idMale].indexPriorityPartner++];

		//Verificando se sua pretendente esta livre
		if(female->people[idPartner].partner == -1){
			male->people[idMale].partner = idPartner;	
			female->people[idPartner].partner = idMale;	
		}
		//Se nao esta livre, verifica se ele eh uma melhor opcao ou nao
		else if(female->people[idPartner].priorityPartner[female->people[idPartner].partner] > female->people[idPartner].priorityPartner[idMale]){
			listMale->push_back(female->people[idPartner].partner);
			male->people[idMale].partner = idPartner;
			female->people[idPartner].partner = idMale;
		}
		else{
			listMale->push_back(idMale);
		}
	}

	//Desalocando
	delete listMale;

	//Impressao do resultado
	printResult(male,female);
}


//Desaloca memoria
void freeMemory(MALE *male, FEMALE *female){
	
	int i;

	//Liberando memoria
	for(i=0;i<male->size;i++){
		free(male->people[i].priorityPartner);
		free(female->people[i].priorityPartner);
	}

	free(male->people);
	free(female->people);
	free(male);
	free(female);
}

int main(int argc, char *argv[]){

	int numberTest;

	//Leitura do numero de testes
	scanf("%d",&numberTest);
	
	//Alocando estrutura para armazenar dados de homens e mulheres
	MALE *male = (MALE*) malloc(sizeof(MALE));
	FEMALE *female = (FEMALE*) malloc(sizeof(FEMALE));

	//Leitura dos dados
	readData(male,female);

	//Algoritmo para casamento estavel
	galeShapley(male,female);	
	
	//Desalocando memoria
	freeMemory(male,female);

	return 0;
}
