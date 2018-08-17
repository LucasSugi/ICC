/*
 * Nome: Lucas Yudi Sugi
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "conversion.h"

#define BYTE 8

/*
Conversão da string em um valor
Parâmetros: int, int, int, int
Retorno: nenhum
*/
void conversion_string_to_int(FILE *fp, int nrow, int ncol, int amount_bits, int amount_bytes){
	
	unsigned char *image = NULL;
	int i, j, pos, *number = NULL;
		
	//Alocando a quantidade de memória necessária para a imagem
	image = (unsigned char*) malloc(sizeof(unsigned char) * (amount_bits + 1));
	
	//Armazenando a imagem do stdin
	scanf("%s",image);

	//Zerando as posições da imagem
	for(i=nrow*ncol;i<amount_bits;i++){
		image[i] = '0';	
	}
	image[i] = '\0';
	
	//Alocação dos números que seráo convertidos
	number = (int*) calloc(sizeof(int),amount_bytes); 

	//Posição da primeira imagem
	pos = BYTE - 1;
		
	//Conversão da imagem em um número
	for(i=0;i<amount_bytes;i++){	
		for(j=0;j<BYTE;j++){
			if(image[pos-j] == '1'){
			number[i] += pow(2,j);
			}
		}
		pos += BYTE;
	}
	
	//Desalocando a image
	free(image);	
	
	//Armazenando no arquivo
	for(i=0;i<amount_bytes;i++){
		fwrite(&number[i],1,1,fp);
	}
	
	//Liberando o número
	free(number);
}


/*
Conversão do inteiro para string
Parâmetros: FILE *, int, int, int
Retorno: unsigned char *
*/
unsigned char *conversion_int_to_string(FILE *fp, int end, int amount_bits, int amount_bytes){
	
	int i,j;
	char *binary = NULL;
	int pos, decimal = 0;

	//Alocando a quantidade necessária para a imagem
	binary = (char*) malloc(sizeof(char) * (amount_bits + 1));
	
	//Posição da primeira imagem
	pos = BYTE-1;

	//Convertendo o valor decimal para string
	for(i=0;i<amount_bytes;i++){
		fread(&decimal,1,1,fp);	
		for (j = 0; j < BYTE; j++) {
			binary[pos-j] = decimal & (int) pow(2, j)?'1':'0';
		}
		pos += BYTE;
		decimal = 0;
	}
	binary[end] = '\0';

	return binary;
}
