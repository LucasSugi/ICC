/*
 * Nome: Lucas Yudi Sugi
 * Número USP: 9293251
 */
#include "opcao.h"
#include "ArrayList.h"
#include "item.h"

#include <string.h>
#include <stdio.h>

void sub(ArrayList *list){

        int pos1,pos2;
        char aux;
        ArrayList *newList;

        scanf("%d%d",&pos1,&pos2);
        scanf("%c",&aux);

        newList = sub_ArrayList(list,pos1,pos2);
        print_ArrayList(newList);
        destruct_newList(&newList);
}

void set(ArrayList *list){

        int pos,chave,valor;
        char aux;

        scanf("%d%d%d",&pos,&chave,&valor);
        scanf("%c",&aux);

        set_ArrayList(list,pos,criar_item(chave,valor));
}
void get(ArrayList *list){

        int pos;
        char aux;

        scanf("%d",&pos);
        scanf("%c",&aux);

        imprimir_item(get_ArrayList(list,pos));
}

void remover(ArrayList *list){

        int pos;
        char aux;

        scanf("%d",&pos);
        scanf("%c",&aux);

        remove_ArrayList(list,pos);
}

void index_array(ArrayList *list){

        int chave, retorno;
        char aux;

        scanf("%d",&chave);
        scanf("%c",&aux);

        retorno = index_ArrayList(list,chave);

        if(retorno != -1){
                printf("%d\n",retorno);
        }
}

void contains(ArrayList *list){

        int chave, retorno;
        char aux;

        scanf("%d",&chave);
        scanf("%c",&aux);

        retorno = contains_ArrayList(list,chave);
        retorno != -1 ? printf("1\n") : printf("0\n");
}

void add(ArrayList *list){

        int chave, valor;
        char aux;

        scanf("%d %d",&chave,&valor);
        scanf("%c",&aux);

        add_ArrayList(list,criar_item(chave,chave));
}
