#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	int i,j;
	
	FILE *fp = fopen("data","r");
	FILE *w = fopen("result","w");
	
	fseek(fp,0,SEEK_END);
	long size = ftell(fp);
	fseek(fp,0,SEEK_SET);

	char *buffer = (char*) malloc(sizeof(char) * size);
	char *tmp = (char*) malloc(sizeof(char) * size);
	fread(buffer,sizeof(char),size,fp);
	
	for(i=0,j=0;i<size;i++){
		if(buffer[i] == ' '){
			if(buffer[i-1] != ' '){
				tmp[j++] = buffer[i];	
			}	
		}
		else{
			tmp[j++] = buffer[i];	
		}
	}
	tmp[j] = '\0';
	fwrite(tmp,sizeof(char),j,w);
	
	free(buffer);
	free(tmp);
	fclose(fp);
	fclose(w);

	return 0;
}
