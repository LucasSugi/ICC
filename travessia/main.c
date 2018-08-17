#include <stdio.h>
#include <stdlib.h>

#define DIREITA 0
#define ESQUERDA 1

typedef struct node{
	
	int ld,le,cd,ce,re,rd;
	int pos;

} NODE;

void addCaminho(int Ld,int Le, int Cd, int Ce,int Rd, int Re, NODE *node){
	
	node[node->pos].ld = Ld;
	node[node->pos].le = Le;
	node[node->pos].cd = Cd;
	node[node->pos].ce = Ce;
	node[node->pos].rd = Rd;
	node[node->pos].re = Re;
	node->pos++;
}

void subCaminho(NODE *node){
	node->pos--;
}

void imprimeCaminho(NODE *node){
	
	printf("Caminho\n");
	for(int i=0;i<node->pos;i++){
		printf("Ld: %d\tCd: %d\tRd: %d\tLe: %d\tCe: %d\tRe: %d\n",node[i].ld,node[i].cd,node[i].rd,node[i].le,node[i].ce,node[i].re);		
	}
	printf("\n\n\n");
}

int verificacaoEstado(int Ld,int Le, int Cd, int Ce,int Rd, int Re, NODE *node){
	
	for(int i=0;i<node->pos-1;i++){
		if(node[i].ld == Ld && node[i].rd == Rd && node[i].cd == Cd){
			return 0;
		}
	}
	return  1;
}

void bfs(int Ld,int Le, int Cd, int Ce,int Rd, int Re,int ladoMargem, int anterior, NODE *node){
	
	int ret;
	
	ret = verificacaoEstado(Ld,Le,Cd,Ce,Rd,Re,node);
	if(ret == 0) return;
	
	//Condicao de parada
	if(Le == 1 && Ce == 1 && Re == 1){
		imprimeCaminho(node);
		return;
	}
	
	if(ladoMargem == DIREITA){
		//Travessia lobo
		if(Ld == 1 && !(Cd == 1 && Rd == 1)){
			addCaminho(0,1,Cd,Ce,Rd,Re,node);	
			bfs(0,1,Cd,Ce,Rd,Re,ESQUERDA,1,node);
			subCaminho(node);
		}
		//Travessia cabra
		if(Cd == 1){
			addCaminho(Ld,Le,0,1,Rd,Re,node);	
			bfs(Ld,Le,0,1,Rd,Re,ESQUERDA,2,node);
			subCaminho(node);
		} 
		//Travessia repolho
		if(Rd == 1 && !(Ld == 1 && Cd == 1)){
			addCaminho(Ld,Le,Cd,Ce,0,1,node);	
			bfs(Ld,Le,Cd,Ce,0,1,ESQUERDA,3,node);
			subCaminho(node);
		}
		//Travessia sem nada
		if(anterior != 4 && !(Ld == 1 && Cd == 1) && !(Cd == 1 && Rd == 1)  ){
			bfs(Ld,Le,Cd,Ce,Rd,Re,ESQUERDA,4,node);
		}	
	}
	else if(ladoMargem == ESQUERDA){
		//Travessia lobo
		if(Le == 1 && !(Ce == 1 && Re == 1)){
			addCaminho(1,0,Cd,Ce,Rd,Re,node);	
			bfs(1,0,Cd,Ce,Rd,Re,DIREITA,1,node);
			subCaminho(node);
		}
		//Travessia cabra
		if(Ce == 1){
			addCaminho(Ld,Le,1,0,Rd,Re,node);	
			bfs(Ld,Le,1,0,Rd,Re,DIREITA,2,node);
			subCaminho(node);
		} 
		//Travessia repolho
		if(Re == 1 && !(Le == 1 && Ce == 1)){
			addCaminho(Ld,Le,Cd,Ce,1,0,node);	
			bfs(Ld,Le,Cd,Ce,1,0,DIREITA,3,node);
			subCaminho(node);
		}
		//Travessia sem nada
		if(anterior != 4 && !(Le == 1 && Ce == 1) && !(Ce == 1 && Re == 1)  ){
			bfs(Ld,Le,Cd,Ce,Rd,Re,DIREITA,4,node);
		}	
	}
}

int main(int argc, char *argv[]){

	NODE *node = (NODE*) malloc(sizeof(NODE) * 40);
	node->pos = 0;	
	
	addCaminho(1,0,1,0,1,0,node);

	bfs(1,0,1,0,1,0,DIREITA,0,node);

	free(node);

	return 0;
}
