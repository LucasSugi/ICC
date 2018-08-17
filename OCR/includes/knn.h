/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#ifndef _KNN_H_
#define _KNN_H_

#include <stdio.h>
#include "ocr.h"
#include "data.h"
#include "knn.h"
#include "conversion.h"

//Dump das n classes mais próximas
void dump_class(FILE *, INFO_SCHEMA *, int *);

//Dump da classe mais próxima
void dump_nn(FILE *, INFO_SCHEMA *, int *,int );

//Ordenação do vetor de dist
void sort(double *, int *, int );

//Procurando pelo vizinhos mais próximos
void search_knn(FILE *,INFO_SCHEMA *, INFO_DATA *, int , int );

//Classificaão das imagens
void ocr_dump_nn(INFO_SCHEMA *, INFO_DATA *, IMAGE *, int );

#endif
