/*
 * Nome: Lucas Yudi
 * Número USP: 9293251
 */

#ifndef _OCR_H_
#define _OCR_H_

typedef struct image{

	int nrow;
	int ncol;	
	unsigned char **mat_img;
	
}IMAGE;

//Erosão da imagem
int erode_image(IMAGE *, IMAGE *,int , int );

//Erosão da imagem
void erode(IMAGE *, IMAGE *, IMAGE *);

//Dilatação da imagem
void dilate_image(IMAGE *, IMAGE *, IMAGE *, int , int , int , int );

//Dilatação da imagem
void dilate(IMAGE *, IMAGE *, IMAGE *);

//Transformando a string em uma matriz de imagem
void transform(unsigned char *, IMAGE *);

//Desalocando a imagem
void destroy_img(IMAGE *);

//Impressão da imagem resultante
void print_image(IMAGE *, IMAGE *, IMAGE *);

//Cópia da imagem
void copy_image(IMAGE *, IMAGE *);

//Zerando a imagem resultante
void reset_image(IMAGE *);

//Operações morfológicas
IMAGE *mem_op(int , int );

//Cálculo da distância de hamming
int mem_dist_image(IMAGE *, IMAGE *);

//Distância de hamming
void mem_dist();

#endif
