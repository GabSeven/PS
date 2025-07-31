#include <stdio.h>
#include <stdlib.h>
#include "fila_dinamica.h"

/*recebe uma fila e inicializa ela, numa fila vazia*/
void inicializa_fila(struct fila *f){
	f->primeiro = NULL;
	f->ultimo = NULL;
}

/*retorna 1 se a fila está vazia, ou 0 caso contrário*/
int fila_vazia(struct fila *f){
	if (f->primeiro == NULL){return 1;};
	return 0;
}

/*Insere d no final da fila. Retorna 1 se foi possível inserir, 0 caso contrário
Não se esqueça de laterar o tipo de dado a ser inserido na fila*/
int enfilera(struct fila *f, int d){
	struct no_fila *novo = malloc(sizeof(struct no_fila));
	novo->dado = d;
	novo -> prox = NULL;
	if (fila_vazia(f)){
		f->primeiro = novo;
		f->ultimo = novo;
	}else {
		f->ultimo->prox = novo;
		f->ultimo =novo;
	}
	return 1; // o que seria o caso de nao conseguir enfileirar(return 0)??
}

/*Remove o primeiro da fila. Retorna 1 se foi possível remover, 0 caso contrário*/
int desenfilera(struct fila *f){
	if (fila_vazia(f)){
		return 0;
	}
	struct no_fila *remover = f->primeiro;
	f->primeiro = f->primeiro->prox;
	if (f->primeiro==NULL){
		f->ultimo=NULL;
	}
	free(remover);
	return 1;
}

/*Obtém os dados do primeiro elemento da fila e amazena em ret.
Além disso, a função retorna 1 quando conseguiu obter o primeiro, ou 0 quando não foi
possível obter o primeiro elemento (fila vazia) */
int primeiro(struct fila *f, int *ret){
	if (fila_vazia(f)){return 0;}
	*ret = f->primeiro->dado;
	return 1; // é assim ? n tinha q retornar esse ret
}

/*verifica se o valor v está presente no campo dado de algum nó da fila*/
int busca_fila(struct fila *f, int v){
	struct no_fila *atual = f->primeiro;
	while (atual != NULL){
		if (atual->dado == v){
			return 1;
		}
		atual = atual->prox;
	}
	return 0;
}

/*imprime o conteúdo da fila com o valor mais a esquerda sendo o primeiro da fila*/
void escreve_fila(struct fila *f){
	struct no_fila *atual = f->primeiro;
    printf("Fila: ");
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}