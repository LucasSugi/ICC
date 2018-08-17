/*Algoritmo que simula um campo minado
 *Nome: Lucas Yudi Sugi
 *Número USP: 9293251
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função responsável pela leitura do nome do arquivo
char *read_file(){
	
	size_t num;
	char *filename = NULL;
	
	//Armazenando a string na variável filename		
	getline(&filename,&num,stdin);

	//Eliminando a quebra de linha na string (caractere '\n')
	num = strlen(filename);
	filename[num-1] = '\0';
	
	return filename;
}

//Função responsável pela leitura do conteúdo do arquivo
char **content_file(char *filename, int *height, int *width){
	
	int i,j;	
	FILE *fp;
	char aux;
	char **content = NULL;
	
	//Abrindo o arquivo para leitura
	fp = fopen(filename,"r");  
	
	//Lendo o tamanho da altura e largura do campo minado(leitura feita até o final do arquivo)
	do{
		aux = fgetc(fp);
		//Ignorando os enters
		if(aux == '\n'){
			(*height)++;
		} 
		if(aux == '*' || aux == '.'){	
			(*width)++;
		}

	} while(!feof(fp));

	//Como a largura "contou" todos os caracteres presentes no conteúdo do arquivo, basta dividi-lá pela quantidade da altura
	//Que iremos encontrar o valor da largura
	(*width) = (*width)/(*height);
	
	//Criação da matriz que receberá o conteúdo do arquivo -> Número de linhas
	content = (char**) malloc(sizeof(char*)*(*height));
	
	//Criação da matriz que receberá o conteúdo do arquivo -> Número de colunas
	for(i=0;i<(*height);i++){
		content[i] = (char*) malloc(sizeof(char)*(*width));
	}
	
	//Zerando variáveis para o laço while
	i = 0;
	j = 0;
	
	//Movendo o cursor do arquivo para o início
	fseek(fp,0,SEEK_SET);
	
	//Passando o conteúdo do arquivo para a matriz
	do{
		aux = fgetc(fp);
		//Sempre que é encontrado um \n é "pulado uma linha na matriz
		if(aux == '\n'){
			i++;
			j = 0;		
		}
		if(aux == '*' || aux == '.'){	
			content[i][j] = aux;
			j++;
		}

	} while(!feof(fp));

	//Fechando o arquivo
	fclose(fp);

	return content;
}

/*Essa função é executada quando o usuário digita a opção 1 do menu do opções da main,
ela é responsável por imprimir o campo minado na tela*/
void printMatrix(char **content, int height, int width){

	int i,j;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
				printf("%c",content[i][j]);
		}
		printf("\n");
	}
}

/*Subfunção da opção 2 na qual é procurado por minas em volta do quadrado
	
A busca funcionará da seguinte maneira: Tendo as coordenadas do quadrado, retiramos em uma unidade o valor
dessas coordenadas para levá-lo a um quadrante imaginário. Desse modo, é percorrido um quadrante 3x3 sempre.
Assim, conseguimos olhar os quadrados adjascentes para procurar por minas. Contudo, com esse metódo, iríamos 
procurar por posições com valor negativo, mas isso é resolvido utilizando uma condição
*/
void search_mine(char **content,int height,int width, int x, int y){
	
	int i,j,posX,posY;
	int counter = 0;

	//Armazenando as coordendas iniciais do quadrado
	posX = x;
	posY = y;
	
	//Levando as coordenadas para a primeira posição do quadrante
	x--;	
	y--;
	
	//Procura nos quadrados adjascentes por bombas
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			if(i>=0 && i<height && j>=0 && j<width){
				if(content[i][j] == '*'){
					counter++;	
				}
			}
		}	
	}
	
	/*Caso o contador seja maior do que zero isso significa que há bombas adjascentes em relação ao quadrado		
	logo é necessário colocar esse valor no quadrado inicial*/
	if(counter>0){
		content[posX][posY] = counter + 48;
	}
}

/*Essa função é executada quando o usuário digita a opção 2 do menu do opções da main,
ela é responsável por colocar dicas no campo minado*/
void tips_minefield(char **content, int height, int width){

	int i,j;
	
	//Um espaçõ vazio é procurado no campo, quando for encontrada é chamado uma outra função
	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			if(content[i][j] != '*'){
				search_mine(content,height,width,i,j);
			}
		}
	}
}

/*Subfunção da opção 3 na qual o quadrado revelado é uma dica e é necessário imprimir o campo minado
Note que somente a dica é impressa como revelada , o resto é impresso com um X(não revelado) */
void print_minefield(char **content, int height, int width, int x, int y){

	int i,j;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			if(i == x && j == y){
				printf("%c",content[i][j]);				
			}else{
				printf("X");		
			}
		}
		printf("\n");
	}			
}

/*As dicas a serem escondidas da função hide_square2 só não serão reveladas quando não houver espaços vazios em sua volta
para isso existe essa função que irá procurar em sua volta por tais espaçoes*/
void hide_square3(char **content, int height, int width, int x, int y){

	int counter = 0;
	int posX,posY,i,j;

	//Armazenar a posição inicial
	posX = x;
	posY = y;
	
	//Ponto de partida da coordenada
	x--;
	y--;
	
	//Procura nos quadrados adjascentes por espaços vazios
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			if(i>=0 && i<height && j>=0 && j<width){
				if(content[i][j] == '.'){
					counter = 1;
				}
			}
		}	
	}
	//Caso o counter seja igual a 0, significa que não há espaços vazios em volta logo a dica deve ser escondida
	if(counter == 0){
		content[posX][posY] = 'X';
	}
}

//Subfunção 3 das opções na qual após revelar os quadrados é preciso esconder as minas e as dicas já que não foram reveladas
void hide_square2(char **content, int height, int width){
	
	int i,j;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			if(content[i][j] == '*'){
				content[i][j] = 'X';
			} 
			if(content[i][j] != '.' && content[i][j] != 'X'){
				hide_square3(content,height,width,i,j);				
			}
		}
	}
}

//Subfunção 3 das opções na qual para facilitar a lógica do algoritmo é trocado todos os espaços vazio por X(não revelado)
void hide_square(char **content, int height, int width){
	
	int i,j;

	for(i=0;i<height;i++){
		for(j=0;j<width;j++){
			if(content[i][j] == '.'){
				content[i][j] = 'X';
			} 
		}
	}
}

//Subfunção 3 das opções que será responsável por revelar quadrados no campo minado
void reveal_square(char **content, int height, int width,int x, int y){

	int i,j;
	
	//Ponto de partida da coordenada
	x--;
	y--;
	
	//Procura nos quadrados adjascentes por quadrados não revelados
	for(i=x;i<x+3;i++){
		for(j=y;j<y+3;j++){
			if(i>=0 && i<height && j>=0 && j<width){
				if(content[i][j] == 'X'){
					content[i][j] = '.';
					reveal_square(content,height,width,i,j);	
				}
			}
		}	
	}	
}

/*Essa função é executada quando o usuário digita a opção 3 do menu do opções da main,
ela é responsável por revelar um quadrado*/
void revealing_square(char **content, int height, int width ){

	int x,y;

	//Lendo as duas coordenadas do quadrado a ser revelado	
	scanf("%d%d",&x,&y);
	
	//Procurando pelas dicas
	tips_minefield(content,height,width);
	
	//Caso o quadrado seja uma mina, é impresso o campo minado para dizer que o usuário perdeu
	if(content[x][y] == '*'){
		printMatrix(content,height,width);			
	}  
	//Caso o quadrado seja uma dica, é impresso o campo minado com a dica revelada e o resto não revelado
	else if(content[x][y]>=49 && content[x][y]<=57) {
		print_minefield(content,height,width,x,y);				
	} 
	/*Caso o quadrado esteja vazio, estão é liberada a área adjascentes até encontrar uma borda ou uma dica
	e o campo minado é impresso */
	else if(content[x][y] == '.'){
		hide_square(content,height,width);
		reveal_square(content,height,width,x,y);			
		hide_square2(content,height,width);			
		printMatrix(content,height,width);
	}
}

//Função responsável por desalocar a matriz
void freeMatrix(char **content, int height){

	int i;

	for(i=0;i<height;i++){
		free(content[i]);
	}

	free(content);	
}

int main(int argc, char *argv[]){
	
	int option;
	int width = 0;
	int height = 0;
	char aux;
	char *filename = NULL;
	char **content = NULL;

	//Lendo a opção que o usuário deseja
	scanf("%d",&option);

	//Scanf necessário para pegar o caractere '\n'
	scanf("%c",&aux);
		
	//Leitura do nome do arquivo
  	filename = read_file();	
	
	//Leitura do conteúdo do arquivo
	content = content_file(filename,&height,&width);

	//Menu de opções
	switch(option){
		case 1: printMatrix(content,height,width); break;
		case 2: tips_minefield(content,height,width); printMatrix(content,height,width); break;
		case 3: revealing_square(content,height,width); break;
	}
	
	//Liberando o conteúdo da matriz
	freeMatrix(content,height);
	
	//Liberando o nome do arquivo
	free(filename);

	return 0;
}
