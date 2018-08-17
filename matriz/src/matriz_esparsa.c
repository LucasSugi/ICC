/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include "matriz_esparsa.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Estruturá que armazenará o valor 
typedef struct CELULA{

	int linha;
	int coluna;
	int valor;
	int quantidade;
	struct CELULA *direita;
	struct CELULA *abaixo;

} CELULA;

//Estrutura que conterá a matriz esparsa
struct matriz_esparsa{

	CELULA *begin;
	CELULA *posLin;	
	CELULA *posCol;
	int nr_linhas;
	int nr_colunas;
};

//Criação da matriz esparsa com nós cabeças e de maneira circular
MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas){

	int i;
	MATRIZ_ESPARSA *mat = (MATRIZ_ESPARSA*) malloc(sizeof(MATRIZ_ESPARSA));	
	CELULA *paux;
	
	//Caso a matriz seja diferente de nula então será tentato alocar a primeira célula	
	if(mat != NULL){
		//Caso seja possível alocar a célula então será alocado os nós cabeças
		mat->begin = (CELULA*) malloc(sizeof(CELULA));
		if(mat->begin != NULL){
			
			//Inicializando os valores em begin
			mat->begin->valor = -1;
			mat->begin->quantidade = -1;
			mat->begin->linha -1;
			mat->begin->coluna -1;
			
			//Alocando os nós cabeças nas colunas
			i = 0;
			paux = mat->begin;
			while(i < nr_colunas){
				paux->direita = (CELULA*) malloc(sizeof(CELULA));
				paux = paux->direita;
				paux->valor = 0;
				paux->linha = 0;
				paux->coluna = i;
				paux->quantidade = 0;
				paux->abaixo = paux;
				i++;
			}
			paux->direita = mat->begin;	
			
			//Alocando os nós cabeças nas linhas
			i = 0;
			paux = mat->begin;
			while(i < nr_linhas){
				paux->abaixo = (CELULA*) malloc(sizeof(CELULA));
				paux = paux->abaixo;
				paux->valor = 0;
				paux->linha = i;
				paux->coluna = 0;
				paux->quantidade = 0;
				paux->direita = paux;
				i++;
			}
			paux->abaixo = mat->begin;

			//Armazenando a linha e a coluna
			mat->nr_linhas = nr_linhas;
			mat->nr_colunas = nr_colunas;
			
			//A CELULA *posLin e posCol irão apontar para linhas e colunas de modo a facilitar o aceso
			mat->posLin = mat->begin->abaixo;
			mat->posCol = mat->begin->direita;
		}	

	}
	return mat;
}

//Desalocando todos os elementos da matriz
void apagar_matriz(MATRIZ_ESPARSA **mat){
	
	CELULA *paux;
	CELULA *prem;
	CELULA *inicial;
	int i;

	if(mat != NULL && *mat != NULL){
		inicial = (*mat)->begin;
		paux = inicial->direita;		
	
		for(i=0;i<=(*mat)->nr_linhas;i++){
			while(inicial != paux){
				prem = paux;
				paux = paux->direita;
				free(prem);
			}
			if(inicial != (*mat)->begin){
				prem = inicial;
				inicial = inicial->abaixo;
				paux = inicial->direita;
				free(prem);
					
			}
			else {
				inicial = inicial->abaixo;
				paux = inicial->direita;
			}
		}
		free((*mat)->begin);
		free((*mat));
	}
}	

//Setando um elemento na matriz
int set_matriz(MATRIZ_ESPARSA *mat, int linha, int coluna, int valor){
	
	CELULA *pauxLin = mat->posLin;
	CELULA *pauxCol = mat->posCol;
	CELULA *pmove;
	CELULA *pnovo;

	if(mat->posLin->linha > linha){
		pauxLin = mat->begin->abaixo;
	}
	if(mat->posCol->coluna > coluna){
		pauxCol = mat->begin->direita;
	}	

	
	//Alocando célula
	pnovo = (CELULA*) malloc(sizeof(CELULA));
	
	//Inicializando os valores nela
	pnovo->valor = valor;
	pnovo->linha = linha;
	pnovo->coluna = coluna;
	pnovo->quantidade = -2;
	
	//Procurando pela linha na qual se deve inserir o elemento	
	while(pauxLin->linha < linha){
		pauxLin = pauxLin->abaixo;
	}
	//Aumentando a quantidade de elementos na linha
	pauxLin->quantidade++;
	
	//Percorrendo naquela linha a procura da coluna na qual se deve inserir	a célula
	pmove = pauxLin->direita;
	while(pmove->direita->coluna < coluna && pmove->direita != pauxLin){
		pmove = pmove->direita;
	}
	pnovo->direita = pmove->direita;
	pmove->direita = pnovo;		
		
	//Procurando pela coluna na qual se deve inserir o elemento
	while(pauxCol->coluna < coluna){
		pauxCol = pauxCol->direita;
	}
	//Aumentando a quantidade de elementos na coluna
	pauxCol->quantidade++;
	
	//Percorrendo naquela coluna a procura da linha na qual se deve inserir a célula
	pmove = pauxCol->abaixo;		
	while(pmove->abaixo->linha < linha   && pmove->abaixo != pauxCol){
		pmove = pmove->abaixo;
	}
	pnovo->abaixo = pmove->abaixo;
	pmove->abaixo = pnovo;

	//Armazenando na matriz esparsar os ponteiros das últimas linhas e colunas apontadas	
	//Isso será útil já que a entrada dos elementos do programa é feita de maneira ordenada
	mat->posLin = pauxLin;
	mat->posCol = pauxCol;

	return 1;
}

//Dado uma linha e uma coluna é procurado por um elemento com essas coordenadas
int get_matriz(MATRIZ_ESPARSA *mat, int linha, int coluna){
	
	CELULA *pauxLin = mat->posLin;
	CELULA *pmove;
	
	//Procurando pela linha correta
	while(pauxLin->linha < linha){
		pauxLin = pauxLin->abaixo;
	}	
		
	//Procurando na coluna pelo elemento
	pmove = pauxLin->direita;
	while( pmove->direita->coluna <= coluna  && pmove->direita != pauxLin){
		pmove = pmove->direita;			
	}
	
	if(pmove->coluna == coluna){
		mat->posLin = pauxLin;
		return pmove->valor;
	}	
	else if(pmove->direita == pauxLin && pmove->coluna <= coluna){
		mat->posLin = pauxLin;
		return INT_MAX;	
	}	
	return 0;
}

int get_linha(MATRIZ_ESPARSA *mat, int k, int j){

	
	//Acessando a linha
	while(mat->posLin->linha < k){
		mat->posLin = mat->posLin->abaixo;
		mat->posCol = mat->posLin;
	}
	
	if(mat->posCol->direita == mat->posLin){
		return -1;	
	}	
	
	mat->posCol = mat->posCol->direita;
	return mat->posCol->coluna;
}

int get_coluna(MATRIZ_ESPARSA *mat, int j, int i){
	
	//Acessando a coluna
	while(mat->posCol->coluna < i){
		mat->posCol = mat->posCol->direita;	
		mat->posLin = mat->posCol;
	}
	
	if(mat->posLin->linha > j){
		mat->posLin = mat->posCol;
	}	

	//Procurando pela linha	
	while(mat->posLin->abaixo->linha <= j && mat->posLin->abaixo != mat->posCol){
		mat->posLin = mat->posLin->abaixo;	
	}

	if(mat->posLin->linha == j){
		return mat->posLin->valor;
	}
	return 0;
}

//Multiplicação de uma maneira por outra
MATRIZ_ESPARSA *multiplicar_matriz(MATRIZ_ESPARSA *mat1, MATRIZ_ESPARSA *mat2){
	
	int i,j,k,valor = 0;
	int aux;
	
	//Criação da matriz resultante
	MATRIZ_ESPARSA	*matRes = criar_matriz(mat1->nr_linhas,mat2->nr_colunas);

	//Pegando a primeira linha e a primeira coluna
	mat1->posLin = mat1->begin->abaixo;
	mat1->posCol = mat1->posLin;
	
	//Pegando a primeira linha e a primeira coluna
	mat2->posCol = mat2->begin->direita;
	mat2->posLin = mat2->posCol;

	//Multiplicando
	for(k=0;k<mat1->nr_linhas;k++){
		for(i=0;i<mat2->nr_colunas;i++){
			for(j=0;j<mat1->nr_colunas;j++){
				j = get_linha(mat1,k,j);
				if(j != -1){
					valor += mat1->posCol->valor * get_coluna(mat2,j,i);
				}
				else{
					j = mat1->nr_colunas;
				}
			}
				
			//Atualizando	
			mat1->posCol = mat1->posLin;
	
			//Setando o valor
			if(valor != 0){
				set_matriz(matRes,k,i,valor);
				valor = 0;
			}
		}		
		mat2->posCol = mat2->begin->direita;
		mat2->posLin = mat2->posCol;
	}
	
	return matRes;
}


MATRIZ_ESPARSA *somar_matriz(MATRIZ_ESPARSA *mat1, MATRIZ_ESPARSA *mat2){
	
	int i,j,valor = 0, aux;

	//Criação da matriz resultante
	MATRIZ_ESPARSA	*matRes = criar_matriz(mat1->nr_linhas,mat1->nr_colunas);

	mat1->posLin = mat1->begin->abaixo;
	mat2->posLin = mat2->begin->abaixo;
	
	for(i=0;i<mat1->nr_linhas;i++){
		for(j=0;j<mat1->nr_colunas;j++){
				
			aux = get_matriz(mat1,i,j);	
			if(aux != INT_MAX){
				valor = aux;
			}
			aux =  get_matriz(mat2,i,j);
			if(aux != INT_MAX){
				valor += aux;
			}
			if(valor != 0){
				set_matriz(matRes,i,j,valor);
				valor = 0;
			}
		}
	}	

	return matRes;
}

//Impressão da matriz
void imprimir_matriz(MATRIZ_ESPARSA *mat){
		
	int i,j,retorno;

	//Pegando a primeira linha
	mat->posLin = mat->begin->abaixo;
	
	printf("-1 %d %d\n",mat->nr_linhas,mat->nr_colunas);
	
	for(i=0;i<mat->nr_linhas;i++){
		for(j=0;j<mat->nr_colunas;j++){
			retorno = get_matriz(mat,i,j);
			if(retorno != 0 && retorno != INT_MAX){
				printf("%d %d %d\n",i,j,retorno);
			}
			if(retorno == INT_MAX){
				j = mat->nr_colunas;
			}
		}
	}	
}
