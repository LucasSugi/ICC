#include <stdio.h>
#include <stdlib.h>

#define nrow 8
#define ncol 8

#define FALSE 0
#define TRUE 1

//Estrutura para controle do xadrez
typedef struct{
	char xadrez;
} BOARD;

//Criando um tabuleiro
BOARD **createBoard(){
	
	int i,j;
	BOARD **board = NULL;
	
	//Alocando e inicializando	
	board = (BOARD**) malloc(sizeof(BOARD*) * nrow); 
	for(i=0;i<nrow;i++){
		board[i] = (BOARD*) malloc(sizeof(BOARD) * ncol);
		for(j=0;j<ncol;j++){
			board[i][j].xadrez = '.';
		}
	}
	
	return board;
}

//Desalocando o tabuleiro
void destroyBoard(BOARD **board){
	
	int i;

	for(i=0;i<nrow;i++){
		free(board[i]);
	}
	free(board);
}

//Impressaod do tabuleiro
void printBoard(BOARD **board){
	
	int i,j;

	for(i=0;i<nrow;i++){
		for(j=0;j<ncol;j++){
			printf("%c",board[i][j].xadrez);
		}
		printf("\n");
	}
	printf("\n");
}

//Verificando se o tabuleiro esta consistente
int correctBoard(BOARD **board, int row, int col){

	int i;
	int tempRow,tempCol;
	
	//Verificando se ha outra rainha na direcao: NOROESTE
	tempRow = row-1;
	tempCol = col-1;
	while(tempRow >= 0 && tempCol >= 0){
		if(board[tempRow][tempCol].xadrez == 'Q'){
			return FALSE;	
		}
		tempRow--;
		tempCol--;	
	}

	//Verificando se ha outra rainha na direcao: NORDESTE
	tempRow = row-1;
	tempCol = col+1;
	while(tempRow >= 0 && tempCol < ncol){
		if(board[tempRow][tempCol].xadrez == 'Q'){
			return FALSE;	
		}
		tempRow--;
		tempCol++;	
	}

	//Verificando se ha outra rainha na direcao: SUDESTE
	tempRow = row+1;
	tempCol = col+1;
	while(tempRow < nrow && tempCol < ncol){
		if(board[tempRow][tempCol].xadrez == 'Q'){
			return FALSE;	
		}
		tempRow++;
		tempCol++;	
	}
	
	//Verificando se ha outra rainha na direcao: SUDOESTE
	tempRow = row+1;
	tempCol = col-1;
	while(tempRow < nrow && tempCol >= 0){
		if(board[tempRow][tempCol].xadrez == 'Q'){
			return FALSE;	
		}
		tempRow++;
		tempCol--;	
	}

	return TRUE;
}

//Verifica se na coluna existe rainha
int verifyCol(BOARD **board, int row, int col){
	
	int i;

	//Verificando se ha outra rainha na coluna
	for(i=0;i<ncol;i++){
		if(board[i][col].xadrez == 'Q' && i != row){
			return FALSE;	
		}	
	}
	return TRUE;
}

//Algoritmo para resolver o problema das 8 rainhas
void queen(BOARD **board, int row){
	
	int i,j;
	int flag = TRUE;
	
	//Condicao de parada
	if(row == nrow){
		for(i=0;i<nrow;i++){
			for(j=0;j<ncol;j++){
				if(board[i][j].xadrez == 'Q'){
					if(correctBoard(board,i,j) == FALSE){
						flag = FALSE;	
						break;
					}
				}	
			}
		}	
		if(flag == TRUE) printBoard(board);
	}

	//Recursao
	for(i=0;i<nrow;i++){
		if(verifyCol(board,row,i) != FALSE){
			board[row][i].xadrez = 'Q';
			queen(board,row+1);
			board[row][i].xadrez = '.';
		}
	}
}

int main(int argc, char *argv[]){

	BOARD **board = NULL;

	//Criando tabuleiro
	board = createBoard();	

	//Resolvendo problema
	queen(board,0);

	//Desalocando tabuleiro
	destroyBoard(board);

	return 0;
}
