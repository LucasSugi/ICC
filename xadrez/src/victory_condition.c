/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include "motion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//Leitura do código FEN
char *read_name(){

	char *name = (char*) malloc(sizeof(char) * 10);
	
	//Leitura
	scanf("%s",name);
	
	return name;
}

/*
Impressão da FEN
Parâmetros: XADREZ *
Retorno: nenhum
*/
void print_fen(XADREZ *xadrez){

	int i,j;
	int counter = 0;

	//Impressão do tabuleiro
	for(i=0;i<RANKS;i++){
		for(j=0;j<FILES;j++){
			if(xadrez->board[i][j].piece == empty){
				counter++;
			}
			else{
				if(counter != 0){
					printf("%d",counter);
					counter = 0;	
				}
				printf("%c",xadrez->board[i][j].piece);
			}
		}
		if(counter != 0){
			printf("%d",counter);
			counter = 0;
		}
		if(i!= RANKS-1)printf("/");
	}

	//Impressão do turno
	printf(" %c ",xadrez->turn);

	counter = 0;
	//Impressão do roque caso exista
	if(xadrez->roque->roqueWhite[0] != '-'){
		printf("%c",xadrez->roque->roqueWhite[0]);
	}
	else{
		counter++;
	}
	if(xadrez->roque->roqueWhite[1] != '-'){
		printf("%c",xadrez->roque->roqueWhite[1]);
	}
	else{
		counter++;
	}
	if(xadrez->roque->roqueBlack[0] != '-'){
		printf("%c",xadrez->roque->roqueBlack[0]);
	}
	else{
		counter++;
	}
	if(xadrez->roque->roqueBlack[1] != '-'){
		printf("%c",xadrez->roque->roqueBlack[1]);
	}
	else{
		counter++;
	}
	if(counter == 4){
		printf("-");
	}

	//Impressão do en passant
	if(xadrez->en_passant->rank != -1 && xadrez->en_passant->file != -1){
		printf(" %c",xadrez->en_passant->file+97);
		printf("%d ",RANKS-xadrez->en_passant->rank);
	}
	else{
		printf(" - ");
	}

	//Impressão do meio turno
	printf("%d ",xadrez->middle_turn);

	//Impressão do turno
	printf("%d\n",xadrez->num_turn);
}

/*
Verifica se pode ocorrer um en passant
Parâmetros: XADREZ *, int, int, int, int
Retorno: int
*/
int verify_en_passant(XADREZ *xadrez,int posActualCol, int posActualLin, int posCol, int posLin){

	//Verifica qual a cor da peça
	if(islower(xadrez->board[posLin][posCol].piece)){
		//Verifica se o peão andou duas casas, caso tenha andado pode ocorrer en passant
		if(posLin == 3 && posActualLin == 1){
			xadrez->en_passant->rank = 2;
			xadrez->en_passant->file = posCol;
			return YES;
		}
	}
	else{
		if(posLin == 4 && posActualLin == 6){
			xadrez->en_passant->rank = 5;
			xadrez->en_passant->file = posCol;
			return YES;
		}
	}

	return NO;
}

/*
Verifica se não se pode mais realizar roque
Parâmetros: XADREZ *, int, int, int, int
Retorno: nenhum
*/
void verify_roque1(XADREZ *xadrez,int posActualCol, int posActualLin, int posCol, int posLin){

	//Verifica a cor da peça
	if(islower(xadrez->board[posLin][posCol].piece)){
		//Verifica se o rei ou a torre saiu da sua posição atual do tabuleiro para outro lugar, caso ocorra então não existe mais roque
		if(posActualLin == 0 && posActualCol == 0){
			xadrez->roque->roqueBlack[1] = '-';
		}
		else if(posActualLin == 0 && posActualCol == 7){
			xadrez->roque->roqueBlack[0] = '-';
		}
		else if(posActualLin == 0 && posActualCol == 4){
			xadrez->roque->roqueBlack[0] = '-';
			xadrez->roque->roqueBlack[1] = '-';
		}
	}
	else{
		if(posActualLin == 7 && posActualCol == 0){
			xadrez->roque->roqueWhite[1] = '-';
		}
		else if(posActualLin == 7 && posActualCol == 7){
			xadrez->roque->roqueWhite[0] = '-';
		}
		else if(posActualLin == 7 && posActualCol == 4){
			xadrez->roque->roqueWhite[0] = '-';
			xadrez->roque->roqueWhite[1] = '-';
		}
	}
}

/*
Verifica se não se pode mais realizar roque
Parâmetros: XADREZ *, int, int
Retorno: nenhum
*/
void verify_roque2(XADREZ *xadrez, int posCol, int posLin){

	//Verificando a cor da peça
	if(islower(xadrez->board[posLin][posCol].piece)){
		if(posLin == 0 && posCol == 0){
			xadrez->roque->roqueBlack[1] = '-';
		}
		else if(posLin == 0 && posCol == 7){
			xadrez->roque->roqueBlack[0] = '-';
		}
	}
	else{
		if(posLin == 7 && posCol == 0){
			xadrez->roque->roqueWhite[1] = '-';
		}
		else if(posLin == 7 && posCol == 7){
			xadrez->roque->roqueWhite[0] = '-';
		}
	}
}

/*
Verificando se o roque ocorre
Parâmetros: XADREZ *, int, int, int, int
Retorno: nenhum
*/
void verify_roque_swap(XADREZ *xadrez,int posActualCol, int posActualLin, int posCol, int posLin){

	//Verifica a cor da peça
	if(islower(xadrez->board[posLin][posCol].piece)){
		//Verifica o movimento do rei foi o roque, caso seja então a torre é movimentada também
		if(posActualLin == 0 && posActualCol == 4 && posCol == 2){
			xadrez->board[0][3].piece = 'r';
			xadrez->board[0][0].piece = empty;
		}
		else if(posActualLin == 0 && posActualCol == 4 && posCol == 6){
			xadrez->board[0][5].piece = 'r';
			xadrez->board[0][7].piece = empty;
		}
	}
	else{
		if(posActualLin == 7 && posActualCol == 4 && posCol == 2){
			xadrez->board[7][3].piece = 'R';
			xadrez->board[7][0].piece = empty;
		}
		else if(posActualLin == 7 && posActualCol == 4 && posCol == 6){
			xadrez->board[7][5].piece = 'R';
			xadrez->board[7][7].piece = empty;
		}
	}
}

/*
Checando se as coordenadas passadas são válidas
Parâmetros: 
Retorno: int
*/
void checks_position(XADREZ *xadrez, INFO_MOTION *info_motion, int posActualCol, int posActualLin, int posCol, int posLin, char promotion, int *counter){

	int i,j,k;
	int amountPiece, amountMotion, ret = NO;
	int valid = NO, piece = -1,catch_piece = -1;

	//Percorrendo todas as peças
	for(i=0;i<AMOUNT_PIECE;i++){
		//Percorrendo as peças do mesmo tipo
		amountPiece = info_motion[i].amount_piece;
		j = 0;
		while(amountPiece-- > 0){
			if(info_motion[i].coor[j].actual_lin == posActualLin && info_motion[i].coor[j].actual_col == posActualCol){
				amountMotion = info_motion[i].coor[j].amount_motion;
				k = 0;
				while(amountMotion-- > 0){
					if(info_motion[i].coor[j].lin[k] == posLin && info_motion[i].coor[j].col[k] == posCol){
						//Verificando se a peça a ser caputarada é a torre
						if(xadrez->board[posLin][posCol].piece == 'r' || xadrez->board[posLin][posCol].piece == 'R'){
							verify_roque2(xadrez,posCol,posLin);
						}
						//Verificando se a peça em questão é um peão que precisa de promoção
						if(promotion == empty){
							 xadrez->board[posLin][posCol].piece = xadrez->board[posActualLin][posActualCol].piece;
							 xadrez->board[posActualLin][posActualCol].piece = empty;
						}
						else{
							if(islower(xadrez->board[posActualLin][posActualCol].piece)){
								xadrez->board[posLin][posCol].piece = tolower(promotion);
							}
							else{
								xadrez->board[posLin][posCol].piece = promotion;	
							}
							xadrez->board[posActualLin][posActualCol].piece = empty;	
						}
						//Funções que verificam empate,roque e en passant
						if(i == PAWN) ret = verify_en_passant(xadrez,posActualCol,posActualLin,posCol,posLin);
						verify_roque_swap(xadrez,posActualCol,posActualLin,posCol,posLin);
						if(i == ROOK || i == KING) verify_roque1(xadrez,posActualCol,posActualLin,posCol,posLin);
						//Armazenando o catch_piece
						catch_piece = info_motion[i].coor[j].catch_piece[k];
						//Armazenando a peça
						piece = i;
						//Dizendo que o movimento é válido
						valid = YES;
						break;
					}
					k++;
				}
			}
			j++;
		}
	}

	//Caso o movimento seja válido então é trocado o turno
	if(valid == YES){
		//Alterando o turno
		if(xadrez->turn == 'w'){
			xadrez->turn = 'b';
		}
		else{
			 xadrez->turn = 'w';
		}
		//Verificando a ocorrência de meio turno
		if(piece != PAWN && catch_piece == 0){
			xadrez->middle_turn++;
		}
		//Zerando os meios turnos
		if(piece == PAWN || catch_piece == 1){
			xadrez->middle_turn = 0;
		}
		//Verificando se um turno já foi completo
		(*counter)++;
		if(*counter == 2){
			xadrez->num_turn++;
			*counter = 0;
		}
		if(ret == NO){
			xadrez->en_passant->rank = -1;
			xadrez->en_passant->file = -1;
		}
		//Impressão da fen
		print_fen(xadrez);
	}
	else{
		printf("Movimento invalido. Tente novamente.\n");
	}	
}

/*
Verifica empate por ocorrer os 50 movimentos
Parâmetros: XADREZ *
Retorno: nenhum
*/
int check_tie_50mov(XADREZ *xadrez){

	//Empate por meio dos 50 movimentos
	if(xadrez->middle_turn == 50){
		printf("Empate -- Regra dos 50 Movimentos\n");
		return YES;
	}

	return NO;
}

/*
Verica empate por falta de material
Parâmetros: XADREZ *
Retorno: nenhum
*/
int check_tie_material_miss(XADREZ *xadrez){

	int i,j;
	int amountKnight = 0, amountBishop = 0, amountPiece = 0;

	//Empate por falta de material
	for(i=0;i<RANKS;i++){
		for(j=0;j<FILES;j++){
			if(xadrez->board[i][j].piece == 'n' || xadrez->board[i][j].piece == 'N'){
				amountKnight++;
			}
			else if(xadrez->board[i][j].piece == 'b' || xadrez->board[i][j].piece == 'B'){
				amountBishop++;
			}
			else if(xadrez->board[i][j].piece != empty && xadrez->board[i][j].piece != 'K' && xadrez->board[i][j].piece != 'k'){
				amountPiece++;
			}
		}
	}
	if(amountPiece == 0){
		if( (amountBishop == 1 || amountBishop == 0) && amountKnight == 0){
			printf("Empate -- Falta de Material\n");
			return YES;
		}
		else if( (amountKnight == 1 || amountKnight == 0) && amountBishop == 0){
			printf("Empate -- Falta de Material\n");
			return YES;
		}
	}

	return NO;
}

/*
Verificando quantos movimentos o jogador possui
Parâmetros: INFO_MOTION *
Retorno: nenhum
*/
int verify(INFO_MOTION *info_motion){

	int i,j;
	int amountPiece, amountMotion;
	int counter = 0;

	//Verificando se há algum movimento possível
	for(i=0;i<AMOUNT_PIECE;i++){
		amountPiece = info_motion[i].amount_piece;
		j = 0;
		while(amountPiece-- > 0){
			amountMotion = info_motion[i].coor[j].amount_motion;
			if(amountMotion > 0){
				counter++;
			}
			j++;
		}
	}

	//NO indica que não há movimentos possíveis enquanto que YES sim
	if(counter == 0){
		return NO;
	}
	else{
		return YES;
	}
}

/*
Verificando se ocorreu xeque-mate ou empate por afogamento
Parâmetros:
Retorno: int
*/
int check_mate_or_tie(GEN_MOTION *gen_motion, XADREZ *xadrez){

	int i,j;
	int retGen, retVer;
	MOTION *motion;

	//Alocando a variável que irá armazenar os movimentos
	motion = create_motion(xadrez);

	//Gerando todos os movimentos e verificando a ocorrência de xeque-mate ou empate por afogamento
	if(xadrez->turn == 'w'){
		generate_motion(gen_motion,xadrez,motion,'w',0);
		retGen = generate_motion(gen_motion,xadrez,motion,'b',1);
		retVer = verify(motion->white);
	}
	else{
		generate_motion(gen_motion,xadrez,motion,'b',0);
		retGen = generate_motion(gen_motion,xadrez,motion,'w',1);	
		retVer = verify(motion->black);
	}

	/*retGen irá informar se o rei está em perigo(1) ou não(0)
	retVer irá informar se existe algum movimento possível
	A combinação deles irá gerar empate ou xeque*/
	if(retGen == 1 && retVer == 0){
		printf("Cheque-mate -- Vitoria: ");
		if(xadrez->turn == 'w'){
			printf("PRETO\n");
		}
		else{
			printf("BRANCO\n");
		}
		destroy_motion(motion);
		return YES;
	}
	else if(retGen == 0 && retVer == 0){
		printf("Empate -- Afogamento\n");
		destroy_motion(motion);
		return YES;
	}

	//Desalocação
	destroy_motion(motion);

	return NO;
}

/*
Jogando com o xadrez
Parâmetros: XADREZ *
Retorno: nenhum
*/
int play_xadrez(GEN_MOTION *gen_motion, XADREZ *xadrez, int *counter){

	int tam, ret = NO;
	char *pos;
	MOTION *motion;

	//Inicializando a estrutura que armazena os movimentos
	motion = create_motion(xadrez);

	//Gerando os movimentos
	generate_motion(gen_motion,xadrez,motion,xadrez->turn,0);

	//Armazenando a coordenada atual e futura da peça
	pos = read_name();

	//Verificando se existe promoção na peça
	tam = strlen(pos);

	//Verificando por empate
	ret = check_tie_50mov(xadrez);
	if(ret == YES) {
		destroy_motion(motion);
		free(pos);
		return YES;
	}

	//Percorrendo os movimentos para verificar se as coordenas que foram passadas são validas
	if(xadrez->turn == 'w'){
		//Caso exista 5 caracteres, então existe promoção
		if(tam == 5){
			checks_position(xadrez,motion->white,pos[0]-97,RANKS-(pos[1]-48),pos[2]-97,RANKS-(pos[3]-48),pos[4],counter);
		}
		else{
			checks_position(xadrez,motion->white,pos[0]-97,RANKS-(pos[1]-48),pos[2]-97,RANKS-(pos[3]-48),empty,counter);
		}
	}
	else{
		//Caso exista 5 caracteres, então existe promoção
		if(tam == 5){
			checks_position(xadrez,motion->black,pos[0]-97,RANKS-(pos[1]-48),pos[2]-97,RANKS-(pos[3]-48),pos[4],counter);
		}
		else{
			checks_position(xadrez,motion->black,pos[0]-97,RANKS-(pos[1]-48),pos[2]-97,RANKS-(pos[3]-48),empty,counter);
		}
	}

	//Desalocando os movimentos
	destroy_motion(motion);

	//Desalocando as coordenas
	free(pos);	

	//Verificando por xeque-mate
	ret = check_mate_or_tie(gen_motion,xadrez);
	if(ret == YES){
		return YES;
	}

	//Verificando por empate
	ret = check_tie_material_miss(xadrez);
	if(ret == YES) {
		return YES;
	}

	return ret;
}
