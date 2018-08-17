/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ocr.h"

/*
Erosão da imagem
Parâmetros: IMAGE *, IMAGE *, int, int
Retorno: int
*/
int erode_image(IMAGE *img1, IMAGE *img2,int x, int y){

	int i,j,aux_x,aux_y, counter = 0;
	
	//Foi utilizado a operação xor, para verificar se há diferença entre o elemento estruturante e a matriz	
	for(i=0,aux_x=x;i<img2->nrow;i++,aux_x++){
		for(j=0,aux_y=y;j<img2->ncol;j++,aux_y++){
			if(img1->mat_img[aux_x][aux_y] ^ img2->mat_img[i][j] && img2->mat_img[i][j] == '1'){
				counter++;	
			}
		}
	}
	
	return counter;
}

/*
Erosão da imagem
Parâmetros: IMAGE *, IMAGE *, IMAGE *
Retorno: nenhum
*/
void erode(IMAGE *img1, IMAGE *img2, IMAGE *imgRes){
	
	int middle_x, middle_y, i,j, retorno;
	int middleX, middleY;
	
	middleX = img1->nrow/2;
	middleY = img1->ncol/2;

	//Cálculo das coordenadas do meio da imagem
	middle_x = img2->nrow/2;
	middle_y = img2->ncol/2;
	
	for(i=0;i<img1->nrow;i++){
		for(j=0;j<img1->ncol;j++){
			if(img1->mat_img[i][j] == '1'){
				retorno = erode_image(img1,img2,i-middle_x,j-middle_y);
				//Caso as matrizes sejam diferentes, no ponto em questão é setado '1'
				if(retorno == 0){
					imgRes->mat_img[i][j] = '1';
				}
				else{
					imgRes->mat_img[i][j] = '0';
				}
			}
			//Caso no meio da matriz seja 0, é setado como '1'
			if(img1->mat_img[i][j] == '0' && i == middleX && j == middleY){
				imgRes->mat_img[i][j] = '1';
			}
		}
	}
}

/*
Dilatação da imagem
Parãmetros: IMAGE *img1, IMAGE *img2, IMAGE *imgRes , int, int, int, int
*/
void dilate_image(IMAGE *img1, IMAGE *img2, IMAGE *imgRes, int x, int y, int middleX, int middleY){

	int i,j,aux_x,aux_y;
	
	for(i=0,aux_x=x;i<img2->nrow;i++,aux_x++){
		for(j=0,aux_y=y;j<img2->ncol;j++,aux_y++){
			//Caso o ponto das matrizes seja diferente e este seja '1' no elemento estruturante, então é setado '1'
			if(img1->mat_img[aux_x][aux_y] ^ img2->mat_img[i][j] && img2->mat_img[i][j] == '1'){
				imgRes->mat_img[aux_x][aux_y] = '1';
			}
			//Caso o ponto das matrizes seja diferente e este seja o meio do elemento estruturante, é setado '0'
			if(img1->mat_img[aux_x][aux_y] ^ img2->mat_img[i][j] && i == middleX && j == middleY){
				imgRes->mat_img[aux_x][aux_y] = '0';
			}
			//Caso o ponto das matrizes seja diferente '1' e este seja o meio do elemento estruturante, é setado '1'
			else if(img1->mat_img[aux_x][aux_y] & img2->mat_img[i][j] && i == middleX && j == middleY){
				imgRes->mat_img[aux_x][aux_y] = '1';
			}
		}
	}
}

/*
Dilatação da imagem
Parâmetros: IMAGE*, IMAGE*, IMAGE *
Retorno: nenhum
*/
void dilate(IMAGE *img1, IMAGE *img2, IMAGE *imgRes){

	int middle_x, middle_y, i,j;

	//Cálculo das coordenadas do meio da imagem
	middle_x = img2->nrow/2;
	middle_y = img2->ncol/2;
	
	for(i=0;i<img1->nrow;i++){
		for(j=0;j<img1->ncol;j++){
			if(img1->mat_img[i][j] == '1'){
				dilate_image(img1,img2,imgRes,i-middle_x,j-middle_y,middle_x,middle_y);
			}
		}
	}
}

/*
Transformação da string em matriz
Parâmetros: unsigned char*,IMAGE *
Retorno: nenhum
*/
void transform(unsigned char *string, IMAGE *img){

	int i,j,k;
	
	//Alocação da imagem - Linhas
	img->mat_img = (unsigned char**) malloc(sizeof(unsigned char*) * img->nrow);
	
	//Alocação da imagem - Colunas
	for(i=0;i<img->nrow;i++){
		img->mat_img[i] = (unsigned char*) malloc(sizeof(unsigned char) * img->ncol);
	}
	
	k = 0;
	
	//Copiando o conteúdo da string para a matriz
	for(i=0;i<img->nrow;i++){
		for(j=0;j<img->ncol;j++){
			img->mat_img[i][j] = string[k];
			k++;
		}
	}
}

/*
Desalocação da imagem
Parâmetros: IMAGE *
Retorno: nenhum
*/
void destroy_img(IMAGE *img){

	int i;

	for(i=0;i<img->nrow;i++){
		free(img->mat_img[i]);
	}
		
	free(img->mat_img);
	free(img);
}

/*
Impressão das imagens
Parâmetros: IMAGE *, IMAGE *, IMAGE *
Retorno: nenhum
*/
void print_image(IMAGE *img1, IMAGE *img2, IMAGE *imgRes){

	int i,j;
	
	printf("im:\n");
	for(i=0;i<img1->nrow;i++){
		for(j=0;j<img1->ncol;j++){
			printf("%c ",img1->mat_img[i][j]);
		}
		printf("\n");
	}
		
	printf("el:\n");
	for(i=0;i<img2->nrow;i++){
		for(j=0;j<img2->ncol;j++){
			printf("%c ",img2->mat_img[i][j]);
		}
		printf("\n");
	}
	
	printf("out:\n");
	for(i=0;i<imgRes->nrow;i++){
		for(j=0;j<imgRes->ncol;j++){
			printf("%c ",imgRes->mat_img[i][j]);
		}
		printf("\n");
	}
}

/*
Cópia da imagem
Parâmetros: IMAGE *, IMAGE *
Retorno: nenhum
*/
void copy_image(IMAGE *img, IMAGE *imgRes){

	int i,j;
	
	//Cópia das linhas e colunas
	imgRes->nrow = img->nrow;
	imgRes->ncol = img->ncol;
	
	//Alocação da cópia
	imgRes->mat_img = (unsigned char**) malloc(sizeof(unsigned char*) * imgRes->nrow);
	
	//Cópia dos pixels
	for(i=0;i<img->nrow;i++){
		imgRes->mat_img[i] = (unsigned char*) malloc(sizeof(unsigned char) * imgRes->ncol);
		for(j=0;j<img->ncol;j++){
			imgRes->mat_img[i][j] = img->mat_img[i][j];
		}
	}
}

/*
Zerando a imagem
Parâmetros: IMAGE *
Retorno: nenhum
*/
void reset_image(IMAGE *img){

	int i,j;

	//Zerando a imagem resultante	
	for(i=0;i<img->nrow;i++){
		for(j=0;j<img->ncol;j++){
			img->mat_img[i][j] = '0';
		}
	}
}

/*
Operações morfológicas
Parâmetros: int, int
Retorno: IMAGE *
*/
IMAGE *mem_op(int control_1, int control_2){

	IMAGE *img1 = (IMAGE*) malloc(sizeof(IMAGE));
	IMAGE *img2 = (IMAGE*) malloc(sizeof(IMAGE));
	IMAGE *imgRes = (IMAGE*) malloc(sizeof(IMAGE));
	unsigned char *string_image = NULL;
	char aux[50];
		
	//Armazenando as medidas da primeira imagem	
	scanf("%d %d",&img1->nrow,&img1->ncol);	

	//Alocando e armazenando a imagem
	string_image = (unsigned char*) malloc(sizeof(unsigned char) * ((img1->nrow * img1->ncol) + 1));
	scanf("%s",string_image);
	
	//Transformando a string em matriz
	transform(string_image,img1);
	
	//Desalocando	
	free(string_image);

	//Cópia da imagem original
	copy_image(img1,imgRes);
		
	//Zerando a imagem resultante
	reset_image(imgRes);
		
	//Armazenando as medidas da imagem estruturante
	scanf("%d %d",&img2->nrow,&img2->ncol);	
	
	//Alocando e armazenando a imagem
	string_image = (unsigned char*) malloc(sizeof(unsigned char) * ((img2->nrow * img2->ncol) + 1));
	scanf("%s",string_image);
	
	//Transformando a string em matriz
	transform(string_image,img2);
	
	//Desalocando	
	free(string_image);
	
	//Armazenando a ação que deverá ser executada na imagem
	scanf("%s",aux);

	if( strcmp(aux,"dilate") == 0){
		dilate(img1,img2,imgRes);
	}
	else if( strcmp(aux,"erode") == 0){
		erode(img1,img2,imgRes);
	}
	else if( strcmp(aux,"open") == 0){
		IMAGE *img3 = (IMAGE*) malloc(sizeof(IMAGE));
		erode(img1,img2,imgRes);
		copy_image(imgRes,img3);
		reset_image(imgRes);
		dilate(img3,img2,imgRes);
		destroy_img(img3);
	}
	else if( strcmp(aux,"close") == 0){
		IMAGE *img3 = (IMAGE*) malloc(sizeof(IMAGE));
		dilate(img1,img2,imgRes);
		copy_image(imgRes,img3);
		reset_image(imgRes);
		erode(img3,img2,imgRes);
		destroy_img(img3);
	}
	
	if(control_2 == 1){
		//Impressão da imagem original, elementro estruturante e image alterada
		print_image(img1,img2,imgRes);
	}
	
	//Desalocando as imagens
	destroy_img(img1);
	destroy_img(img2);
	
	//Caso seja realizado apenas as operações morfológicas então a imagem resultante é desalocada
	//Caso seja necessário realizar uma classificação, então a imagem é retornada
	if(control_1 == 1){
		destroy_img(imgRes);
		return NULL;
	}else{
		return imgRes;
	}
}

/*
Cálculo da distância de hamming
Parâmetros: IMAGE *, IMAGE *
Retorno: int
*/
int mem_dist_image(IMAGE *img1, IMAGE *img2){

	int i,j, counter = 0;

	for(i=0;i<img1->nrow;i++){
		for(j=0;j<img1->ncol;j++){
			if(img1->mat_img[i][j] ^ img2->mat_img[i][j]){
				counter++;
			}	
		}
	}
	return counter;
}

/*
Calcula a distância de hamming
Parâmetros: nenhum
Retorno: nenhum
*/
void mem_dist(){

	IMAGE *img1 = (IMAGE*) malloc(sizeof(IMAGE));
	IMAGE *img2 = (IMAGE*) malloc(sizeof(IMAGE));
	int counter;
	unsigned char *string_image = NULL;
		
	//Armazenando as medidas da primeira imagem	
	scanf("%d %d",&img1->nrow,&img1->ncol);	
	
	//As medidas da segunda imagem é igual ao da primeira
	img2->nrow = img1->nrow;
	img2->ncol = img1->ncol;;

	//Alocando e armazenando a imagem
	string_image = (unsigned char*) malloc(sizeof(unsigned char) * ((img1->nrow * img1->ncol) + 1));
	scanf("%s",string_image);
	
	//Transformando a string em matriz
	transform(string_image,img1);

	//Armazenando a imagem
	scanf("%s",string_image);
	
	//Transformando a string em matriz
	transform(string_image,img2);
	
	//Desalocando	
	free(string_image);	

	//Cálculo da distância
	counter = mem_dist_image(img1,img2);
	
	//Imprimindo a distância
	printf("dist = %d\n",counter);
	
	//Desalocando as imagens
	destroy_img(img1);
	destroy_img(img2);	
}
