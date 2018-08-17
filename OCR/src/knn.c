/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ocr.h"
#include "data.h"
#include "knn.h"
#include "conversion.h"

/*
Dump da classe
Parâmetros: FILE *, INFO_SCHEMA *, int *
Retorno: nenhum
*/
void dump_class(FILE *fp, INFO_SCHEMA *info_schema, int *offset){


	int i,printInt;
	double printDouble;
	char *printChar = (char*) malloc(sizeof(char) * 20);
	
	//Movendo para a classe mais próxima	
	fseek(fp,offset[0],SEEK_SET);
		//os fread sao usados para mover no arquivo até a classe desejada
		for(i=0;i<info_schema->amount_field;i++){
			if(info_schema->data_schema[i].type == 'i'){
				fread(&printInt,sizeof(int),1,fp);
			} 
			else if(info_schema->data_schema[i].type == 'd'){
				fread(&printDouble,sizeof(double),1,fp);
			}
			else if(info_schema->data_schema[i].type == 'c'){
				fread(printChar,info_schema->data_schema[i].tam,1,fp);
				printf("%s\n",printChar);
			}
			else {
				fread(printChar,info_schema->data_schema[i].tam,1,fp);
		}
	}

	free(printChar);
}

/*
Dump dos n registros mais próximos
Parâmetros: FILE *, INFO_SCHEMA *, int *, int
Retorno: nenhum
*/
void dump_nn(FILE *fp, INFO_SCHEMA *info_schema, int *offset,int neighbors){
	
	int i,j,printInt,nrow,ncol;
	double printDouble;
	char *printChar = (char*) malloc(sizeof(char) * 200);
	char *image = NULL;
	
	//Impressão dos n vizinhos	
	for(i=0;i<neighbors;i++){
		//Movendo para o próximo offset do registro
		fseek(fp,offset[i],SEEK_SET);
		for(j=0;j<info_schema->amount_field;j++){
			if(info_schema->data_schema[j].type == 'i'){
				printf("%s = ",info_schema->data_schema[j].filename_field);
				fread(&printInt,sizeof(int),1,fp);	
				//O armazenamento das linhas e colunas ocorre para que se possa transformar os bytes do arquivo da imagem
				if(j == 1){
					nrow = printInt;
				}
				if(j == 2){
					ncol = printInt;
				}
				printf("%d\n",printInt);
			} 
			else if(info_schema->data_schema[j].type == 'd'){
				printf("%s = ",info_schema->data_schema[j].filename_field);	
				fread(&printDouble,sizeof(double),1,fp);
				printf("%.2lf\n",printDouble);
			}
			else if(info_schema->data_schema[j].type == 'c'){
				printf("%s = ",info_schema->data_schema[j].filename_field);	
				fread(printChar,info_schema->data_schema[j].tam,1,fp);
				printf("%s\n",printChar);
			}
			else {
				printf("%s = ",info_schema->data_schema[j].filename_field);
				image = conversion_int_to_string(fp,nrow*ncol,info_schema->data_schema[j].tam*8,info_schema->data_schema[j].tam);
				printf("%s\n",image);
				free(image);
			}
		}
	}	

	free(printChar);
}

/*
Ordenação dos dist's
Parâmetros: double *, int *, int
Retorno: nenhum
*/
void sort(double *vector, int *offset, int n){

    int i,j, swpInt;
	double swpDouble;

        for(i=1;i<n;i++){
                for(j=0;j<n-i;j++){
                        if(vector[j] > vector[j+1]){

				swpDouble = vector[j];
				vector[j] = vector[j+1];
				vector[j+1] = swpDouble;
		
				swpInt = offset[j];
				offset[j] = offset[j+1];
				offset[j+1] = swpInt;        
                        }
                }
        }
}

/*
Procurando pelos n vizinhos mais próximos
Parâmetro: FILE *,INFO_SCHEMA *, INFO_DATA *, int, int
Retorno: nenhum
*/
void search_knn(FILE *fp,INFO_SCHEMA *info_schema, INFO_DATA *info_data, int neighbors, int control){
	
	int i, pos = 0, *offset = NULL, total = 0;
	double *vector = NULL, dist;	

	//Alocando um vetor que conterá todos os dist
	vector = (double*) malloc(sizeof(double) * info_data->amount_reg); 

	//Alocando um vetor que conterá os offsets
	offset = (int*) malloc(sizeof(int) * info_data->amount_reg);
	
	//Calculando o total de bytes do registro	
	for(i=0;i<info_schema->amount_field;i++){
		total += info_schema->data_schema[i].tam;
	}

	//Primeira posição do dist	
	pos = total - sizeof(double);
		
	//Percorrendo todos os dist a procura do menor
	for(i=0;i<info_data->amount_reg;i++){
		//Movendo o cursor para o próximo dist	
		fseek(fp,pos,SEEK_SET);		

		//Lendo o dist
		fread(&dist,sizeof(double),1,fp);
		
		//Armazenando o dist
		vector[i] = dist;
		
		//Armazenando o offset
		offset[i] = total * i;	

		//Arrumando a posição
		pos = pos + total;
	}
	
	//Ordenação
	sort(vector,offset,info_data->amount_reg);

	if(control == 1){
		dump_nn(fp,info_schema,offset,neighbors);
	}
	else{
		dump_class(fp,info_schema,offset);	
	}

	//Liberando o vetor
	free(vector);
	free(offset);
}

/*
Classificação das imagens
Parâmetros: INFO_SCHEMA *, INFO_DATA *, IMAGE *, int
Retorno: nenhum
*/
void ocr_dump_nn(INFO_SCHEMA *info_schema, INFO_DATA *info_data, IMAGE *img, int control){
	
	int neighbors, i;
	char aux;
	double dist;
	FILE *fp = NULL;
	unsigned char *image = NULL;
	IMAGE *cmp = (IMAGE*) malloc(sizeof(IMAGE));
	
	//Armazenando a quantidade de vizinhos que deve ser analisada
	scanf("%d",&neighbors);
	
	//Abertura do arquivo contendo as imagens
	fp = fopen(info_data->filename_data,"rb+");
	
	//Classificação das imagens	
	for(i=0;i<info_data->amount_reg;i++){
		
		//Ignorando o id no arquivo
		fseek(fp,sizeof(int),SEEK_CUR);
		
		//Armazenando as medidas da imagem
		fread(&cmp->nrow,sizeof(int),1,fp);
		fread(&cmp->ncol,sizeof(int),1,fp);

		//Armazenando a imagem
		image = conversion_int_to_string(fp,cmp->nrow*cmp->ncol,info_schema->data_schema[3].tam*8,info_schema->data_schema[3].tam);
		
		//Pulando a classe da imagem
		fseek(fp,2,SEEK_CUR);

		//Transformando a string em matriz
		transform(image,cmp);

		//Como a imagem já foi transformada a string já não é mais necessária
		free(image);

		//Calculando a distância
		dist = mem_dist_image(img,cmp);

		//Alterando o dist
		fwrite(&dist,sizeof(double),1,fp);
		
		//Desalocando a imagem de comparação
		destroy_img(cmp);	
	
		//Alocando a imagem para a próxima comparação
		cmp = (IMAGE*) malloc(sizeof(IMAGE));
	}	
	
	//Desalocação da imagem
	destroy_img(img);

	//Desalocando a imagem de comparação
	free(cmp);
	
	//Movendo cursor para o início
	fseek(fp,0,SEEK_SET);	

	//Procurando pelos n vizinhos mais próximos
	search_knn(fp,info_schema,info_data,neighbors,control);
	
	//Fechando o arquivo
	fclose(fp);
}
