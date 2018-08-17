#include <stdlib.h>

#include "huffman.h"
#include "heap.h"
#include "arvore_binaria.h"

#define TAM 500

struct huffman {
	
	ARV *arv;
	char codigo[TAM][TAM];
};

HUFFMAN *criar_huffman(){
	
	int i;
	HUFFMAN *huffman = (HUFFMAN*) malloc(sizeof(HUFFMAN));

	if(huffman != NULL){
		for(i=0;i<TAM;i++){
			huffman->codigo[i][0] = '\0';
		}		
		huffman->arv = NULL;
	}
	return huffman;
}

void apagar_huffman(HUFFMAN **huffman){
	
	apagar_arvore(&((*huffman)->arv));
	free(*huffman);
	*huffman = NULL;
}

void criar_arvore_huffman(HUFFMAN *huffman, char *msg){

	int i, freq[TAM];
	NO *no;	
	
	HEAP *heap = criar_heap();

	for(i=0;i<TAM;i++){
		freq[i] = 0;
	}

	for(i=0; msg[i] != '\0'; i++){
		freq[(int)msg[i]]++;
	}
	
	for(i=0;i<TAM;i++){
		if(freq[i] > 0){
			no = (NO*) malloc(sizeof(NO));
			no->simbolo = i;
			no->frequencia = freq[i];
			no->filhoEsq = NULL;
			no->filhoDir = NULL;
			inserir_heap(heap,no);
		}
	}
	
	while(tamanho_heap(heap) > 1){
		no = (NO*) malloc(sizeof(NO));
		no->simbolo = '#';
		no->filhoEsq = remover_heap(heap);
		no->filhoDir = remover_heap(heap);
		no->frequencia = no->filhoEsq->frequencia + no->filhoDir->frequencia;
		inserir_heap(heap,no);
	}
	

	huffman->arv = criar_arvore();
	criar_raiz(huffman->arv,remover_heap(heap));
	apagar_heap(&heap);
}

void criar_codigo_aux(HUFFMAN *huffman, NO *no, char *cod, int fim){

	int i;

	if(no != NULL){
		if(no->filhoEsq  == NULL && no->filhoDir == NULL){
			for(i=0;i<=fim;i++){
				huffman->codigo[(int)no->simbolo][i] = cod[i];
			}
			huffman->codigo[(int)no->simbolo][fim+1] = '\0';
		}
		else{
			if(no->filhoEsq != NULL){
				fim++;
				cod[fim] = '0';
				criar_codigo_aux(huffman,no->filhoEsq,cod,fim);
				fim--;
			}
			if(no->filhoDir != NULL){
				fim++;
				cod[fim] = '1';
				criar_codigo_aux(huffman,no->filhoDir,cod,fim);
				fim--;
			}
		}
	}
}

void criar_codigo(HUFFMAN *huffman){

	char codigo[TAM];
	criar_codigo_aux(huffman, huffman->arv->raiz, codigo, -1);
}

void codificar(HUFFMAN *huffman, char *msg, char *cod){

	int i,j,cod_fim;
	char *pcod;	

	cod_fim = -1;

	for(i=0; msg[i] != '\0'; i++){

		pcod = huffman->codigo[(int) msg[i]];

		for(j=0; pcod[j] != '\0';j++){
			cod_fim++;
			cod[cod_fim] = pcod[j];
		}
	}
	
	cod[cod_fim+1] = '\0';

}

int decodificar(HUFFMAN *huffman, char *cod, char *msg){
	
	int i,decod_fim;
	NO *no;

	decod_fim = -1;
	no = huffman->arv->raiz;

	for(i=0; cod[i] != '\0'; i++){
		if(cod[i] == '0'){
			no = no->filhoEsq;
		}
		else if(cod[i] == '1'){
			no = no->filhoDir;
		}
		else{
			return 0;
		}

		if(no->filhoEsq == NULL && no->filhoDir == NULL){
			decod_fim++;
			msg[decod_fim] = no->simbolo;
			no = huffman->arv->raiz;	
		}
	}

	msg[decod_fim+1] = '\0';
	return 1;
}
