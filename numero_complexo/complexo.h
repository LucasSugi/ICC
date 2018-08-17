#ifndef COMPLEXO_H
#define COMPLEXO_H

typedef struct n_complexo {

	int real;
	int imaginario;

} N_COMPLEXO;

N_COMPLEXO *criar(int r, int i);

void destruir(N_COMPLEXO *n);

N_COMPLEXO *adicao(N_COMPLEXO *n1, N_COMPLEXO *n2);

N_COMPLEXO *multiplicar(N_COMPLEXO *n1, N_COMPLEXO *n2);

void imprimir(N_COMPLEXO *n);

#endif
