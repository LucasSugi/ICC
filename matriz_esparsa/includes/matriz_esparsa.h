#ifndef _MATRIZ_ESPARSA_H_
#define _MATRIZ_ESPARSA_H_

typedef struct matriz_esparsa MATRIZ_ESPARSA;

MATRIZ_ESPARSA *criar_matriz(int, int);
void apagar_matriz(MATRIZ_ESPARSA**);

int set(MATRIZ_ESPARSA*,int,int,float);
float get(MATRIZ_ESPARSA*,int,int);

void imprimir_matriz(MATRIZ_ESPARSA*);

#endif
