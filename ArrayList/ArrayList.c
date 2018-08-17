/*
 * Nome : Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include "ArrayList.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM 10

//Estrutuda de dados contém informações para um vetor de itens 
typedef struct NO{
	
	ITEM **item;
	int fim_no;
	int insert;
	int tamanho;
	struct NO *proximo;
	struct NO *anterior;
} NO;

//Estrutura de dados que irá contenter os nós
struct ArrayList{

	NO *inicio;
	NO *fim;
	int tamanho_ArrayList;
};


//Apagar o no junto com o seu vetor de itens
void apagar_no(NO **no){
	
	if(no != NULL && *no != NULL){
		int i;
		//Os itens são desalocados até onde possuir itens
		for(i=0;i<(*no)->insert;i++){
			apagar_item( &((*no)->item[i]) );
		}
		free((*no)->item);
		free(*no);
		*no = NULL;
	}
}	

/*Após ser passado uma posição, é retornado o índice do nó que conteria aquela posição. Além de 
posicionar o ponteiro para o nó correto. Essa função será utilizada por muitas outras*/
int index_pos(ArrayList *list, NO**paux,int pos){

	int counter = 0, no = 10, n = 2;
	
	//Caso seja passado uma posição inválida é retornado -1
	if(list->tamanho_ArrayList <= pos) return -1;
	
	//Cálculo do índice	
	while(pos >= no + counter){
		counter += no;
		no = 10 * pow(2,n-1);
		n++;
	}	

	n--;
	no = 1;
	
	//Posicionando o ponteiro para o nó correto	
	while( (*paux) != NULL && no != n){
		(*paux) = (*paux)->proximo;
		no++;
	}
	
	//Se a posição encontrada não contiver um item é retornado -1 caso contrário é retornado o índice	
	if( (pos-counter) <=  (*paux)->insert-1){
		return pos-counter;
	}
	else {
		return -1;
	}
}

//Criação de uma novo ArrayList - O ArrayList já é inicializado com um nó
ArrayList *new_ArrayList(){

	ArrayList *list = (ArrayList*) malloc(sizeof(ArrayList));

	if(list != NULL){
	
		list->inicio = NULL;
		list->fim = NULL;
		list->tamanho_ArrayList = 0;
	}
	return list;
}

//Inserção ordenada - O item é shifitado até ele ficar ordenado dentro do vetor 
int insertion_ordered(NO *pno, ITEM *item){

	int i = pno->insert;
	
	//O item é comparado dentro das posições do nó e é shifitado
	while( i != 0 && item->chave < pno->item[i-1]->chave){
		pno->item[i] = pno->item[i-1];
		i--;
	}
	//Após ser comparado dentro do nó é analisado se há um novo nó pelo qual deva ser comparado
	if(pno->anterior != NULL && i == 0){
		/*Caso exista é comparado com a última posição do nó e caso a chave seja menor então é feito a troca
		Após a troca a função é chamada recursivamente para comparar dentro do outro nó*/
		if(item->chave < pno->anterior->item[pno->anterior->fim_no]->chave){	
			pno->item[i] = pno->anterior->item[pno->anterior->fim_no];
			pno->insert++;
			pno->anterior->insert--;
			insertion_ordered(pno->anterior,item);
			return 1;
		}		
	}
	//Caso não exista outro nó ou a chave seja maior que o elemento do outro nó então ela é armazenada
	pno->item[i] = item;
	pno->insert++;
	return 1;

}


//Adição de um novo item - Sempre após inserir o item é chamado uma função responsável por ordenar esse item
int add_ArrayList(ArrayList *list, ITEM *item){


	NO *paux = list->fim;
	
	if(list->tamanho_ArrayList == 0 ){
		NO *no = (NO*) malloc(sizeof(NO));
		if(no != NULL){
			no->tamanho = 10;
			no->fim_no = no->tamanho-1;	
			no->insert = 0;
			no->item = (ITEM**) malloc(sizeof(ITEM*) * no->tamanho);
			no->proximo = NULL;
			no->anterior = NULL;
			list->inicio = no;	
			list->fim = no;
			list->tamanho_ArrayList++;

			insertion_ordered(no,item);
		}	
	}
	
	//Caso exista posições dentro do nó disponíveis então é armazenado nele um item
	else if(paux->insert <= paux->fim_no){
		
		insertion_ordered(paux,item);
		list->tamanho_ArrayList++;
		
	}
	//Caso não exista então é criado outro nó para armazenamento
	else {	
		NO *pnovo = (NO*) malloc(sizeof(NO));			
		if(pnovo != NULL){
			//O novo nó é criado com o dobro do tamanho anterior e os ponteiros do Array são arrumados
			pnovo->tamanho = paux->tamanho*2;
			pnovo->fim_no = pnovo->tamanho-1;
			pnovo->insert = 0;
			pnovo->item = (ITEM**) malloc(sizeof(ITEM*) * pnovo->tamanho);
			paux->proximo = pnovo;
			list->fim = pnovo;
			pnovo->anterior = paux;
			pnovo->proximo = NULL;
			list->tamanho_ArrayList++;

			insertion_ordered(pnovo,item);
		}
	}	
}

//Busca binária - Dada uma chave é realizada uma busca binária dela dentro de um nó específico
int search_binary(NO *vector, int chave, int start, int end){

	int middle = (start + end) / 2;

	if(start > end) return -1;
	
	if(chave == vector->item[middle]->chave){
		return middle;
	}
	else if(chave < vector->item[middle]->chave){
		search_binary(vector,chave,start,middle-1);
	}
	else if(chave > vector->item[middle]->chave){
		search_binary(vector,chave,middle+1,end);
	}
}

//Contém a chave dentro do Array
int contains_ArrayList(ArrayList *list, int chave){

	NO *paux = list->inicio;
	int retorno = -1;	
	
	//Laço utilizado para ir até o último nó	
	while(paux != NULL){
		if(paux->insert == paux->tamanho){
			//A chave é comparada dentro do intervalo do nó para analisar se ela se encontra ali
			if(chave >= paux->item[0]->chave && chave <= paux->item[paux->fim_no]->chave){
				//Caso seja encontrado é realizado a busca binária
				retorno = search_binary(paux,chave,0,paux->fim_no);				
				return retorno;	
			}
		}
		else{
			//A chave é comparada dentro do intervalo do nó para analisar se ela se encontra ali
			if(chave >=  paux->item[0]->chave && chave <= paux->item[paux->insert-1]->chave){
				//Caso seja encontrado é realizado a busca binária
				retorno = search_binary(paux,chave,0,paux->insert-1);				
				return retorno;
			}
		}
		paux = paux->proximo;
	}
	
	return retorno;
}

//Após ser passado uma posição é procurado nos nó para ver se há um item
ITEM *get_ArrayList(ArrayList *list, int pos){
	
	NO *paux = list->inicio;
	
	pos = index_pos(list,&paux,pos);
	
	//Caso o item não exista é retornado NULL
	if( pos != -1){
		return paux->item[pos];	
	}
	else {
		return NULL;
	}
}

//Dada uma chave é procurado no Array por item que contenha a mesma chave
int index_ArrayList(ArrayList *list, int chave){
		
	NO *paux = list->inicio;
	int retorno = 0, no = 0;	
	
	//Laço usadao para ir até o último nó	
	while(paux != NULL){
		//A chave é procurado dentro dos intervalos dos nós e caso seja encontrada é realizado uma busca binária
		if(paux->insert == paux->tamanho){
			if(chave >= paux->item[0]->chave && chave <= paux->item[paux->fim_no]->chave){
				retorno = search_binary(paux,chave,0,paux->fim_no);				
				break;
			}
		}
		else{
			if(chave >=  paux->item[0]->chave && chave <= paux->item[paux->insert-1]->chave){
				retorno = search_binary(paux,chave,0,paux->insert-1);				
				break;
			}
		}
		paux = paux->proximo;
		no++;
	}
	
	//Caso a chave seja encontrada é retornado a posição dela, caso não exista é retonado -1	
	if(retorno != -1 && retorno != 0){
		return retorno + (10 * (pow(2,no) - 1)) ;
	}
	else {
		return -1;
	}
}

//Função responsável para shifitar os elementos dentro do nó
void shift(ArrayList *list,NO *paux, int pos){
	
	//Shifitando dentro do nó
	while(pos <= paux->insert-2){
		paux->item[pos] = paux->item[pos+1];
		pos++;
	}
	//Caso exista um outro nó é shifitado o elemento para o outro nó e ocorre a recursão	
	if(paux->proximo != NULL){
		paux->item[pos] = paux->proximo->item[0];
		shift(list,paux->proximo,0);
	}
	//Caso não exista é parado a recursão e é diminuído a quantidade de itens e de nós
	if(paux->proximo == NULL){
		paux->insert--;
		if(paux->insert == 0){
			list->fim = paux->anterior;	
			paux->anterior->proximo = NULL;
			apagar_no(&paux);
		}
	}
}

//Remoção do item
int remove_ArrayList(ArrayList *list, int pos){

	NO *paux = list->inicio;
	
	//Cálculo da posição
	pos = index_pos(list,&paux,pos);
	
	//Caso a posição seja válida é deletado o nó e é feito um shift no Array	
	if( pos != -1){
		free(paux->item[pos]);
		list->tamanho_ArrayList--;
		shift(list,paux,pos);
		return 1;
	}
	else {
		return 0;
	}
}

//A chave pe menor que o elemento da posição a esquerda logo ocorre um shift anterior
void shift_anterior(NO *paux, ITEM *item, int pos){

	int controle = 0;

	//Shifitando o elemento até a primeira posição do nó
	while( pos >= 0 &&  item->chave < paux->item[pos]->chave ){
		paux->item[pos+1] = paux->item[pos];
		pos--;
	}
	//Caso exista um outro nó e o shift seja necessário é feito uma recursão para o outro nó
	if(pos == -1 && paux->anterior != NULL){
		if(item->chave < paux->anterior->item[paux->anterior->fim_no]->chave){
			paux->item[0] =  paux->anterior->item[paux->anterior->fim_no];
			shift_anterior(paux->anterior,item,paux->anterior->fim_no-1);
			controle = 1;
		}
	}
	//Caso ocorra a recursão não é necessário setar o item, caso não ocorra o item é setado
	if(controle != 1){
		paux->item[pos+1] = item;
	}
}

//A chave é maior que o elemento da posição a direita. Logo o shift ocorre para a direita
void shift_proximo(NO *paux, ITEM *item, int pos){

	int controle = 0;
	
	//Shifitando o elemento até a última posição do nó
	while(pos <= paux->insert-1 && item->chave > paux->item[pos]->chave){
		paux->item[pos-1] = paux->item[pos];
		pos++;
	}
	//Caso exista um outro nó e o shift seja necessário é feito uma recursão para o outro nó
	if(pos == paux->insert && paux->proximo != NULL){
		if(item->chave > paux->proximo->item[0]->chave){
			paux->item[pos-1] = paux->proximo->item[0];
			shift_proximo(paux->proximo,item,1);
			controle = 1;
		}	
	}
	//Caso ocorra a recursão não é necessário setar o item, caso não ocorra o item é setado
	if(controle != 1){
		paux->item[pos-1] = item;
	}
}

//Mudando o item no Array
int set_ArrayList(ArrayList *list, int pos, ITEM *item){

	NO *paux = list->inicio;
	
	//Cálculo da posição	
	pos = index_pos(list,&paux,pos); 
	
	//Caso a posição seja válida é alterado o item
	if( pos != -1){
		free(paux->item[pos]);
		paux->item[pos] = item;		
		
		//Vericações necessárias para analisar se terá que haver um shift no Array
		if( pos == 0 && paux->anterior != NULL ){
			if(item->chave < paux->anterior->item[paux->anterior->fim_no]->chave){
				shift_anterior(paux,item,-1);
			}
		}	
		if( pos == paux->fim_no && paux->proximo != NULL ){
			if(item->chave > paux->proximo->item[0]->chave){
				shift_proximo(paux,item,paux->insert);	
			}
		}
		if( pos != 0){
			if(item->chave < paux->item[pos-1]->chave){
				shift_anterior(paux,item,pos-1);	
			}
		}	
		if( pos != paux->fim_no){
			if(item->chave > paux->item[pos+1]->chave){
				shift_proximo(paux,item,pos+1);	
			}
		}
			return 1;
	}
	else {
		return 0;
	}
}

//Criação de um subArray em um intervalo
ArrayList *sub_ArrayList(ArrayList *list,int pos1, int pos2){

	ArrayList *newList = new_ArrayList();
	NO *paux1, *paux2;	
	int i;

	paux1 = paux2 = list->inicio;
	
	//Cálculo das posições
	pos1 =  index_pos(list,&paux1,pos1);
	pos2 =  index_pos(list,&paux2,pos2);
	
	//Os itens não são copiados para o novo Array, são apenas apontados	
	while(paux1 != paux2){
		while(pos1 <= paux1->insert-1){
			add_ArrayList(newList,paux1->item[pos1]);	
			pos1++;
		}
		paux1 = paux1->proximo;
		pos1 = 0;
	}
	//Continuando apontando os itens até o intervalo aberto
	while(pos1 < pos2){
		add_ArrayList(newList,paux1->item[pos1]);
		pos1++;	
	}
	
	return newList;
}

//Lista vazia - A lista estará vazia caso não exista nenhum item nela
int isEmpty_ArrayList(ArrayList *list){
	return list->tamanho_ArrayList == 0;
}

//Tamanho do Array
int size_ArrayList(ArrayList *list){
	
	printf("%d\n",list->tamanho_ArrayList);
	return 1;
}


//Desalocando o subArray na qual os itens apontados por ela não são desalocados mas os nós e subArray sim
void destruct_newList(ArrayList **list){

	if(list != NULL && *list != NULL){
		NO *paux = (*list)->inicio;
		while( paux != NULL){
			NO *prem = paux;
			paux = paux->proximo;
			free(prem->item);
			free(prem);
		}
		free(*list);
		*list = NULL;
	}
}


//Desalocação total de toda Array
int destruct_ArrayList(ArrayList **list){

	
	if(list != NULL && *list != NULL){
		NO *paux = (*list)->inicio;
		while(paux != NULL){
			NO *prem = paux;
			paux = paux->proximo;
			apagar_no(&prem);
		}
		free(*list);
		*list = NULL;
		return 1;
	}
	return 0;
}

//Impressão de todos os itens do Array
void print_ArrayList(ArrayList *list){

	if( !isEmpty_ArrayList(list) ){
		NO *paux = list->inicio;
		int i;
		while(paux != NULL){
			for(i=0;i<paux->insert;i++){
				imprimir_item(paux->item[i]);		
			}
			printf("\n\n");
			paux = paux->proximo;		
		}
	}
}
