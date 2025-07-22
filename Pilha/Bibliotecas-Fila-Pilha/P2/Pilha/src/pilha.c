#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

/*Função que inicializa a pilha*/
void inicializa_pilha(struct pilha *p){
    p->topo = NULL;
}

/*Função que vevrifica se a pilha p está vazia. Retorna 1 para o caso de
pilha vazia, 0 caso contrário*/
int pilha_vazia(struct pilha *p){
    return p->topo == NULL;
}


/*Insere valor no topo da pilha p. Retorna 1 quando conseguiu inserir, 
0 caso contrário*/
int empilha(struct pilha *p, int valor){
    struct no_pilha *novo;
    novo = (struct no_pilha *)malloc(sizeof(struct no_pilha));
    if(novo == NULL){
        return 0;
    }
    novo->dado = valor;
    novo->prox = p->topo;
    p->topo = novo;
    return 1;
}

/*Remove o topo da pilha e coloca o dado do nó do topo na variavel ret.
Além disso, retorna 1 quando foi possível desempilhar, ou 0 caso contário*/
int desempilha(struct pilha *p, int *ret){
    if(pilha_vazia(p)){
        return 0;
    }
    struct no_pilha *del = p->topo;
    *ret = del->dado;
    p->topo = del->prox;
    free(del);
    return 1;
}

/*Imprime na tela os valores na pilha, com o topo sendo o elemento mais a
esquerda*/
void mostra_pilha(struct pilha *p){
    struct no_pilha *aux = p->topo;
    while(aux != NULL){
        printf("%d ", aux->dado);
        aux = aux->prox;
    }
    printf("\n");
}


/*retorna o elemento que está no topo da pilha. Se a função for
usada quando a pilha esta vazia, ira ocorrer um erro em tempo de
execucao*/
int topo(struct pilha *p){
	return p->topo->dado;
}

/*busca pelo valor v na pilha */
int busca(struct pilha *p, int v){
    struct no_pilha *aux = p->topo;
    while(aux != NULL){
        if(aux->dado == v){
            return 1;
        }
    }
    return 0;
}

