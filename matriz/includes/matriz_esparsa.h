/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#ifndef _MATRIZ_ESPARSA_H_
#define _MATRIZ_ESPARSA_H_

//Definindo a estrutura matriz
typedef struct matriz_esparsa MATRIZ_ESPARSA;

//Criação e alocação da matriz
MATRIZ_ESPARSA *criar_matriz(int, int);

//Desalocação de toda memória alocada pela matriz
void apagar_matriz(MATRIZ_ESPARSA **);

//Setando um valor na matriz
int set_matriz(MATRIZ_ESPARSA *, int, int, int);

//Recuperando um valor da matriz dado uma linha e coluna
int get_matriz(MATRIZ_ESPARSA *, int, int);

//Multiplicação das matrizes 
MATRIZ_ESPARSA *multiplicar_matriz(MATRIZ_ESPARSA *, MATRIZ_ESPARSA *);

//Soma das matrizes
MATRIZ_ESPARSA *somar_matriz(MATRIZ_ESPARSA *, MATRIZ_ESPARSA *);

//Impressão de todos os elementos da matriz
void imprimir_matriz(MATRIZ_ESPARSA *);

#endif
