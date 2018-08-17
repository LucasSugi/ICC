#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"
#include "arvore_binaria.h"
#include "heap.h"

int main(int argc, char** argv) {
	
	char *msg = "SUSIE SAYS IT IS EASY";
	char codificado[1000];
	char decodificado[1000];

	HUFFMAN *huffman = criar_huffman();

	criar_arvore_huffman(huffman, msg);
	criar_codigo(huffman);

	codificar(huffman, msg, codificado);
	decodificar(huffman, codificado, decodificado);
  
	printf("codificacao: %s\n", codificado);
	printf("decodificacao: %s\n", decodificado);

	apagar_huffman(&huffman);

  return 0;
}
