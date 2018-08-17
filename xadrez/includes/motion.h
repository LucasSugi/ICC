/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#ifndef _MOTION_H_
#define _MOTION_H_

#define FILES 8
#define RANKS 8
#define empty 'e'
#define AMOUNT_PIECE 6
#define NO 0
#define YES 1

//Estrutura contendo informações sobre o tabuleiro
typedef struct board{
	
	char piece;

} BOARD;

//Estrutura contendo informações sobre em que posição ocorre o roque
typedef struct roque{
	
	char *roqueBlack;
	char *roqueWhite;

} ROQUE;

//Estrutura contendo informações sobre em que posição ocorre o en passant
typedef struct en_passant{
	
	int rank;
	int file;

} EN_PASSANT;

//Estrutura contendo informações sobre o xadrez
typedef struct xadrez{
	
	BOARD **board;
	char turn;
	ROQUE *roque;
	EN_PASSANT *en_passant;
	int middle_turn;
	int num_turn;	

} XADREZ;

//Estrutura contendo todas as coordenadas e informações sobre o movimento
typedef struct coor{

	int actual_lin;
	int actual_col;	
	int *lin;
	int *col;
	int *catch_piece;
	int *promotion;
	int *en_passant;
	int *equal;
	int amount_motion;

} COOR;

//Estrutura que irá conter para peça seus respectivos movimentos
typedef struct info_motion{
	
	COOR *coor;
	int amount_piece;

} INFO_MOTION;

//Estrutura contendo os movimentos das peças brancas e pretas
typedef struct motion{
	
	INFO_MOTION *black;
	INFO_MOTION *white;

} MOTION;

//Estrutura com os ponteiros para a função que gera os movimentos de cada peça
typedef struct gen_motion{
	
	int (*pointer)(struct gen_motion*, XADREZ *, MOTION *, char, int);

} GEN_MOTION;

//Inicializando o xadrez
XADREZ *start_xadrez();

//Desalocação do xadrez
void destroy_xadrez(XADREZ *);

//Criação dos movimentos
MOTION *create_motion(XADREZ *);

//Desalocação da estrutura de movimentos
void destroy_motion(MOTION *);

//Movimentos do peão
int motion_pawn(GEN_MOTION *, XADREZ *, MOTION *, char, int);

//Movimento do cavalo
int motion_knight(GEN_MOTION *, XADREZ *, MOTION *, char, int);

//Movimento do bispo
int motion_bishop(GEN_MOTION *, XADREZ *, MOTION *, char, int);

//Movimento da torre
int motion_rook(GEN_MOTION *, XADREZ *, MOTION *, char, int);

//Movimento da rainha
int motion_queen(GEN_MOTION *, XADREZ *, MOTION *, char, int);

//Movimento do rei
int motion_king(GEN_MOTION *, XADREZ *, MOTION *, char, int);

//Ordenação dos movimentos
void sort_motion(INFO_MOTION *);

//Iniciando a estrutura com os ponteiros para a função
GEN_MOTION *start_gen_motion();

//Desalocando a estrutura com os ponteiros para a função
void destroy_gen_motion(GEN_MOTION *);

//Geração de todos os movimentos
int generate_motion(GEN_MOTION *, XADREZ *, MOTION *, char, int);

//Verificando se há movimentos iguais
void equal_motion(INFO_MOTION *);

//Imprime todos os movimentos
void print_motion(INFO_MOTION *);

//Imprime a situação do tabuleiro
void imprime(XADREZ *);

#endif