/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "motion.h"
#include "victory_condition.h"

#define play 0
#define game_over 1

int main(int argc, char *argv[]){
	
	int ret = play;
	int counter = 0;
	XADREZ *xadrez;
	GEN_MOTION *gen_motion;
		
	//Armazenando o código
	xadrez = start_xadrez();
	
	//Imprimindo a condição inicial do xadrez
	print_fen(xadrez);
	
	//Inicializando a estrutura que calcula todos os movimentos
	gen_motion = start_gen_motion();

	//Checando empate
	ret = check_tie_material_miss(xadrez);

	//Checando empate
	ret |= check_tie_50mov(xadrez);

	//Checando empate e xeque-mate
	ret |= check_mate_or_tie(gen_motion,xadrez);
	
	//Jogando xadrez
	while(ret != game_over){
		ret = play_xadrez(gen_motion,xadrez,&counter);
	}

	//Desalocação da estrutura
	destroy_gen_motion(gen_motion);
	
	//Desalocando toda a estrutura
	destroy_xadrez(xadrez);
	
	return 0;
}
