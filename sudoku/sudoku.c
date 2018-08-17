#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ncol 9
#define nrow 9

#define FALSE 0
#define TRUE 1

typedef struct{
	char sudoku;
	int flag;
} BOARD;

//Leitura da tabela do sudoku
BOARD **readBoard(){

	int i,j,k;
	BOARD **board;
	FILE *fp;
	
	//Alocando quadro
	board = (BOARD**) malloc(sizeof(BOARD*) * nrow);
	for(i=0;i<nrow;i++){
		board[i] = (BOARD*) malloc(sizeof(BOARD) * ncol);
	}
	
	//Abertura arquivo
	fp = fopen("data","r");
		
	//Leitura
	for(i=0;i<nrow;i++){
		for(j=0;j<ncol;j++){
			board[i][j].sudoku = getc(fp);
			if(board[i][j].sudoku == '.'){
				board[i][j].flag = FALSE;
			}
			else{
				board[i][j].flag= TRUE;
			}
		}
		//Leitura da quebra de linha
		getc(fp);
	}

	//Fechando arquivo
	fclose(fp);

	return board;
}

//Impressao do tabuleiro
void printBoard(BOARD **board){
	
	int i,j;

	for(i=0;i<nrow;i++){
		for(j=0;j<ncol;j++){
			printf("%c",board[i][j].sudoku);
		}
		printf("\n");
	}
}

//Testa se o tabuleiro esta consistente
int boardCorrect(BOARD **board, int row, int col){
	
	int i,j;
	int rowQuadrant, colQuadrant;

	//Verificando se a linha esta correta
	for(i=0;i<ncol;i++){
		if(board[row][i].sudoku == board[row][col].sudoku && col != i){
			//Tabuleiro inconsistente		
			return FALSE;
		}	
	}

	//Verificando se a coluna esta correta
	for(i=0;i<nrow;i++){
		if(board[i][col].sudoku == board[row][col].sudoku && row != i){
			//Tabuleiro inconsistente		
			return FALSE;
		}	
	}	

	//Calculando a linha e a coluna do quadrante	
	rowQuadrant = row / (sqrt(nrow)); 
	rowQuadrant =  rowQuadrant * sqrt(nrow); 
	colQuadrant = col / (sqrt(ncol));
	colQuadrant = colQuadrant *sqrt(ncol); 
	
	//Verificando se o quadrante esta correto
	for(i=rowQuadrant;i<sqrt(nrow)+rowQuadrant;i++){
		for(j=colQuadrant;j<sqrt(ncol)+colQuadrant;j++){
			if(board[i][j].sudoku == board[row][col].sudoku && i != row && j != col){
				//Tabuleiro inconsistente		
				return FALSE;
			}
		}
	}

	return TRUE;
}

//Calculo da proxima posicao
int nextPosition(int *row, int *col){
	
	*col = ((*col)+1) % ncol;	
	
	if(*col == 0) { 
		*row = ((*row)+1) % nrow; 
		if(*row == 0){
			return TRUE;
		}
	}
	return FALSE;
}

//Resolucao do sudoku por backtracking
int backtracking(BOARD **board, int row, int col){

	int i;
	int newRow,newCol;
	int ret = FALSE;

	if(board[row][col].flag == TRUE) {
		if(nextPosition(&row,&col) == TRUE) { return TRUE; }
		ret = backtracking(board,row,col);
		if(ret == TRUE) {
			return TRUE;
		} 
		else if(board[row][col].flag != TRUE){
			board[row][col].sudoku = '.';		
		}
	}	
	else{
		for(i=1;i<=nrow;i++){
			board[row][col].sudoku = i + 48;
			if(boardCorrect(board,row,col) == TRUE){
				newRow = row;
				newCol = col;
				if(nextPosition(&newRow,&newCol) == TRUE) { return TRUE; }
				ret = backtracking(board,newRow,newCol);
				if(ret == TRUE) {
					return TRUE;
				} 
				else if(board[newRow][newCol].flag != TRUE){
					board[newRow][newCol].sudoku = '.';		
				}
			}
		}		
	}
	return ret;
}

//Desalocando memoria da esturura TABELA
void destroyBoard(BOARD **board){
	
	int i;
	
	//Liberando memoria
	for(i=0;i<nrow;i++){
		free(board[i]);
	}	
	free(board);
}

//Cabecalho da funcao que verifica se o tabuleiro esta correto
void verifyBoard(BOARD **board);

int main(int argc, char *argv[]){
	
	BOARD **board;

	//Lendo tabuleiro
	board = readBoard();

	//Resolucao do sudoku
	backtracking(board,0,0);

	//Impressao do tabuleiro
	printBoard(board);
	
	//Verifica o tabuleiro
	verifyBoard(board);
	
	//Desalocando memoria
	destroyBoard(board);
		
	return 0;
}

//Verifica se o tabuleiro esta correto
void verifyBoard(BOARD **board){
	
	int i,j;
	int x,y;
	int sum = 45;
	int test;

	//Teste
	for(i=0;i<nrow;i++){
		for(j=0;j<ncol;j++){
			if(board[i][j].sudoku != '.' && boardCorrect(board,i,j) == FALSE){
				printf("Inconsistente\n");
				return;
			}
		}
	}
	
	//Testando as linhas
	for(i=0;i<nrow;i++){		
		test = 0;
		for(j=0;j<ncol;j++){
			test += board[i][j].sudoku - 48;	
		}
		if(test != 45) {
			printf("Errado - linha\n");
			return;
		}
	}

	//Testando as colunas
	for(i=0;i<ncol;i++){		
		test = 0;
		for(j=0;j<nrow;j++){
			test += board[j][i].sudoku- 48;	
		}
		if(test != 45) {
			printf("Errado - coluna\n");
			return;
		}
	}

	//Testando o quadrante
	x = y = 0;
	test = 0;
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			test += board[i][j].sudoku - 48;	
		}
	}
	if(test != 45) { printf("Errado - 1\n"); return;}

	//Testando o quadrante
	x = 0;
	y = 3;
	test = 0;
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			test += board[i][j].sudoku - 48;	
		}
	}
	if(test != 45) { printf("Errado - 2\n"); return;}	
	
	//Testando o quadrante
	x = 0;
	y = 6;
	test = 0;
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			test += board[i][j].sudoku - 48;	
		}
	}
	if(test != 45) { printf("Errado - 3\n"); return;}

	//Testando o quadrante
	x = 3;
	y = 0;
	test = 0;
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			test += board[i][j].sudoku - 48;	
		}
	}
	if(test != 45) { printf("Errado - 4\n"); return;}	
	
	//Testando o quadrante
	x = 3;
	y = 3;
	test = 0;
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			test += board[i][j].sudoku - 48;	
		}
	}
	if(test != 45) { printf("Errado - 5\n"); return;}	
	
	//Testando o quadrante
	x = 3;
	y = 6;
	test = 0;
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			test += board[i][j].sudoku - 48;	
		}
	}
	if(test != 45) { printf("Errado - 6\n"); return;}

	//Testando o quadrante
	x = 6;
	y = 0;
	test = 0;
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			test += board[i][j].sudoku - 48;	
		}
	}
	if(test != 45) { printf("Errado - 7\n"); return;}	
	
	//Testando o quadrante
	x = 6;
	y = 3;
	test = 0;
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			test += board[i][j].sudoku - 48;	
		}
	}
	if(test != 45) { printf("Errado - 8\n"); return;}	
	
	//Testando o quadrante
	x = 6;
	y = 6;
	test = 0;
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			test += board[i][j].sudoku - 48;	
		}
	}
	if(test != 45) { printf("Errado - 9\n"); return;}
	

	printf("Certo\n");
}
