#include <stdio.h>
#include <stdlib.h>

#define ESQUERDA 0
#define DIREITA 1

typedef struct node{
	
	int cd,md,ce,me;
	int pos;

} NODE;

void addCaminho(NODE *node, int cd,int ce, int md, int me){
	
	node[node->pos].cd = cd;
	node[node->pos].md = md;
	node[node->pos].ce = ce;
	node[node->pos].me = me;
	node->pos++;	
}

void subCaminho(NODE *node){

	node->pos--;	
	node[node->pos].cd = -1;
	node[node->pos].md = -1;
	node[node->pos].ce = -1;
	node[node->pos].me = -1;
}

void imprime(int Cd, int Md, int Ce, int Me, int ladoMargem, int anterior){
	
	int op = anterior;
	
	printf("Cd: %d\tMd: %d\tCe: %d\tMe: %d\n",Cd,Md,Ce,Me);
}

void imprimeCaminho(NODE *node){
	
	printf("Caminho\n");	
	for(int i=0;i<node->pos;i++){
		printf("Cd: %d\tMd: %d\tCe: %d\tMe: %d\n",node[i].cd,node[i].md,node[i].ce,node[i].me);
	}
	printf("\n\n\n");
}

//Busca em profundidade
int bfs(int Cd,int Md, int Ce, int Me, int ladoMargem, int anterior, NODE *node){
	
	int ret = 0;
	
	//Condição de parada do jogo
	if(Ce == 3 && Me == 3){
		imprimeCaminho(node);
		return 1;
	}
	if(Cd == 3 && Md == 3 && anterior != 0){
		return 0;
	}
	
	//Vericações para a margem a direita
	if(ladoMargem == DIREITA){
		//Travessia dos canibais
		if(anterior != 1 && Cd > 0 && ((Ce+1) <= Me || Me == 0)){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd-1,Md,Ce+1,Me,ESQUERDA,1,node);
			subCaminho(node);
		}
		if(anterior != 2 && Cd > 1 && ((Ce+2) <= Me || Me == 0)){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd-2,Md,Ce+2,Me,ESQUERDA,2,node);
			subCaminho(node);
		}
		//Travessia dos missionários
		if(anterior != 3 && Md > 0 && (Me+1) >= Ce && ((Md-1)>=Cd || Md-1 == 0)){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd,Md-1,Ce,Me+1,ESQUERDA,3,node);
			subCaminho(node);
		}
		if(anterior != 4 && Md > 1 && (Me+2) >= Ce && ((Md-2)>=Cd || Md-2 ==0)){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd,Md-2,Ce,Me+2,ESQUERDA,4,node);
			subCaminho(node);
		}
		//Travessia canibal missionário
		if(anterior != 5 && Cd>0 && Md>0 && (Ce+1)<=(Me+1) && (Cd-1)<=(Md-1)){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd-1,Md-1,Ce+1,Me+1,ESQUERDA,5,node);
			subCaminho(node);
		}
	}	
	else if(ladoMargem == ESQUERDA){
		//Travessia dos canibais
		if(anterior != 1 && Ce > 0 && ((Cd+1) <= Md || Md == 0)){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd+1,Md,Ce-1,Me,DIREITA,1,node);
			subCaminho(node);
		}
		if(anterior != 2 && Ce > 1 && ((Cd+2) <= Md || Md == 0)){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd+2,Md,Ce-2,Me,DIREITA,2,node);
			subCaminho(node);
		}
		//Travessia dos missionários
		if(anterior != 3 && Me > 0 && (Md+1) >= Cd && ((Me-1)>=Ce || Me-1 == 0)){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd,Md+1,Ce,Me-1,DIREITA,3,node);
			subCaminho(node);
		}
		if(anterior != 4 && Me > 1 && (Md+2) >= Cd && ((Me-2)>=Ce || Me-2 == 0 )){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd,Md+1,Ce,Me-1,DIREITA,4,node);
			subCaminho(node);
		}
		//Travessia canibal missionário
		if(anterior != 5 && Ce>0 && Me>0 && (Cd+1)<=(Md+1) && (Ce-1)<=(Me-1)){
			addCaminho(node,Cd,Ce,Md,Me);
			ret = bfs(Cd+1,Md+1,Ce-1,Me-1,DIREITA,5,node);
			subCaminho(node);
		}
	}

	return ret;
}

int main(int argc, char *argv[]){
	
	//Inicialização do nó	
	NODE *node = (NODE*) malloc(sizeof(NODE) * 40);
	for(int i=0;i<40;i++){
		node->cd= -1;
		node->ce= -1;
		node->md= -1;
		node->me= -1;
	}
	node->pos = 0;	

	//Criação do primeiro nó
	addCaminho(node,3,0,3,0);
	
	//Busca em profundidade
	bfs(3,3,0,0,DIREITA,0,node);
	
	free(node);

	return 0;
}
