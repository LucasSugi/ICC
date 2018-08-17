#include "matriz_esparsa.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct CELULA { 
	int linha;
	int coluna;
	float valor;
	struct CELULA *direita;
	struct CELULA *abaixo;
} CELULA;

struct matriz_esparsa {
	CELULA **linhas;	
	CELULA **colunas;
	int nr_linhas;	
	int nr_colunas;
};

MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas){

	MATRIZ_ESPARSA *mat = (MATRIZ_ESPARSA*) malloc(sizeof(MATRIZ_ESPARSA));

	if(mat != NULL){
		mat->nr_linhas = nr_linhas;
		mat->nr_colunas = nr_colunas;
		mat->linhas = (CELULA**) malloc(sizeof(CELULA*) * nr_linhas);
		mat->colunas = (CELULA**) malloc(sizeof(CELULA*) * nr_colunas);			

		if(mat->linhas != NULL && mat->colunas != NULL){
			int i;
			for(i=0;i<nr_linhas;i++){
				mat->linhas[i] = (CELULA*) malloc(sizeof(CELULA));
				mat->linhas[i]->linha = i;
				mat->linhas[i]->coluna = 0;
				mat->linhas[i]->valor = 0;
				mat->linhas[i]->direita = NULL;
			}	
			
			for(i=0;i<nr_colunas;i++){
				mat->colunas[i] = (CELULA*) malloc(sizeof(CELULA));
				mat->colunas[i]->coluna = i;  
				mat->colunas[i]->linha = 0;  
				mat->colunas[i]->valor = 0;
				mat->colunas[i]->abaixo = NULL;
			}	
			
		} else{
			mat->linhas == NULL ? mat->linhas = NULL : free(mat->linhas);
			mat->colunas == NULL ? mat->colunas = NULL : free(mat->colunas);
		}
	}
	return mat;
}

int set(MATRIZ_ESPARSA *mat, int lin, int col, float val){

	if(lin < mat->nr_linhas && col < mat->nr_colunas){
		CELULA *paux = mat->linhas[lin];

		while( paux->direita != NULL && paux->direita->coluna <= col){
			paux = paux->direita;	
		}


		if(paux->coluna == col){
			paux->valor = val;
		}	
		else {
			CELULA *pnovo = (CELULA*) malloc(sizeof(CELULA));
			if(pnovo != NULL){
				pnovo->linha = lin;
				pnovo->coluna = col;
				pnovo->valor = val;
				pnovo->direita = paux->direita;
				paux->direita = pnovo;		

				paux = mat->colunas[col];
				while(paux->abaixo != NULL && paux->abaixo->linha <= lin){
					paux = paux->abaixo;
				}

				pnovo->abaixo = paux->abaixo;
				paux->abaixo = pnovo;
			}
			return 1;
		}
	}
	
	return 0;
}

float get(MATRIZ_ESPARSA *mat, int lin, int col){

	if(lin < mat->nr_linhas && col < mat->nr_colunas){
		CELULA *paux = mat->linhas[lin];
		
		while(paux->direita != NULL && paux->direita->coluna <= col){
			paux = paux->direita;
		}
		
		if(paux->coluna == col){
			return paux->valor;
		}
	}		
	
	return 0;
}

void imprimir_matriz(MATRIZ_ESPARSA *mat){

	int i,j;

	for(i=0;i<mat->nr_linhas;i++){
		for(j=0;j<mat->nr_colunas;j++){
			printf("%.1lf\t",get(mat,i,j));
		}
		printf("\n");
	}	
}

void apagar_matriz(MATRIZ_ESPARSA **mat){
	int i;
	
	for(i=0;i<(*mat)->nr_linhas;i++){
		CELULA *paux = (*mat)->linhas[i];

		while(paux != NULL){
			CELULA *prem = paux;
			paux = paux->direita;
			free(prem);
		}
		
	}

	for(i=0;i<(*mat)->nr_colunas;i++){
		free( (*mat)->colunas[i] );
	}

	free( (*mat)->linhas );
	free( (*mat)->colunas );
	free(*mat);
	*mat = NULL;
}
