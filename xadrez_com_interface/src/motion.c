/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
*/

#include "motion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
#include <ctype.h>


//Enum que irá indicar a posição de cada peça na struct
enum{

	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
};

/*
Inicializando o xadrez
Parâmetros: char *
Retorno: XADREZ *
*/
XADREZ *start_xadrez(){

	int i,j,k;
	int value;
	XADREZ *xadrez = NULL;
	char start[100];
	char aux[100];

	//Alocando a estrutura
	xadrez = (XADREZ*) malloc(sizeof(XADREZ));

	//Alocação do tabuleiro - linhas
	xadrez->board = (BOARD**) malloc(sizeof(BOARD*) * RANKS);
		
	//Alocação do tabuleiro - colunas
	for(i=0;i<RANKS;i++){
		xadrez->board[i] = (BOARD*) malloc(sizeof(BOARD) * FILES);
	}
	
	//Zerando variável	
	k = 0;

	//Leitura do tabuleiro
	scanf("%s",start);
	
	//Inicializando o tabuleiro
	for(i=0;i<RANKS;i++){
		for(j=0;j<FILES;j++){
			if(start[k] == 'p'){
				xadrez->board[i][j].piece = 'p';
				k++;
			}
			else if(start[k] == 'n'){
				xadrez->board[i][j].piece = 'n';
				k++;
			}
			else if(start[k] == 'b'){
				xadrez->board[i][j].piece = 'b';
				k++;
			}
			else if(start[k] == 'r'){
				xadrez->board[i][j].piece = 'r';
				k++;
			}
			else if(start[k] == 'q'){
				xadrez->board[i][j].piece = 'q';
				k++;
			}
			else if(start[k] == 'k'){
				xadrez->board[i][j].piece = 'k';
				k++;
			}
			else if(start[k] == 'P'){
				xadrez->board[i][j].piece = 'P';
				k++;
			}
			else if(start[k] == 'N'){
				xadrez->board[i][j].piece = 'N';
				k++;
			}
			else if(start[k] == 'B'){
				xadrez->board[i][j].piece = 'B';
				k++;
			}
			else if(start[k] == 'R'){
				xadrez->board[i][j].piece = 'R';
				k++;
			}
			else if(start[k] == 'Q'){
				xadrez->board[i][j].piece = 'Q';
				k++;
			}
			else if(start[k] == 'K'){
				xadrez->board[i][j].piece = 'K';
				k++;
			}
			else if( 48 < start[k] && start[k] < 57){
				value = (int)start[k] - 48;		
				while(value > 0){
					xadrez->board[i][j].piece = empty;
					j++;
					value--;
				}
				k++;
				j--;
			}
			else if(start[k] == '/'){
				k++;
				j--;
			}
		}
	}

	//Leitura de quem joga primeiro
	k = 0;
	scanf("%s",start);

	//Inicializando quem joga primeiro
	xadrez->turn = start[k];	

	//Leitura sobre o roque
	scanf("%s",start);
	
	//Alocando a estrutura roque
	xadrez->roque = (ROQUE*) malloc(sizeof(ROQUE));
	
	//Alocando a ocorrência de roque e a inicializando
	xadrez->roque->roqueWhite = (char*) malloc(sizeof(char) * 2);
	xadrez->roque->roqueBlack = (char*) malloc(sizeof(char) * 2);
	xadrez->roque->roqueWhite[0] = '-';	
	xadrez->roque->roqueBlack[0] = '-';	
	xadrez->roque->roqueWhite[1] = '-';	
	xadrez->roque->roqueBlack[1] = '-';	

	//Verificando a ocorrencia de roque
	while( start[k] != '\0'){
		if(start[k] == 'k'){
			xadrez->roque->roqueBlack[0] = 'k';
		}
		else if(start[k] == 'q'){
			xadrez->roque->roqueBlack[1] = 'q';
		}
		else if(start[k] == 'K'){
			xadrez->roque->roqueWhite[0] = 'K';
		}
		else if(start[k] == 'Q'){
			xadrez->roque->roqueWhite[1] = 'Q';
		}
		k++;
	}
	

	//Leitura do en passant
	k = 0;
	scanf("%s",start);

	//Alocando a estrutura de en passant e inicializando
	xadrez->en_passant = (EN_PASSANT*) malloc(sizeof(EN_PASSANT));
		
	//Armazenando o en passant
	while(start[k] != '\0'){
		if(start[k] == '-'){
			xadrez->en_passant->rank = -1;
			xadrez->en_passant->file = -1;
		}
		else if(96 < start[k] && start[k] < 105){
			xadrez->en_passant->file = (int)start[k] - 97;
		}
		else if(48 < start[k] && start[k] < 57){
			xadrez->en_passant->rank = FILES - ((int)start[k] - 48);
		}
		k++;	
	}

	//Leitura do meio turno
	k = i = 0;
	scanf("%s",start);

	//Armazenando o meio-turno	
	while(start[k] != '\0'){
		aux[i++] = start[k++];
	}
	aux[i] = '\0';
	xadrez->middle_turn = atoi(aux);

	//Leitura do turno
	k = i = 0;
	scanf("%s",start);
	
	//Armazenando o turno
	while(start[k] != '\0'){
		aux[i++] = start[k++];
	}
	aux[i] = '\0';
	xadrez->num_turn = atoi(aux);

	return xadrez;
}

/*
Desalocando o xadrez
Parâmetros: XADREZ *
Retorno: nenhum
*/
void destroy_xadrez(XADREZ *xadrez){

	int i;

	//Desalocação do tabuleiro
	for(i=0;i<RANKS;i++){
		free(xadrez->board[i]);
	}
	free(xadrez->board);

	//Desalocação do roque
	free(xadrez->roque->roqueBlack);
	free(xadrez->roque->roqueWhite);
	free(xadrez->roque);

	//Desalocação do en passant
	free(xadrez->en_passant);

	//Desalocação do xadrez
	free(xadrez);
}

/*
Criando e inicializando a estrutura que irá armazenar os movimentos
Parâmetros: XADREZ *
Retorno: nenhum
*/
MOTION *create_motion(XADREZ *xadrez){
	
	int i,j;
	int aux;

	//Alocando a estrutura de movimento
	MOTION *motion = (MOTION*) malloc(sizeof(MOTION));
	
	//Alocando a estrutura para as peças brancas e pretas
	motion->white = (INFO_MOTION*) malloc(sizeof(INFO_MOTION) * AMOUNT_PIECE);
	motion->black = (INFO_MOTION*) malloc(sizeof(INFO_MOTION) * AMOUNT_PIECE);
	
	//Inicializando essa estrutura
	for(i=0;i<AMOUNT_PIECE;i++){
		motion->white[i].coor = NULL;
		motion->white[i].amount_piece = 0;
		motion->black[i].coor = NULL;
		motion->black[i].amount_piece = 0;
	}
	
	//Percorrendo o xadrez a procura das posições inicias das peças	
	for(i=0;i<RANKS;i++){
		for(j=0;j<FILES;j++){
			if(xadrez->board[i][j].piece == 'p'){
				motion->black[PAWN].coor = (COOR*) realloc(motion->black[PAWN].coor,sizeof(COOR)*(++motion->black[PAWN].amount_piece));
				motion->black[PAWN].coor[motion->black[PAWN].amount_piece-1].actual_lin = i;
				motion->black[PAWN].coor[motion->black[PAWN].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'n'){
				motion->black[KNIGHT].coor = (COOR*) realloc(motion->black[KNIGHT].coor,sizeof(COOR)*(++motion->black[KNIGHT].amount_piece));
				motion->black[KNIGHT].coor[motion->black[KNIGHT].amount_piece-1].actual_lin = i;
				motion->black[KNIGHT].coor[motion->black[KNIGHT].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'b'){
				motion->black[BISHOP].coor = (COOR*) realloc(motion->black[BISHOP].coor,sizeof(COOR)*(++motion->black[BISHOP].amount_piece));
				motion->black[BISHOP].coor[motion->black[BISHOP].amount_piece-1].actual_lin = i;
				motion->black[BISHOP].coor[motion->black[BISHOP].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'r'){
				motion->black[ROOK].coor = (COOR*) realloc(motion->black[ROOK].coor,sizeof(COOR)*(++motion->black[ROOK].amount_piece));
				motion->black[ROOK].coor[motion->black[ROOK].amount_piece-1].actual_lin = i;
				motion->black[ROOK].coor[motion->black[ROOK].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'q'){
				motion->black[QUEEN].coor = (COOR*) realloc(motion->black[QUEEN].coor,sizeof(COOR)*(++motion->black[QUEEN].amount_piece));
				motion->black[QUEEN].coor[motion->black[QUEEN].amount_piece-1].actual_lin = i;
				motion->black[QUEEN].coor[motion->black[QUEEN].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'k'){
				motion->black[KING].coor = (COOR*) realloc(motion->black[KING].coor,sizeof(COOR)*(++motion->black[KING].amount_piece));
				motion->black[KING].coor[motion->black[KING].amount_piece-1].actual_lin = i;
				motion->black[KING].coor[motion->black[KING].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'P'){
				motion->white[PAWN].coor = (COOR*) realloc(motion->white[PAWN].coor,sizeof(COOR)*(++motion->white[PAWN].amount_piece));
				motion->white[PAWN].coor[motion->white[PAWN].amount_piece-1].actual_lin = i;
				motion->white[PAWN].coor[motion->white[PAWN].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'N'){
				motion->white[KNIGHT].coor = (COOR*) realloc(motion->white[KNIGHT].coor,sizeof(COOR)*(++motion->white[KNIGHT].amount_piece));
				motion->white[KNIGHT].coor[motion->white[KNIGHT].amount_piece-1].actual_lin = i;
				motion->white[KNIGHT].coor[motion->white[KNIGHT].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'B'){
				motion->white[BISHOP].coor = (COOR*) realloc(motion->white[BISHOP].coor,sizeof(COOR)*(++motion->white[BISHOP].amount_piece));
				motion->white[BISHOP].coor[motion->white[BISHOP].amount_piece-1].actual_lin = i;
				motion->white[BISHOP].coor[motion->white[BISHOP].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'R'){
				motion->white[ROOK].coor = (COOR*) realloc(motion->white[ROOK].coor,sizeof(COOR)*(++motion->white[ROOK].amount_piece));
				motion->white[ROOK].coor[motion->white[ROOK].amount_piece-1].actual_lin = i;
				motion->white[ROOK].coor[motion->white[ROOK].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'Q'){
				motion->white[QUEEN].coor = (COOR*) realloc(motion->white[QUEEN].coor,sizeof(COOR)*(++motion->white[QUEEN].amount_piece));
				motion->white[QUEEN].coor[motion->white[QUEEN].amount_piece-1].actual_lin = i;
				motion->white[QUEEN].coor[motion->white[QUEEN].amount_piece-1].actual_col = j;
			}
			else if(xadrez->board[i][j].piece == 'K'){
				motion->white[KING].coor = (COOR*) realloc(motion->white[KING].coor,sizeof(COOR)*(++motion->white[KING].amount_piece));
				motion->white[KING].coor[motion->white[KING].amount_piece-1].actual_lin = i;
				motion->white[KING].coor[motion->white[KING].amount_piece-1].actual_col = j;
			}
		}
	}		
	
	//Inicializando toda a estrutura
	for(i=0;i<AMOUNT_PIECE;i++){
		aux = motion->black[i].amount_piece;
		j = 0;
		while(aux>0){
			motion->black[i].coor[j].lin = NULL;
			motion->black[i].coor[j].col = NULL;
			motion->black[i].coor[j].catch_piece = NULL;
			motion->black[i].coor[j].promotion = NULL;
			motion->black[i].coor[j].en_passant = NULL;
			motion->black[i].coor[j].equal = NULL;
			motion->black[i].coor[j].amount_motion = 0;
			aux--;
			j++;
		}
		aux = motion->white[i].amount_piece;
		j = 0;
		while(aux>0){
			motion->white[i].coor[j].lin = NULL;
			motion->white[i].coor[j].col = NULL;
			motion->white[i].coor[j].catch_piece = NULL;
			motion->white[i].coor[j].promotion = NULL;
			motion->white[i].coor[j].en_passant = NULL;
			motion->white[i].coor[j].equal = NULL;
			motion->white[i].coor[j].amount_motion = 0;
			aux--;
			j++;
		}
	}

	return motion;
}

/*
Desalocando a estrutura que armazena os movimentos
Parâmetros: MOTION *
Retorno: nenhum
*/
void destroy_motion(MOTION *motion){

	int i,j,k;

	//Percorrendo todas as peças para desalocação
	for(i=0;i<AMOUNT_PIECE;i++){
			//Percorrendo todas as peças do mesmo tipo
			j = motion->white[i].amount_piece;
			while(j-1>=0){
				motion->white[i].coor[j-1].lin == NULL ? : free(motion->white[i].coor[j-1].lin);
				motion->white[i].coor[j-1].col == NULL ? : free(motion->white[i].coor[j-1].col);
				motion->white[i].coor[j-1].catch_piece == NULL ? : free(motion->white[i].coor[j-1].catch_piece);
				motion->white[i].coor[j-1].promotion == NULL ? : free(motion->white[i].coor[j-1].promotion);
				motion->white[i].coor[j-1].en_passant == NULL ? : free(motion->white[i].coor[j-1].en_passant);
				motion->white[i].coor[j-1].equal == NULL ? : free(motion->white[i].coor[j-1].equal);
				j--;
			}
			//Desalocando os movimentos
			motion->white[i].coor == NULL ? : free(motion->white[i].coor);	

			//Percorrendo todas as peças do mesmo tipo
			j = motion->black[i].amount_piece;
			while(j-1>=0){
				motion->black[i].coor[j-1].lin == NULL ? : free(motion->black[i].coor[j-1].lin);
				motion->black[i].coor[j-1].col == NULL ? : free(motion->black[i].coor[j-1].col);
				motion->black[i].coor[j-1].catch_piece == NULL ? : free(motion->black[i].coor[j-1].catch_piece);
				motion->black[i].coor[j-1].promotion == NULL ? : free(motion->black[i].coor[j-1].promotion);
				motion->black[i].coor[j-1].en_passant == NULL ? : free(motion->black[i].coor[j-1].en_passant);
				motion->black[i].coor[j-1].equal == NULL ? : free(motion->black[i].coor[j-1].equal);
				j--;
			}
			//Desalocando os movimentos
			motion->black[i].coor == NULL ? : free(motion->black[i].coor);
	}
	//Desalocação das peças brancas e pretas
	free(motion->white);
	free(motion->black);
	free(motion);
}

/*
Função auxliar que irá percorrer os movimentos de cada peça para verificar se há algum igual
Parâmetros: COOR *, int
Retorno: nenhum
*/
void aux_equal_motion(COOR *coor, int n){

	int i,j,k;
	int pos;
	int amountMotion;
	int aux;

	//Percorrrendo a peça
	for(i=1;i<n;i++){
		amountMotion = coor[i].amount_motion;
		j = 0;
		//Percorrendo os movimentos que a peça possui
		while(amountMotion-- > 0){
			for(k=0;k<i;k++){
				aux = coor[k].amount_motion;
				pos = 0;
				//Comparação para verificar se o movimento é igual caso seja, o campo equal é setado como 1
				while(aux-- > 0){
					if(coor[i].col[j] == coor[k].col[pos] && coor[i].lin[j] == coor[k].lin[pos]){
						coor[k].equal[pos] = YES;
						coor[i].equal[j] = YES;
					}
					pos++;
				}
			}
			j++;
		}
	}
}

/*
Procurando por movimentos iguais
Parâmetros: INFO_MOTION *
Retorno: nenhum
*/
void equal_motion(INFO_MOTION *info_motion){

	int i,j;
	int amountPiece;

	//Alocação da variável que irá armazenar se existem valores iguais
	for(i=0;i<AMOUNT_PIECE;i++){
		amountPiece = info_motion[i].amount_piece;
		j = 0;
		while(amountPiece-- > 0){
			info_motion[i].coor[j].equal = (int*) calloc(info_motion[i].coor[j].amount_motion,sizeof(int));
			j++;
		}
		//Percorrendo os movimentos de cada peça para verificar se há movimentos iguais
		if(info_motion[i].amount_piece > 1){
			aux_equal_motion(info_motion[i].coor, info_motion[i].amount_piece);
		}
	}
}

/*
Função responsável por verificar se o movimento a ser realizado irá causar um cheque ou não
Parâmetros: GEN_MOTION *, XADREZ *, MOTION *, int, int, int, int, char, char, int
Retorno: int
*/	
int checkmate(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, int actual_lin, int actual_col,int move_lin, int move_col,char color, char piece, int control){

	int ret = 0;
	MOTION *motion_aux;
	char movePiece;

	if(control == 0){
		//Armazenando a peça ou uma casa vazia que se encontra na posição em que irá ocorrer o movimento
		movePiece = xadrez->board[move_lin][move_col].piece;

		//A peça é movida para tal posição
		if(color == 'w')xadrez->board[move_lin][move_col].piece = piece; 
		else xadrez->board[move_lin][move_col].piece = tolower(piece);

		//Colocando vazio no lugar a onde a peça se encontrava
		xadrez->board[actual_lin][actual_col].piece = empty;

		//Calculando os novos movimentos
		motion_aux = create_motion(xadrez);

		//Gerando os movimentos para verificar se existe cheque
		if(color == 'w'){
			ret = generate_motion(gen_motion,xadrez,motion_aux,'b',1);	
		}
		else{
			ret = generate_motion(gen_motion,xadrez,motion_aux,'w',1);
		}

		//Desalocando a estrutura auxiliar
		destroy_motion(motion_aux);

		//Retornando as condições iniciais antes do movimento
		if(color == 'w')xadrez->board[actual_lin][actual_col].piece = piece;
		else xadrez->board[actual_lin][actual_col].piece = tolower(piece);
		xadrez->board[move_lin][move_col].piece = movePiece;
	}
	else{
		//Verificando se para onde o a peça será movido o rei é capturado
		if(color == 'w'){
			if(xadrez->board[move_lin][move_col].piece == 'k') return 1;
		}
		else{
			if(xadrez->board[move_lin][move_col].piece == 'K') return 1;	
		}
	}
	return ret;
}

/*
Alocação do movimento que o peão possa realizar
Parâmetros: MOTION *, char, int, int , int , int , int , int
Retorno: nenhum
*/
void alloc_motion_pawn(MOTION *motion,char color,int pos, int counter,int lin, int col, int catch_piece, int promotion, int en_passant){
	
	//Aloca-se o as coordenadas e se é possível realizar ou não: captura, promoção, en passant		
	if(color == 'w'){
		motion->white[PAWN].coor[pos].lin = (int*) realloc(motion->white[PAWN].coor[pos].lin,sizeof(int)*counter);
		motion->white[PAWN].coor[pos].col = (int*) realloc(motion->white[PAWN].coor[pos].col,sizeof(int)*counter);
		motion->white[PAWN].coor[pos].catch_piece = (int*) realloc(motion->white[PAWN].coor[pos].catch_piece,sizeof(int)*counter);
		motion->white[PAWN].coor[pos].promotion = (int*) realloc(motion->white[PAWN].coor[pos].promotion,sizeof(int)*counter);
		motion->white[PAWN].coor[pos].en_passant = (int*) realloc(motion->white[PAWN].coor[pos].en_passant,sizeof(int)*counter);

		motion->white[PAWN].coor[pos].lin[counter-1] = lin;
		motion->white[PAWN].coor[pos].col[counter-1] = col;
		motion->white[PAWN].coor[pos].catch_piece[counter-1] = catch_piece;
		motion->white[PAWN].coor[pos].promotion[counter-1] = promotion;
		motion->white[PAWN].coor[pos].en_passant[counter-1] = en_passant;
		motion->white[PAWN].coor[pos].amount_motion++;
	}
	else{
		motion->black[PAWN].coor[pos].lin = (int*) realloc(motion->black[PAWN].coor[pos].lin,sizeof(int)*counter);
		motion->black[PAWN].coor[pos].col = (int*) realloc(motion->black[PAWN].coor[pos].col,sizeof(int)*counter);
		motion->black[PAWN].coor[pos].catch_piece = (int*) realloc(motion->black[PAWN].coor[pos].catch_piece,sizeof(int)*counter);
		motion->black[PAWN].coor[pos].promotion = (int*) realloc(motion->black[PAWN].coor[pos].promotion,sizeof(int)*counter);
		motion->black[PAWN].coor[pos].en_passant = (int*) realloc(motion->black[PAWN].coor[pos].en_passant,sizeof(int)*counter);

		motion->black[PAWN].coor[pos].lin[counter-1] = lin;
		motion->black[PAWN].coor[pos].col[counter-1] = col;
		motion->black[PAWN].coor[pos].catch_piece[counter-1] = catch_piece;
		motion->black[PAWN].coor[pos].promotion[counter-1] = promotion;
		motion->black[PAWN].coor[pos].en_passant[counter-1] = en_passant;
		motion->black[PAWN].coor[pos].amount_motion++;	
	}
}


/*
Cálculo dos movimentos - peão
Parâmetro: GEN_MOTION *, XADREZ *, MOTION *, char, int , int , int , int
Retorno: int
*/
int aux_motion_pawn(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color, int actual_lin, int actual_col, int pos,int control){

	int counter = 0;
	int ret = 0;

	//Peaças brancas
	if(color == 'w'){
		//Verificando se é possível andar duas casas inicialmente
		if(actual_lin == RANKS - 2 && xadrez->board[actual_lin - 2][actual_col].piece == empty && xadrez->board[actual_lin - 1][actual_col].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-2,actual_col,color,'P',control);
			if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin-2,actual_col,NO,NO,NO);
			ret = 0;
		}

		//Verificando se é possível andar uma casa a frente
		if( actual_lin-1 >= 0 && xadrez->board[actual_lin-1][actual_col].piece == empty){
			//Verificando se existe promoção ou não
			if(actual_lin-1 == 0){
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin-1,actual_col,NO,YES,NO);
				ret = 0;
			}
			else{
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin-1,actual_col,NO,NO,NO);
				ret = 0;
			}
		}

		//Verificando se é possível capturar uma peça nas diagonais
		if(actual_lin-1>=0 && actual_col-1>=0 && xadrez->board[actual_lin-1][actual_col-1].piece != empty && islower(xadrez->board[actual_lin-1][actual_col-1].piece) ){
			//Verificando se existe promoção ou não
			if(actual_lin-1 == 0){
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col-1,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin-1,actual_col-1,YES,YES,NO);
				if(ret == 1 && control == 1) return 1;
				ret = 0;
			}
			else{
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col-1,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin-1,actual_col-1,YES,NO,NO);
				if(ret == 1 && control == 1) return 1;
				ret = 0;
			}
		}
		if(actual_lin-1 >=0 && actual_col+1<FILES && xadrez->board[actual_lin-1][actual_col+1].piece != empty && islower(xadrez->board[actual_lin-1][actual_col+1].piece) ){
			//Verificando se existe promoção ou não
			if(actual_lin-1 == 0){
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col+1,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin-1,actual_col+1,YES,YES,NO);
				if(ret == 1 && control == 1) return 1;
				ret = 0;
			}
			else{
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col+1,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin-1,actual_col+1,YES,NO,NO);
				if(ret == 1 && control == 1) return 1;
				ret = 0;
			}
		}

		//Verificando se é possível realizar en passant
		if(actual_col-1>=0 && xadrez->board[actual_lin][actual_col-1].piece != empty && islower(xadrez->board[actual_lin][actual_col-1].piece)){
			if(actual_lin-1>=0 && xadrez->en_passant->rank ==actual_lin-1 && xadrez->en_passant->file ==actual_col-1){
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin-1,actual_col-1,YES,NO,YES);
			}
		}
		if(actual_col+1<FILES && xadrez->board[actual_lin][actual_col+1].piece != empty && islower(xadrez->board[actual_lin][actual_col+1].piece)){
			if(actual_lin-1>=0 && xadrez->en_passant->rank ==actual_lin-1 && xadrez->en_passant->file ==actual_col+1){
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin-1,actual_col+1,YES,NO,YES);
			}
		}
	}

	//Peças pretas
	else{
	//Verificando se é possível andar duas casas inicialmente
		if(actual_lin == 1 && xadrez->board[actual_lin+2][actual_col].piece == empty && xadrez->board[actual_lin+1][actual_col].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+2,actual_col,color,'P',control);
			if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin+2,actual_col,NO,NO,NO);
			ret = 0;
		}

		//Verificando se é possível andar uma casa a frente
		if( actual_lin+1 <RANKS && xadrez->board[actual_lin+1][actual_col].piece == empty){
			//Verificando se existe promoção ou não
			if(actual_lin+1 == RANKS-1){
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin+1,actual_col,NO,YES,NO);
				ret = 0;
			}
			else{
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin+1,actual_col,NO,NO,NO);
				ret = 0;
			}
		}

		//Verificando se é possível capturar uma peça nas diagonais
		if(actual_lin+1<RANKS && actual_col-1>=0 && xadrez->board[actual_lin+1][actual_col-1].piece != empty && !islower(xadrez->board[actual_lin+1][actual_col-1].piece) ){
			//Verificando se existe promoção ou não
			if(actual_lin+1 == RANKS-1){
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col-1,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin+1,actual_col-1,YES,YES,NO);
				if(ret == 1 && control == 1) return 1;
				ret = 0;
			}
			else{
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col-1,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin+1,actual_col-1,YES,NO,NO);
				if(ret == 1 && control == 1) return 1;
				ret = 0;
			}
		}
		if(actual_lin+1<RANKS && actual_col+1<FILES && xadrez->board[actual_lin+1][actual_col+1].piece != empty && !islower(xadrez->board[actual_lin+1][actual_col+1].piece) ){
			//Verificando se existe promoção ou não
			if(actual_lin+1 == RANKS-1){
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col+1,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin+1,actual_col+1,YES,YES,NO);
				if(ret == 1 && control == 1) return 1;
				ret = 0;
			}
			else{
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col+1,color,'P',control);
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin+1,actual_col+1,YES,NO,NO);
				if(ret == 1 && control == 1) return 1;
				ret = 0;
			}
		}

		//Verificando se é possível realizar en passant
		if(actual_col-1>=0 && xadrez->board[actual_lin][actual_col-1].piece != empty && !islower(xadrez->board[actual_lin][actual_col-1].piece)){
			if(actual_lin+1<RANKS && xadrez->en_passant->rank ==actual_lin+1 && xadrez->en_passant->file ==actual_col-1){
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin+1,actual_col-1,YES,NO,YES);
			}
		}
		if(actual_col+1<FILES && xadrez->board[actual_lin][actual_col+1].piece != empty && !islower(xadrez->board[actual_lin][actual_col+1].piece)){
			if(actual_lin+1<RANKS && xadrez->en_passant->rank ==actual_lin+1 && xadrez->en_passant->file ==actual_col+1){
				if(ret == 0 && control == 0) alloc_motion_pawn(motion,color,pos,++counter,actual_lin+1,actual_col+1,YES,NO,YES);
			}
		}	
	}

	return ret;
}

/*
Movimento do peão
Parâmetros: GEN_MOTION *, XADREZ *, MOTION *, char , int
Retorno: int
*/
int motion_pawn(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color,int control){

	int i;
	int amount;
	int ret = 0;

	if(color == 'w'){
		//Percorrendo todos os peões brancos
		amount = motion->white[PAWN].amount_piece;
		i = 0;
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento do cavalo
			ret = aux_motion_pawn(gen_motion,xadrez,motion,color,motion->white[PAWN].coor[i].actual_lin,motion->white[PAWN].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;
			i++;
		}
	}
	else{
		//Percorrendo todos os peões pretos
		amount = motion->black[PAWN].amount_piece;
		i = 0;
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento do cavalo
			ret = aux_motion_pawn(gen_motion,xadrez,motion,color,motion->black[PAWN].coor[i].actual_lin,motion->black[PAWN].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;
			i++;
		}
	}
	return ret;
}

//Alocação do movimento que uma peça possa realizar
void alloc_motion(MOTION *motion, char color, int lin, int col, int pos, int counter, int catch_piece, int piece){

	//Aloca-se o as coordenadas e se é possível realizar ou não: captura
	if(color == 'w'){
		motion->white[piece].coor[pos].lin = (int*) realloc(motion->white[piece].coor[pos].lin,sizeof(int)*counter);
		motion->white[piece].coor[pos].col = (int*) realloc(motion->white[piece].coor[pos].col,sizeof(int)*counter);
		motion->white[piece].coor[pos].catch_piece = (int*) realloc(motion->white[piece].coor[pos].catch_piece,sizeof(int)*counter);

		motion->white[piece].coor[pos].lin[counter-1] = lin;
		motion->white[piece].coor[pos].col[counter-1] = col;
		motion->white[piece].coor[pos].catch_piece[counter-1] = catch_piece;
		motion->white[piece].coor[pos].amount_motion++;
	}
	else{
		motion->black[piece].coor[pos].lin = (int*) realloc(motion->black[piece].coor[pos].lin,sizeof(int)*counter);
		motion->black[piece].coor[pos].col = (int*) realloc(motion->black[piece].coor[pos].col,sizeof(int)*counter);
		motion->black[piece].coor[pos].catch_piece = (int*) realloc(motion->black[piece].coor[pos].catch_piece,sizeof(int)*counter);

		motion->black[piece].coor[pos].lin[counter-1] = lin;
		motion->black[piece].coor[pos].col[counter-1] = col;
		motion->black[piece].coor[pos].catch_piece[counter-1] = catch_piece;
		motion->black[piece].coor[pos].amount_motion++;	
	}
}

/*
Cálculo dos movimentos - cavalo
Parâmetro: GEN_MOTION *, XADREZ *, MOTION *, char, int , int , int , int
Retorno: int
*/
int aux_motion_knight(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color, int actual_lin, int actual_col, int pos,int control){

	int counter = 0;
	int ret = 0;

/*Em todos os movimentos é verificado se: 
-As coordenadas estão dentro do tabuleiro
-O quadrado é vazio, caso não seja é verificado qual o tipo de peça que há nesse lugar por meio da função islower
-A função checkmate verifica se o movimento causa xeque, caso cause ele não é alocado
*/

	//Primeiro movimento  - Verifica se é possível realizar o 'L' e se o campo está vazio ou se há uma peça
	if(actual_lin-2 >=0 && actual_col+1<FILES){
		if(xadrez->board[actual_lin-2][actual_col+1].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-2,actual_col+1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-2,actual_col+1,pos,++counter,NO,KNIGHT);
			ret = 0;
		}
		else if(color == 'w' && islower(xadrez->board[actual_lin-2][actual_col+1].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-2,actual_col+1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-2,actual_col+1,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
		else if(color == 'b' && !islower(xadrez->board[actual_lin-2][actual_col+1].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-2,actual_col+1,color,'N',control);
			if(ret == 0 && control == 0)alloc_motion(motion,color,actual_lin-2,actual_col+1,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
	}

	//Segundo movimento  - Verifica se é possível realizar o 'L' e se o campo está vazio ou se há uma peça
	if(actual_lin-2>=0 && actual_col-1>=0){
		if(xadrez->board[actual_lin-2][actual_col-1].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-2,actual_col-1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-2,actual_col-1,pos,++counter,NO,KNIGHT);
			ret = 0;
		}
		else if(color == 'w' && islower(xadrez->board[actual_lin-2][actual_col-1].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-2,actual_col-1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-2,actual_col-1,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}	
		else if(color == 'b' && !islower(xadrez->board[actual_lin-2][actual_col-1].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-2,actual_col-1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-2,actual_col-1,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
	}

	//Terceiro movimento  - Verifica se é possível realizar o 'L' e se o campo está vazio ou se há uma peça
	if(actual_lin+2<FILES && actual_col+1<FILES){
		if(xadrez->board[actual_lin+2][actual_col+1].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+2,actual_col+1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+2,actual_col+1,pos,++counter,NO,KNIGHT);
			ret = 0;
		}
		else if(color == 'w' && islower(xadrez->board[actual_lin+2][actual_col+1].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+2,actual_col+1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+2,actual_col+1,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
		else if(color == 'b' && !islower(xadrez->board[actual_lin+2][actual_col+1].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+2,actual_col+1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+2,actual_col+1,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
	}

	//Quarto movimento  - Verifica se é possível realizar o 'L' e se o campo está vazio ou se há uma peça
	if(actual_lin+2<FILES && actual_col-1>=0){
		if(xadrez->board[actual_lin+2][actual_col-1].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+2,actual_col-1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+2,actual_col-1,pos,++counter,NO,KNIGHT);
			ret = 0;
		}
		else if(color == 'w' && islower(xadrez->board[actual_lin+2][actual_col-1].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+2,actual_col-1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+2,actual_col-1,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
		else if(color == 'b' && !islower(xadrez->board[actual_lin+2][actual_col-1].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+2,actual_col-1,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+2,actual_col-1,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
	}

	//Quinto movimento  - Verifica se é possível realizar o 'L' e se o campo está vazio ou se há uma peça
	if(actual_lin-1>=0 && actual_col+2<FILES){
		if(xadrez->board[actual_lin-1][actual_col+2].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col+2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col+2,pos,++counter,NO,KNIGHT);
			ret = 0;
		}
		else if(color == 'w' && islower(xadrez->board[actual_lin-1][actual_col+2].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col+2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col+2,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
		else if(color == 'b' && !islower(xadrez->board[actual_lin-1][actual_col+2].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col+2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col+2,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
	}

	//Sexto movimento  - Verifica se é possível realizar o 'L' e se o campo está vazio ou se há uma peça
	if(actual_lin-1>=0 && actual_col-2>=0){
		if(xadrez->board[actual_lin-1][actual_col-2].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col-2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col-2,pos,++counter,NO,KNIGHT);
			ret = 0;
		}
		else if(color == 'w' && islower(xadrez->board[actual_lin-1][actual_col-2].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col-2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col-2,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
		else if(color == 'b' && !islower(xadrez->board[actual_lin-1][actual_col-2].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col-2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col-2,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
	}

	//Sétimo movimento  - Verifica se é possível realizar o 'L' e se o campo está vazio ou se há uma peça
	if(actual_lin+1<RANKS && actual_col+2<FILES){
		if(xadrez->board[actual_lin+1][actual_col+2].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col+2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col+2,pos,++counter,NO,KNIGHT);
			ret = 0;
		}
		else if(color == 'w' && islower(xadrez->board[actual_lin+1][actual_col+2].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col+2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col+2,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
		else if(color == 'b' && !islower(xadrez->board[actual_lin+1][actual_col+2].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col+2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col+2,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
	}

	//Oitavo movimento  - Verifica se é possível realizar o 'L' e se o campo está vazio ou se há uma peça
	if(actual_lin+1<RANKS && actual_col-2>=0){
		if(xadrez->board[actual_lin+1][actual_col-2].piece == empty){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col-2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col-2,pos,++counter,NO,KNIGHT);
			ret = 0;
		}
		else if(color == 'w' && islower(xadrez->board[actual_lin+1][actual_col-2].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col-2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col-2,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
		else if(color == 'b' && !islower(xadrez->board[actual_lin+1][actual_col-2].piece)){
			ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col-2,color,'N',control);
			if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col-2,pos,++counter,YES,KNIGHT);
			if(ret == 1 && control == 1) return 1;
			ret = 0;
		}
	}

	return ret;
}

/*
Movimento do cavalo
Parâmetros: GEN_MOTION *, XADREZ *, MOTION *, char , int
Retorno: int
*/
int motion_knight(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color,int control){

	int i;
	int amount;
	int ret = 0;

	if(color == 'w'){
		amount = motion->white[KNIGHT].amount_piece;
		i = 0;
		//Percorrendo todos os cavalos brancos
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento do cavalo
			ret = aux_motion_knight(gen_motion,xadrez,motion,color,motion->white[KNIGHT].coor[i].actual_lin,motion->white[KNIGHT].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;
			i++;
		}
	}
	else{
		amount = motion->black[KNIGHT].amount_piece;
		i = 0;
		//Percorrendo todos os cavalos pretos
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento do cavalo
			ret = aux_motion_knight(gen_motion,xadrez,motion,color,motion->black[KNIGHT].coor[i].actual_lin,motion->black[KNIGHT].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;
			i++;
		}
	}
	return ret;
}

/*
Cálculo dos movimentos - bispo
Parâmetro: GEN_MOTION *, XADREZ *, MOTION *, char, int , int , int , int
Retorno: int
*/
int aux_motion_bishop(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color, int actual_lin, int actual_col, int pos,int control){

	int counter = 0;
	int aux = 1;
	int ret = 0;

/*Em todos os movimentos é verificado se: 
-As coordenadas estão dentro do tabuleiro
-O quadrado é vazio, caso não seja é verificado qual o tipo de peça que há nesse lugar por meio da função islower
-A função checkmate verifica se o movimento causa xeque, caso cause ele não é alocado
*/
	
	//Primeio movimento - Noroeste(Diagonal)
	while(actual_lin-aux>=0 && actual_col-aux>=0 && xadrez->board[actual_lin-aux][actual_col-aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col-aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col-aux,pos,++counter,NO,BISHOP);
		aux++;
		ret = 0;
	}
	if(actual_lin-aux>=0 && actual_col-aux>=0 && color == 'w' && islower(xadrez->board[actual_lin-aux][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col-aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col-aux,pos,++counter,YES,BISHOP);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin-aux>=0 && actual_col-aux>=0 && color == 'b' && !islower(xadrez->board[actual_lin-aux][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col-aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col-aux,pos,++counter,YES,BISHOP);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Segundo movimento - Nordeste(Diagonal)
	aux = 1;
	while(actual_lin-aux>=0 && actual_col+aux<FILES && xadrez->board[actual_lin-aux][actual_col+aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col+aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col+aux,pos,++counter,NO,BISHOP);
		aux++;
		ret = 0;
	}
	if(actual_lin-aux>=0 && actual_col+aux<FILES && color == 'w' && islower(xadrez->board[actual_lin-aux][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col+aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col+aux,pos,++counter,YES,BISHOP);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin-aux>=0 && actual_col+aux<FILES && color == 'b' && !islower(xadrez->board[actual_lin-aux][actual_col+aux].piece)){
		checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col+aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col+aux,pos,++counter,YES,BISHOP);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Terceiro movimento - Sudoeste(Diagonal)
	aux = 1;
	while(actual_lin+aux<RANKS && actual_col-aux>=0 && xadrez->board[actual_lin+aux][actual_col-aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col-aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col-aux,pos,++counter,NO,BISHOP);
		aux++;
		ret = 0;
	}
	if(actual_lin+aux<RANKS && actual_col-aux>=0 && color == 'w' && islower(xadrez->board[actual_lin+aux][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col-aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col-aux,pos,++counter,YES,BISHOP);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin+aux<RANKS && actual_col-aux>=0 && color == 'b' && !islower(xadrez->board[actual_lin+aux][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col-aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col-aux,pos,++counter,YES,BISHOP);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Quarto movimento - Sudeste(Diagonal)
	aux = 1;
	while(actual_lin+aux<RANKS && actual_col+aux<FILES && xadrez->board[actual_lin+aux][actual_col+aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col+aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col+aux,pos,++counter,NO,BISHOP);
		aux++;
		ret = 0;
	}
	if(actual_lin+aux<RANKS && actual_col+aux<FILES && color == 'w' && islower(xadrez->board[actual_lin+aux][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col+aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col+aux,pos,++counter,YES,BISHOP);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin+aux<RANKS && actual_col+aux<FILES && color == 'b' && !islower(xadrez->board[actual_lin+aux][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col+aux,color,'B',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col+aux,pos,++counter,YES,BISHOP);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	return ret;
}

/*
Movimento do bispo
Parâmetros: GEN_MOTION *, XADREZ *, MOTION *, char , int
Retorno: int
*/
int motion_bishop(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color,int control){

	int i;
	int amount;
	int ret = 0;

	if(color == 'w'){
		amount = motion->white[BISHOP].amount_piece;
		i = 0;
		//Percorrendo todos os bispos brancos
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento do bispo
			ret = aux_motion_bishop(gen_motion,xadrez,motion,color,motion->white[BISHOP].coor[i].actual_lin,motion->white[BISHOP].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;
			i++;
		}
	}
	else{
		amount = motion->black[BISHOP].amount_piece;
		i = 0;
		//Percorrendo todos os bispos pretos
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento do bispo
			ret = aux_motion_bishop(gen_motion,xadrez,motion,color,motion->black[BISHOP].coor[i].actual_lin,motion->black[BISHOP].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;
			i++;
		}
	}
	return ret;
}

/*
Cálculo dos movimentos - torre
Parâmetro: GEN_MOTION *, XADREZ *, MOTION *, char, int , int , int , int
Retorno: int
*/
int aux_motion_rook(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color, int actual_lin, int actual_col, int pos,int control){

	int counter = 0;
	int aux = 1;
	int i,j;
	int ret = 0;

/*Em todos os movimentos é verificado se: 
-As coordenadas estão dentro do tabuleiro
-O quadrado é vazio, caso não seja é verificado qual o tipo de peça que há nesse lugar por meio da função islower
-A função checkmate verifica se o movimento causa xeque, caso cause ele não é alocado
*/
	//Primeio movimento - Horizontal para cima
	while(actual_lin-aux>=0 && xadrez->board[actual_lin-aux][actual_col].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col,pos,++counter,NO,ROOK);
		aux++;
		ret = 0;
	}
	if(actual_lin-aux>=0 && color == 'w' && islower(xadrez->board[actual_lin-aux][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col,pos,++counter,YES,ROOK);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin-aux>=0 && color == 'b' && !islower(xadrez->board[actual_lin-aux][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col,pos,++counter,YES,ROOK);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Segundo movimento - Horizontal para baixo
	aux = 1;
	while(actual_lin+aux<RANKS && xadrez->board[actual_lin+aux][actual_col].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col,pos,++counter,NO,ROOK);
		aux++;
		ret = 0;
	}
	if(actual_lin+aux<RANKS && color == 'w' && islower(xadrez->board[actual_lin+aux][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col,pos,++counter,YES,ROOK);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin+aux<RANKS && color == 'b' && !islower(xadrez->board[actual_lin+aux][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col,pos,++counter,YES,ROOK);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Terceiro movimento - Vertical para a esquerda
	aux = 1;
	while(actual_col-aux>=0 && xadrez->board[actual_lin][actual_col-aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col-aux,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-aux,pos,++counter,NO,ROOK);
		aux++;
		ret = 0;
	}
	if(actual_col-aux>=0 && color == 'w' && islower(xadrez->board[actual_lin][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col-aux,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-aux,pos,++counter,YES,ROOK);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_col-aux>=0 && color == 'b' && !islower(xadrez->board[actual_lin][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col-aux,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-aux,pos,++counter,YES,ROOK);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Quarto movimento - Vertical para a direita
	aux = 1;
	while(actual_col+aux<FILES && xadrez->board[actual_lin][actual_col+aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col+aux,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+aux,pos,++counter,NO,ROOK);
		aux++;
		ret = 0;
	}
	if(actual_col+aux<FILES && color == 'w' && islower(xadrez->board[actual_lin][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col+aux,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+aux,pos,++counter,YES,ROOK);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_col+aux<FILES && color == 'b' && !islower(xadrez->board[actual_lin][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col+aux,color,'R',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+aux,pos,++counter,YES,ROOK);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Verificação de roque para as brancas
	if(color == 'w'){
		//Verificando se as peças estão nas posições corretas para realizar o roque - Lado do rei
		if(xadrez->roque->roqueWhite[0] == 'K' && actual_lin == RANKS-1 && actual_col == FILES-1 && xadrez->board[RANKS-1][4].piece == 'K'){
			i = 5;
			j = 0;
			//Verificando se a posição entre eles está vazia
			while(xadrez->board[RANKS-1][i].piece == empty){
				j++;
				i++;
			}
			if(j == 2){
				if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-2,pos,++counter,NO,ROOK);				
			}
		}
		//Verificando se as peças estão nas posições corretas para realizar o roque - Lado da rainha
		if(xadrez->roque->roqueWhite[1] == 'Q' && actual_lin == RANKS-1 && actual_col == 0 && xadrez->board[RANKS-1][4].piece == 'K'){
			i = 1;
			j = 0;
			//Verificando se a posição entre eles está vazia
			while(xadrez->board[RANKS-1][i].piece == empty){
				j++;
				i++;
			}
			if(j == 3){
				if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+2,pos,++counter,NO,ROOK);
			}
		}
	}
	//Verificação de roque para as pretas
	else{
		if(xadrez->roque->roqueBlack[0] == 'k' && actual_lin == 0 && actual_col == FILES-1 && xadrez->board[0][4].piece == 'k'){
			i = 5;
			j = 0;
			while(xadrez->board[0][i].piece == empty){
				j++;
				i++;
			}
			if(j == 2){
				if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-2,pos,++counter,NO,ROOK);
			}
		}
		if(xadrez->roque->roqueBlack[1] == 'q' && actual_lin == 0 && actual_col == 0 && xadrez->board[0][4].piece == 'k'){
			i = 1;
			j = 0;
			while(xadrez->board[0][i].piece == empty){
				j++;
				i++;
			}
			if(j == 3){
				if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+2,pos,++counter,NO,ROOK);	
			}
		}
	}
	return ret;
}

/*
Movimento da torre
Parâmetros: GEN_MOTION *, XADREZ *, MOTION *, char , int
Retorno: int
*/
int motion_rook(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color,int control){

	int i;
	int amount;
	int ret = 0;

	if(color == 'w'){
		amount = motion->white[ROOK].amount_piece;
		i = 0;
		//Percorrendo todas as torres brancas
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento da torre
			ret = aux_motion_rook(gen_motion,xadrez,motion,color,motion->white[ROOK].coor[i].actual_lin,motion->white[ROOK].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;
			i++;
		}
	}
	else{
		amount = motion->black[ROOK].amount_piece;
		i = 0;
		//Percorrendo todas as torres pretas
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento da torre
			ret = aux_motion_rook(gen_motion,xadrez,motion,color,motion->black[ROOK].coor[i].actual_lin,motion->black[ROOK].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;
			i++;
		}
	}
	return ret;
}

/*
Cálculo dos movimentos - rainha
Parâmetro: GEN_MOTION *, XADREZ *, MOTION *, char, int , int , int , int
Retorno: int
*/
int aux_motion_queen(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color, int actual_lin, int actual_col, int pos,int control){

	int counter = 0;
	int aux = 1;
	int ret = 0;

/*Em todos os movimentos é verificado se: 
-As coordenadas estão dentro do tabuleiro
-O quadrado é vazio, caso não seja é verificado qual o tipo de peça que há nesse lugar por meio da função islower
-A função checkmate verifica se o movimento causa xeque, caso cause ele não é alocado
*/
	
	//Primeio movimento - Horizontal para baixo
	while(actual_lin-aux>=0 && xadrez->board[actual_lin-aux][actual_col].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col,pos,++counter,NO,QUEEN);
		aux++;
		ret = 0;
	}
	if(actual_lin-aux>=0 && color == 'w' && islower(xadrez->board[actual_lin-aux][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin-aux>=0 && color == 'b' && !islower(xadrez->board[actual_lin-aux][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Segundo movimento - Horizontal para cima
	aux = 1;
	while(actual_lin+aux<RANKS && xadrez->board[actual_lin+aux][actual_col].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col,pos,++counter,NO,QUEEN);
		aux++;
		ret = 0;
	}
	if(actual_lin+aux<RANKS && color == 'w' && islower(xadrez->board[actual_lin+aux][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin+aux<RANKS && color == 'b' && !islower(xadrez->board[actual_lin+aux][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Terceiro movimento - Vertical para a esquerda
	aux = 1;
	while(actual_col-aux>=0 && xadrez->board[actual_lin][actual_col-aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col-aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-aux,pos,++counter,NO,QUEEN);
		aux++;
		ret = 0;
	}
	if(actual_col-aux>=0 && color == 'w' && islower(xadrez->board[actual_lin][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col-aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_col-aux>=0 && color == 'b' && !islower(xadrez->board[actual_lin][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col-aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Quarto movimento - Vertical para a direita
	aux = 1;
	while(actual_col+aux<FILES && xadrez->board[actual_lin][actual_col+aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col+aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+aux,pos,++counter,NO,QUEEN);
		aux++;
		ret = 0;
	}
	if(actual_col+aux<FILES && color == 'w' && islower(xadrez->board[actual_lin][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col+aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_col+aux<FILES && color == 'b' && !islower(xadrez->board[actual_lin][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col+aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Quinto movimento - Noroeste(Diagonal)
	aux = 1;
	while(actual_lin-aux>=0 && actual_col-aux>=0 && xadrez->board[actual_lin-aux][actual_col-aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col-aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col-aux,pos,++counter,NO,QUEEN);
		aux++;
		ret = 0;
	}
	if(actual_lin-aux>=0 && actual_col-aux>=0 && color == 'w' && islower(xadrez->board[actual_lin-aux][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col-aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col-aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin-aux>=0 && actual_col-aux>=0 && color == 'b' && !islower(xadrez->board[actual_lin-aux][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col-aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col-aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Sexto movimento - Nordeste(Diagonal)
	aux = 1;
	while(actual_lin-aux>=0 && actual_col+aux<FILES && xadrez->board[actual_lin-aux][actual_col+aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col+aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col+aux,pos,++counter,NO,QUEEN);
		aux++;
		ret = 0;
	}
	if(actual_lin-aux>=0 && actual_col+aux<FILES && color == 'w' && islower(xadrez->board[actual_lin-aux][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col+aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col+aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin-aux>=0 && actual_col+aux<FILES && color == 'b' && !islower(xadrez->board[actual_lin-aux][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-aux,actual_col+aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-aux,actual_col+aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Sétimo movimento - Sudoeste(Diagonal)
	aux = 1;
	while(actual_lin+aux<RANKS && actual_col-aux>=0 && xadrez->board[actual_lin+aux][actual_col-aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col-aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col-aux,pos,++counter,NO,QUEEN);
		aux++;
		ret = 0;
	}
	if(actual_lin+aux<RANKS && actual_col-aux>=0 && color == 'w' && islower(xadrez->board[actual_lin+aux][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col-aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col-aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin+aux<RANKS && actual_col-aux>=0 && color == 'b' && !islower(xadrez->board[actual_lin+aux][actual_col-aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col-aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col-aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Oitavo movimento - Sudeste(Diagonal)
	aux = 1;
	while(actual_lin+aux<RANKS && actual_col+aux<FILES && xadrez->board[actual_lin+aux][actual_col+aux].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col+aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col+aux,pos,++counter,NO,QUEEN);
		aux++;
		ret = 0;
	}
	if(actual_lin+aux<RANKS && actual_col+aux<FILES && color == 'w' && islower(xadrez->board[actual_lin+aux][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col+aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col+aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin+aux<RANKS && actual_col+aux<FILES && color == 'b' && !islower(xadrez->board[actual_lin+aux][actual_col+aux].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+aux,actual_col+aux,color,'Q',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+aux,actual_col+aux,pos,++counter,YES,QUEEN);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	return ret;
}

/*
Movimento da rainha
Parâmetros: GEN_MOTION *, XADREZ *, MOTION *, char , int
Retorno: int
*/
int motion_queen(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color,int control){

	int i;
	int amount;
	int ret = 0;

	if(color == 'w'){
		amount = motion->white[QUEEN].amount_piece;
		i = 0;
		//Percorrendo todas as rainhas brancas
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento da rainha
			ret = aux_motion_queen(gen_motion,xadrez,motion,color,motion->white[QUEEN].coor[i].actual_lin,motion->white[QUEEN].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;		
			i++;
		}
	}
	else{
		amount = motion->black[QUEEN].amount_piece;
		i = 0;
		//Percorrendo todas as rainhas pretas
		while(amount-- > 0){
			//Função auxiliar que calcula o movimento da rainha
			ret = aux_motion_queen(gen_motion,xadrez,motion,color,motion->black[QUEEN].coor[i].actual_lin,motion->black[QUEEN].coor[i].actual_col,i,control);
			//Ret == 1 indica que o movimento causa xeque
			if(ret == 1) return ret;
			i++;
		}
	}
	return ret;
}

/*
Cálculo dos movimentos - rei
Parâmetro: GEN_MOTION *, XADREZ *, MOTION *, char, int , int , int , int
Retorno: int
*/
int aux_motion_king(GEN_MOTION *gen_motion,XADREZ *xadrez, MOTION *motion, char color, int actual_lin, int actual_col, int pos,int control){

	int counter = 0;
	int i,j;
	int ret = 0;

/*Em todos os movimentos é verificado se: 
-As coordenadas estão dentro do tabuleiro
-O quadrado é vazio, caso não seja é verificado qual o tipo de peça que há nesse lugar por meio da função islower
-A função checkmate verifica se o movimento causa xeque, caso cause ele não é alocado
*/

	//Primeio movimento - Para cima
	if(actual_lin-1>=0 && xadrez->board[actual_lin-1][actual_col].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col,pos,++counter,NO,KING);
		ret = 0;
	}
	else if(actual_lin-1>=0 && color == 'w' && islower(xadrez->board[actual_lin-1][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin-1>=0 && color == 'b' && !islower(xadrez->board[actual_lin-1][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Segundo movimento - Para baixo
	if(actual_lin+1<RANKS && xadrez->board[actual_lin+1][actual_col].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col,pos,++counter,NO,KING);
		ret = 0;
	}
	else if(actual_lin+1<RANKS && color == 'w' && islower(xadrez->board[actual_lin+1][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin+1<RANKS && color == 'b' && !islower(xadrez->board[actual_lin+1][actual_col].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Terceiro movimento - Para esquerda
	if(actual_col-1>=0 && xadrez->board[actual_lin][actual_col-1].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col-1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-1,pos,++counter,NO,KING);
		ret = 0;
	}
	else if(actual_col-1>=0 && color == 'w' && islower(xadrez->board[actual_lin][actual_col-1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col-1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_col-1>=0 && color == 'b' && !islower(xadrez->board[actual_lin][actual_col-1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col-1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col-1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Quarto movimento - Para direita
	if(actual_col+1<FILES && xadrez->board[actual_lin][actual_col+1].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col+1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+1,pos,++counter,NO,KING);
		ret = 0;
	}
	else if(actual_col+1<FILES && color == 'w' && islower(xadrez->board[actual_lin][actual_col+1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col+1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_col+1<FILES && color == 'b' && !islower(xadrez->board[actual_lin][actual_col+1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin,actual_col+1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin,actual_col+1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Quinto movimento - Noroeste
	if(actual_lin-1>=0 && actual_col-1>=0 && xadrez->board[actual_lin-1][actual_col-1].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col-1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col-1,pos,++counter,NO,KING);
		ret = 0;
	}
	else if(actual_lin-1>=0 && actual_col-1>=0 && color == 'w' && islower(xadrez->board[actual_lin-1][actual_col-1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col-1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col-1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin-1>=0 && actual_col-1>=0 && color == 'b' && !islower(xadrez->board[actual_lin-1][actual_col-1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col-1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col-1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Sexto movimento - Nordeste
	if(actual_lin-1>=0 && actual_col+1<FILES && xadrez->board[actual_lin-1][actual_col+1].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col+1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col+1,pos,++counter,NO,KING);
		ret = 0;
	}
	else if(actual_lin-1>=0 && actual_col+1<FILES && color == 'w' && islower(xadrez->board[actual_lin-1][actual_col+1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col+1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col+1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin-1>=0 && actual_col+1<FILES && color == 'b' && !islower(xadrez->board[actual_lin-1][actual_col+1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin-1,actual_col+1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin-1,actual_col+1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Sétimo movimento - Sudoeste
	if(actual_lin+1<RANKS && actual_col-1>=0 && xadrez->board[actual_lin+1][actual_col-1].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col-1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col-1,pos,++counter,NO,KING);
		ret = 0;
	}
	else if(actual_lin+1<RANKS && actual_col-1>=0 && color == 'w' && islower(xadrez->board[actual_lin+1][actual_col-1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col-1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col-1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin+1<RANKS && actual_col-1>=0 && color == 'b' && !islower(xadrez->board[actual_lin+1][actual_col-1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col-1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col-1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Oitavo movimento - Sudeste
	if(actual_lin+1<RANKS && actual_col+1<FILES && xadrez->board[actual_lin+1][actual_col+1].piece == empty){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col+1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col+1,pos,++counter,NO,KING);
		ret = 0;
	}
	else if(actual_lin+1<RANKS && actual_col+1<FILES && color == 'w' && islower(xadrez->board[actual_lin+1][actual_col+1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col+1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col+1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}
	else if(actual_lin+1<RANKS && actual_col+1<FILES && color == 'b' && !islower(xadrez->board[actual_lin+1][actual_col+1].piece)){
		ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,actual_lin+1,actual_col+1,color,'K',control);
		if(ret == 0 && control == 0) alloc_motion(motion,color,actual_lin+1,actual_col+1,pos,++counter,YES,KING);
		if(ret == 1 && control == 1) return 1;
		ret = 0;
	}

	//Verificação de roque para o lado do rei
	if(color == 'w'){
		//Verificando se as peças estã em suas posições corretas
		if(xadrez->roque->roqueWhite[0] == 'K' && xadrez->board[RANKS-1][RANKS-1].piece == 'R'  && xadrez->board[RANKS-1][4].piece == 'K'){
			i = 5;
			j = 0;
			//Verificando se os espaços estão vazios entre a torre e o rei
			while(xadrez->board[RANKS-1][i].piece == empty){
				//Verificando se o rei não passa por casas atacadas
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,RANKS-1,i,color,'K',control);
				if(ret == 1 && control == 0) return 1;
				ret = 0;
				j++;
				i++;
			}
			if(j == 2){
				if(ret == 0 && control == 0) alloc_motion(motion,color,RANKS-1,actual_col+2,pos,++counter,NO,KING);
			}
		}
		//Verificação de roque para o lado da rainha
		if(xadrez->roque->roqueWhite[1] == 'Q' && xadrez->board[RANKS-1][0].piece == 'R' && xadrez->board[RANKS-1][4].piece == 'K'){
			i = 1;
			j = 0;
			//Verificando se os espaços estão vazios entre a torre e o rei
			while(xadrez->board[RANKS-1][i].piece == empty){
				//Verificando se o rei não passa por casas atacadas
				if(i != 1){
					ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,RANKS-1,i,color,'K',control);
				}
				if(ret == 1 && control == 0) return 1;
				ret = 0;
				j++;
				i++;
			}
			if(j == 3){
				if(ret == 0 && control == 0) alloc_motion(motion,color,RANKS-1,actual_col-2,pos,++counter,NO,KING);
			}
		}
	}
	//Verificação de roque para o lado da rainha
	else{
		//Verificando se as peças estã em suas posições corretas
		if(xadrez->roque->roqueBlack[0] == 'k' && xadrez->board[0][FILES-1].piece == 'r'  && xadrez->board[0][4].piece == 'k'){
			i = 5;
			j = 0;
			//Verificando se os espaços estão vazios entre a torre e o rei
			while(xadrez->board[0][i].piece == empty){
				//Verificando se o rei não passa por casas atacadas
				ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,0,i,color,'K',control);
				if(ret == 1 && control == 0) return 1;
				ret = 0;
				j++;
				i++;
			}
			if(j == 2){
				if(ret == 0 && control == 0) alloc_motion(motion,color,0,actual_col+2,pos,++counter,NO,KING);
			}
		}
		//Verificando se as peças estã em suas posições corretas
		if(xadrez->roque->roqueBlack[1] == 'q' && xadrez->board[0][0].piece == 'r'  && xadrez->board[0][4].piece == 'k'){
			i = 1;
			j = 0;
			//Verificando se os espaços estão vazios entre a torre e o rei
			while(xadrez->board[0][i].piece == empty){
				//Verificando se o rei não passa por casas atacadas
				if(i != 1){
					ret = checkmate(gen_motion,xadrez,motion,actual_lin,actual_col,0,i,color,'K',control);
				}
				if(ret == 1 && control == 0) return 1;
				ret = 0;
				j++;
				i++;
			}
			if(j == 3){
				if(ret == 0 && control == 0) alloc_motion(motion,color,0,actual_col-2,pos,++counter,NO,KING);	
			}
		}
	}
	return ret;
}

/*
Movimento do rei
Parâmetros: GEN_MOTION *, XADREZ *, MOTION *, char , int
Retorno: int
*/
int motion_king(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color,int control){

	int ret = 0;
	int amount;
	int i;

	if(color == 'w'){
		amount = motion->white[KING].amount_piece;
		i = 0;
			while(amount-- > 0){
				//Função auxiliar que calcula o movimento do rei
				ret = aux_motion_king(gen_motion, xadrez,motion,color,motion->white[KING].coor[i].actual_lin,motion->white[KING].coor[i].actual_col,i,control);
				//Ret == 1 indica que o movimento executado pelo rei causa um xeque nele
				if(ret == 1) return ret;
				i++;
			}
	}
	else{
		amount = motion->black[KING].amount_piece;
		i = 0;
			while(amount-- > 0){
				//Função auxiliar que calcula o movimento do rei
				ret = aux_motion_king(gen_motion, xadrez,motion,color,motion->black[KING].coor[i].actual_lin,motion->black[KING].coor[i].actual_col,i,control);
				//Ret == 1 indica que o movimento executado pelo rei causa um xeque nele
				if(ret == 1) return ret;
				i++;
			}
	}
	return ret;
}

/*
Ordenação das peças
Parâmetros: COOR*, int
Retorno: nenhum
*/
void sort_piece(COOR *coor, int n){

	int i,j;
	COOR aux;

	//Bubble
	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if(coor[j].actual_col > coor[j+1].actual_col){
				memcpy(&aux, &(coor[j]), sizeof(COOR) );
				memcpy(&(coor[j]), &(coor[j+1]), sizeof(COOR) );
				memcpy(&(coor[j+1]), &aux ,sizeof(COOR) );
			}
			else if(coor[j].actual_col == coor[j+1].actual_col){
				if(coor[j].actual_lin < coor[j+1].actual_lin){
					memcpy(&aux, &(coor[j]), sizeof(COOR) );
					memcpy(&(coor[j]), &(coor[j+1]), sizeof(COOR) );
					memcpy(&(coor[j+1]), &aux ,sizeof(COOR) );
				}
			}
		}
	}
}

/*
Ordenação dos movimentos de cada peça
Parâmetros: COOR*, int
Retorno: nenhum
*/
void sort_piece_motion(COOR *coor,int n){

	int i,j;
	int swap;

	//Bubble
	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if(coor->col[j] > coor->col[j+1]){
				swap = coor->col[j];
				coor->col[j] = coor->col[j+1];
				coor->col[j+1] = swap;

				swap = coor->lin[j];
				coor->lin[j] = coor->lin[j+1];
				coor->lin[j+1] = swap;

				swap = coor->catch_piece[j];
				coor->catch_piece[j] = coor->catch_piece[j+1];
				coor->catch_piece[j+1] = swap;

				swap = coor->equal[j];
				coor->equal[j] = coor->equal[j+1];
				coor->equal[j+1] = swap;
				
				//Somente o peão possui o campo promoção e en passant alocados, por isso deve-se checar se eles devem ser trocados ou não
				if(coor->promotion != NULL){
					swap = coor->promotion[j];
					coor->promotion[j] = coor->promotion[j+1];
					coor->promotion[j+1] = swap;

					swap = coor->en_passant[j];
					coor->en_passant[j] = coor->en_passant[j+1];
					coor->en_passant[j+1] = swap;
				}
			}
			else if(coor->col[j] == coor->col[j+1]){
				if(coor->lin[j] < coor->lin[j+1]){
					swap = coor->col[j];
					coor->col[j] = coor->col[j+1];
					coor->col[j+1] = swap;

					swap = coor->lin[j];
					coor->lin[j] = coor->lin[j+1];
					coor->lin[j+1] = swap;

					swap = coor->catch_piece[j];
					coor->catch_piece[j] = coor->catch_piece[j+1];
					coor->catch_piece[j+1] = swap;

					swap = coor->equal[j];
					coor->equal[j] = coor->equal[j+1];
					coor->equal[j+1] = swap;
					//Somente o peão possui o campo promoção e en passant alocados, por isso deve-se checar se eles devem ser trocados ou não
					if(coor->promotion != NULL){
						swap = coor->promotion[j];
						coor->promotion[j] = coor->promotion[j+1];
						coor->promotion[j+1] = swap;

						swap = coor->en_passant[j];
						coor->en_passant[j] = coor->en_passant[j+1];
						coor->en_passant[j+1] = swap;
					}
				}
				//Caso haja dois movimentos iguais então um deles recebe o valor máximo para ser levado ao final e então poder ser descartado
				else if(coor->lin[j] == coor->lin[j+1]){
					coor->lin[j+1] = INT_MIN;
					coor->col[j+1] = INT_MAX;
					coor->amount_motion--;
					i = 1;
					j = -1;
				}
			}
		}
	}
}

/*
Ordenação dos movimentos
Parâmetros: INFO_MOTION *
Retorno: nenhum
*/
void sort_motion(INFO_MOTION *info_motion){

	int i,j;
	int amount;

	//Ordenando as peças iguais
	for(i=0;i<AMOUNT_PIECE;i++){
		//Ordenando as peças do mesmo tipo
		sort_piece(info_motion[i].coor,info_motion[i].amount_piece);
		amount = info_motion[i].amount_piece;
		j = 0;
		while(amount>0){
			//Ordenando os movimentos de cada peça
			sort_piece_motion(&(info_motion[i].coor[j]),info_motion[i].coor[j].amount_motion);
			amount--;
			j++;
		}
	}
}

/*
Impressão dos movimentos das peças
Parâmetros: INFO_MOTION *
Retorno: nenhum
*/
void print_motion(INFO_MOTION *info_motion){

	int i,j,k;
	int aux;
	int amountPiece, amountMotion;
	//String que será utilizada para imprimir cada peça
	char typePiece[7] = "PNBRQK";

	//Impressão do peão - A impressão do peão é realizada a parte por conta de ele possuir os campos: en passant e promoção
	//Verificando quantos peões existem
	amountPiece = info_motion[PAWN].amount_piece;
	j = 0;
	while(amountPiece-- > 0){
		//Verificando a quantidade de movimentos de cada peão
		amountMotion = info_motion[PAWN].coor[j].amount_motion;
		k = 0;
		while(amountMotion-- > 0){
			//Verificando se existe captura mas não existe promoção
			if(info_motion[PAWN].coor[j].catch_piece[k] == 1 && info_motion[PAWN].coor[j].promotion[k] == 0){
				printf("%cx%c%d",info_motion[PAWN].coor[j].actual_col+97,info_motion[PAWN].coor[j].col[k]+97,RANKS-info_motion[PAWN].coor[j].lin[k]);
				//Verificando por el passant
				if(info_motion[PAWN].coor[j].en_passant[k] == 1){
					printf("e.p.\n");
				}
				else{
					printf("\n");
				}
			}
			//Verificando se existe captura e promoção
			if(info_motion[PAWN].coor[j].catch_piece[k] == 1 && info_motion[PAWN].coor[j].promotion[k] == 1){
				aux = 0;
				while(aux++ < 4){
					printf("%cx%c%d",info_motion[PAWN].coor[j].actual_col+97,info_motion[PAWN].coor[j].col[k]+97,RANKS-info_motion[PAWN].coor[j].lin[k]);
					printf("%c\n",typePiece[aux]);	
				}
			}
			//Verificando se não existe captura mas existe promoção
			if(info_motion[PAWN].coor[j].catch_piece[k] == 0 && info_motion[PAWN].coor[j].promotion[k] == 1){
				aux = 0;
				while(aux++ < 4){
					printf("%c%c%d",info_motion[PAWN].coor[j].actual_col+97,info_motion[PAWN].coor[j].col[k]+97,RANKS-info_motion[PAWN].coor[j].lin[k]);
					printf("%c\n",typePiece[aux]);	
				}
			}
			//Verificando se não existe captura, promoção e en passant
			if(info_motion[PAWN].coor[j].catch_piece[k] == 0 && info_motion[PAWN].coor[j].promotion[k] == 0 && info_motion[PAWN].coor[j].en_passant[k] == 0){
					printf("%c%c%d\n",info_motion[PAWN].coor[j].actual_col+97,info_motion[PAWN].coor[j].col[k]+97,RANKS-info_motion[PAWN].coor[j].lin[k]);	
			}
			k++;
		}
		j++;
	}

	//Impressão das demais peças
	for(i=1;i<AMOUNT_PIECE;i++){
		//Verificando a quantidade de peças do mesmo tipo
		amountPiece = info_motion[i].amount_piece;
		j = 0;
		while(amountPiece-- > 0){
			//Verificando a quantidade de movimentos da peça
			amountMotion = info_motion[i].coor[j].amount_motion;
			k = 0;
			while(amountMotion-- > 0){
				//Impressão do seu tipo
				printf("%c",typePiece[i]);
				//Verificando se há um movimento igual
				if(info_motion[i].coor[j].equal[k] == 1){
					printf("%c",info_motion[i].coor[j].actual_col+97);
				}
				//Verificando se há captura
				if(info_motion[i].coor[j].catch_piece[k] == 1){
					printf("x");
				}
				//Impressão do movimento
				printf("%c%d\n",info_motion[i].coor[j].col[k]+97,RANKS-info_motion[i].coor[j].lin[k]);
				k++;
			}
			j++;
		}
	}
}

/*
Armazenando todas as funções de movimento em um ponteiro
Parâmetros: GEN_MOTION *
Retorno: GEN_MOTION *
*/
GEN_MOTION *start_gen_motion(){

	GEN_MOTION *gen_motion = (GEN_MOTION*) malloc(sizeof(GEN_MOTION) * AMOUNT_PIECE );

	gen_motion[0].pointer = motion_pawn;
	gen_motion[1].pointer = motion_knight;
	gen_motion[2].pointer = motion_bishop;
	gen_motion[3].pointer = motion_rook;
	gen_motion[4].pointer = motion_queen;
	gen_motion[5].pointer = motion_king;

	return gen_motion;
}

/*
Gerando todos os movimentos
Parâmetros: GEN_MOTION *, XADREZ *, MOTION *, char , int
Retorno: int
*/
int generate_motion(GEN_MOTION *gen_motion, XADREZ *xadrez, MOTION *motion, char color, int control){

	int i;
	int ret = 0;

	//Gerando os movimentos
	for(i=0;i<AMOUNT_PIECE;i++){
		if(color == 'w'){
			ret = gen_motion[i].pointer(gen_motion,xadrez,motion,'w',control);
			//Ret é uma variável auxliar que será utilizada para verificar se os movimentos põem o rei em xeque
			if(ret == 1) return ret;
		}
		else{
			ret = gen_motion[i].pointer(gen_motion,xadrez,motion,'b',control);
			if(ret == 1) return ret ;
		}
	}
	return ret;
}

/*
Desalocando a estrutura que armazena as funções de movimento
Parâmetros: GEN_MOTION *
Retorno: nennhum
*/
void destroy_gen_motion(GEN_MOTION *gen_motion){
	free(gen_motion);
}

/*
Imprime o tabuleiro
Parâmetros: XADREZ *
Retorno: nenhum
*/
void imprime(XADREZ *xadrez){

	int i,j;
	
	for(i=0;i<RANKS;i++){
		for(j=0;j<FILES;j++){
			//Onde é vazio será impresso um ponto '.'
			if(xadrez->board[i][j].piece == empty){
				if(j==0) printf("\t%d ",RANKS-i);
				printf(".");
			}
			//Onde não é vazio é impresso a peça
			else{
				if(j==0) printf("\t%d ",RANKS-i);
				printf("%c",xadrez->board[i][j].piece);
			}
		}
		printf("\n");
	}

	printf("\n\t  abcdefgh\n\n");
}
