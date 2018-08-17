#include <stdio.h>
#include <stdlib.h>

#define MAXC1 7
#define MAXC2 5

typedef struct node{
	
	int c1,c2;	
	int pos;

} NODE;

void addCaminho(int c1, int c2, NODE *node){
	
	node[node->pos].c1 = c1;
	node[node->pos].c2 = c2;
	node->pos++;
	
}

void subCaminho(NODE *node){
	node->pos--;
}

void imprimeCaminho(NODE *node){
	printf("Caminho\n");
	for(int i=0;i<node->pos;i++){
		printf("Content c1: %d\tContent c2: %d\n",node[i].c1,node[i].c2);
	}
}

void passarConteudo(int *c1, int *c2, int max){
		
	int res;
		
	res = *c1 + *c2;
	res = res - max;
	
	if(res>=0){
		*c1 = res;
		*c2 = max;	
	}
	else{
		*c2 = *c1 + *c2;
		*c1 = 0;
	}
}

int verificaEstado(int c1, int c2, NODE *node){
	
	for(int i=0;i<node->pos-1;i++){
		if(node[i].c1 == c1 && node[i].c2 == c2){
			return 0;
		}
	}

	return 1;
}

void bfs(int c1, int c2, NODE *node){

	int ret,aux1,aux2;	

	//Verificando o estado
	ret = verificaEstado(c1,c2,node);
	if(ret == 0){ 
		return;
	}

	//Condição de parada
	if(c1 == 4 || c2 == 4){
		imprimeCaminho(node);
		return;
	}
	
	//Verificações para encher
	if(c1<MAXC1){
		//printf("1 - c1: %d\tc2: %d\n",c1,c2);
		addCaminho(MAXC1,c2,node);
		bfs(MAXC1,c2,node);
		subCaminho(node);
	}
	if(c2<MAXC2){
		//printf("2 - c1: %d\tc2: %d\n",c1,c2);
		addCaminho(c1,MAXC2,node);
		bfs(c1,MAXC2,node);
		subCaminho(node);
	}
	if(c1<MAXC1 && c2 <MAXC2){
		//printf("3 - c1: %d\tc2: %d\n",c1,c2);
		addCaminho(MAXC1,MAXC2,node);
		bfs(MAXC1,MAXC2,node);
		subCaminho(node);
	}
	//Verificações para esvaziar
	if(c1>0){
		//printf("4 - c1: %d\tc2: %d\n",c1,c2);
		addCaminho(0,c2,node);
		bfs(0,c2,node);
		subCaminho(node);
	}
	if(c2>0){
		//printf("5 - c1: %d\tc2: %d\n",c1,c2);
		addCaminho(c1,0,node);
		bfs(c1,0,node);
		subCaminho(node);
	}
	if(c1>0 && c2 >0){
		//printf("6 - c1: %d\tc2: %d\n",c1,c2);	
		addCaminho(0,0,node);
		bfs(0,0,node);
		subCaminho(node);
	}
	//Verificação para passar o conteúdo
	if(c1>0 && c2<MAXC2){
		//printf("7 - c1: %d\tc2: %d\n",c1,c2);
		aux1 = c1;
		aux2 = c2;
		passarConteudo(&aux1,&aux2,MAXC2);
		addCaminho(aux1,aux2,node);
		bfs(aux1,aux2,node);
		subCaminho(node);
	}	
	if(c2>0 && c1<MAXC1){
		//printf("8 - c1: %d\tc2: %d\n",c1,c2);
		aux1 = c1;
		aux2 = c2;
		passarConteudo(&aux2,&aux1,MAXC1);
		addCaminho(aux1,aux2,node);
		bfs(aux1,aux2,node);
		subCaminho(node);
	}
}

int main(int argc, char *argv[]){
	
	//Criação do nó
	NODE *node = (NODE*) malloc(sizeof(NODE) * 30);	
	
	//Criação do primeiro nó
	addCaminho(0,0,node);

	//Execução da busca pelo caminho
	bfs(0,0,node);	
	
	//Desalocando	
	free(node);
	
	return 0;
}
