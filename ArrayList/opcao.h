/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#ifndef _OPTION_H_
#define _OPTION_H_

#include "ArrayList.h"
#include "item.h"

/*Nesse cabeçalho são definidos subfunções todas responsáveis por receber dados e executar
 *as funções contidas em ArrayList.c
 */

void sub(ArrayList *);

void set(ArrayList *);

void get(ArrayList *);

void remover(ArrayList *);

void index_array(ArrayList *);

void contains(ArrayList *);

void add(ArrayList *);

#endif
