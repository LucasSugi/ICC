/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#ifndef _VICTORY_CONDITION_H_
#define _VICTORY_CONDITION_H_

#include "motion.h"

//Leitura das coordenadas das jogadas
char *read_name();

//Impressão da fen
void print_fen(XADREZ *);

//Verifcação de xeque-mate ou empate (Afogamento)
int check_mate_or_tie(GEN_MOTION *, XADREZ*);

//Verificação de empate - Falta de material
int check_tie_material_miss(XADREZ *);

//Verificação de empate - Regra dos 50 movimentos
int check_tie_50mov(XADREZ *);

//Jogando xadrez
int play_xadrez(GEN_MOTION *, XADREZ *, int *);

#endif