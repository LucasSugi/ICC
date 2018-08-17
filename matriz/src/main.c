/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include "matriz_esparsa.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	MATRIZ_ESPARSA *matA, *matB, *matC;
	char option;
	int nr_linhas, nr_colunas, valor;
	
	//Definindo a opção
	scanf("%c",&option);

	//Lendo a quantidade de linhas e colunas da matriz A
	scanf("%d %d %d",&valor,&nr_linhas,&nr_colunas);

	//Criando a matriz A
	matA = criar_matriz(nr_linhas,nr_colunas);

	//Armazenando os valores em A
	while( scanf("%d %d %d",&nr_linhas,&nr_colunas,&valor) && nr_linhas != -1){
		set_matriz(matA,nr_linhas,nr_colunas,valor);
	}

	//Criando a matriz B
	matB = criar_matriz(nr_colunas,valor);

	//Armazenando os valor em B
	while( scanf("%d %d %d",&nr_linhas,&nr_colunas,&valor) && nr_linhas != -1){
		set_matriz(matB,nr_linhas,nr_colunas,valor);
	}
		
	//Calculando a matriz resultante de acordo com a operação definida
	if(option == 'M'){
		matC = multiplicar_matriz(matA,matB);
	}
	else {
		matC = somar_matriz(matA,matB);
	}

	//Imprimindo a matriz resultante
	imprimir_matriz(matC);

	//Apagando todas as matrizes
	apagar_matriz(&matA);
	apagar_matriz(&matB);
	apagar_matriz(&matC);

	return 0;
}
