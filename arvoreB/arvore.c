#include <stdio.h>
#include <stdlib.h>

//Nó de ordem 4
typedef struct no{
	
	int id;
	int size;	
	char *conteudo;
	struct no **filho;

} NO;

void bubble(char *vector, int n){
	
	int i,j;
	char aux;
	
	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if(vector[j] > vector[j+1]){
				aux = vector[j];
				vector[j] = vector[j+1];
				vector[j+1] = aux;	
			}	
		}
	}
}

NO* criarNo(){

	//Aloca o no na heap
	NO *no = (NO*) malloc(sizeof(NO));

	//Alocando memoria para armazenar as chaves
	no->conteudo = (char*) malloc(sizeof(char) * 4);
	for(int i=0;i<4;i++){
		no->conteudo[i] = '\0';
	}
	
	//Alocando memoria para armazenar os ponteiros
	no->filho = (NO**) malloc(sizeof(NO*) * 5);
	for(int i=0;i<5;i++){
		no->filho[i] = NULL;
	}

	//Inicializacao
	no->id = 0;
	no->size = 0;

	return no;
}

void shift(NO *no , int pos){
	
	int i = 4;
	
	//Ajuste dos ponteiros
	while(i != pos){
		no->filho[i] = no->filho[i-1];
		i--;
	}
}

NO *criarIrmao(NO *no, char *letra){
	
	//Cria o novo no
	NO* irmao = criarNo();

	//Passa o conteudo
	irmao->conteudo[0] = no->conteudo[3];
	no->conteudo[3] = '\0';
	
	//Nova chave a ser promovida
	*letra = no->conteudo[2];
	no->conteudo[2] = '\0';

	//Passar ponteiros
	irmao->filho[0] = no->filho[3];
	irmao->filho[1] = no->filho[4];
	no->filho[3] = no->filho[4] = NULL;

	//Arrumando o tamanho
	no->size = 2;
	irmao->size = 1;

	return irmao;
}

int add(NO **raiz, NO *no, char *letra,  NO **novo){
	
	int i,ret;
	NO *irmao,*pai;
	char promocao;

	if(no == NULL){
		return 0;
	}
	
	for(i=0;i<no->size;i++){
		if(*letra < no->conteudo[i]){
			break;	
		}
	}
	ret = add(raiz,no->filho[i],letra,novo);
	

	//Verificando se houve promocao
	if(ret == 1){
		return 1;
	}
	//Caso haja promocao verifica se ha espaco
	else if(no->size < 3){
		no->conteudo[no->size++] = *letra;
		bubble(no->conteudo,no->size);
		shift(no,i+1);
		no->filho[i+1] = *novo;
		*novo = NULL;
		return 1;
	
	}	
	//Se nao ha espaco realiza um split
	else{
		no->conteudo[no->size++] = *letra;	
		bubble(no->conteudo,no->size);
		shift(no,i+1);
		no->filho[i+1] = *novo;
		irmao = criarIrmao(no,letra);
		*novo = irmao;
		if(no == *raiz){
			pai = criarNo();
			pai->filho[0] = no;
			pai->filho[1] = irmao;
			*novo = NULL;
			pai->conteudo[0] = *letra;
			pai->size = 1;
			*raiz = pai;
			return 1;
		}
		return 0;
	}
}

void imprime(NO *no){

	for(int i=0;i<3;i++){
		if(no->conteudo[i] != '\0'){
			printf("%c ",no->conteudo[i]);
		}
	}
	for(int i=0;i<4;i++){
		if(no->filho[i] != NULL){
			imprime(no->filho[i]);
		}
	}
}

void deletaArvoreAux(NO *no){
	
	int i;

	if(no == NULL) return;

	for(i=0;i<4;i++){
		deletaArvoreAux(no->filho[i]);
	}
	free(no->conteudo);
	free(no->filho);
	free(no);

}

void deletaArvore(NO *no){
	deletaArvoreAux(no);
}

int main(int argc, char *argv[]){
	
	char letra;

	//No raiz inicial
	NO *raiz = criarNo();	
	NO *no = NULL;
	
	//Id inicial do no raiz
	raiz->id = 0;
	
	//C S D T A M P I B W N G U R K

	//Adicionando chaves
	letra = 'c';
	add(&raiz,raiz,&letra,&no);	
	letra = 's';
	add(&raiz,raiz,&letra,&no);	
	letra = 'd';
	add(&raiz,raiz,&letra,&no);	
	letra = 't';
	add(&raiz,raiz,&letra,&no);	
	letra = 'a';
	add(&raiz,raiz,&letra,&no);	
	letra = 'm';
	add(&raiz,raiz,&letra,&no);	
	letra = 'p';
	add(&raiz,raiz,&letra,&no);	
	letra = 'i';
	add(&raiz,raiz,&letra,&no);	
	letra = 'b';
	add(&raiz,raiz,&letra,&no);	
	letra = 'w';
	add(&raiz,raiz,&letra,&no);	
	letra = 'n';
	add(&raiz,raiz,&letra,&no);	
	letra = 'g';
	add(&raiz,raiz,&letra,&no);	
	letra = 'u';
	add(&raiz,raiz,&letra,&no);	
	letra = 'r';
	add(&raiz,raiz,&letra,&no);	
	letra = 'k';
	add(&raiz,raiz,&letra,&no);	

	imprime(raiz);

	deletaArvore(raiz);

	return 0;
}
