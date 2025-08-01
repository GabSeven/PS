#include <stdio.h>
#include <stdlib.h>
#include "fila_dinamica.h"

typedef struct no_fila no_fila;

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
int enfileira(struct fila *f, Pixel d){
	struct no_fila *novo = malloc(sizeof(struct no_fila));
	novo->dado = d;
	novo->prox = NULL;
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
int desenfileira(struct fila *f){
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


/*imprime o conteúdo da fila com o valor mais a esquerda sendo o primeiro da fila*/
void escreve_fila(struct fila *f) {
	no_fila no = *f->primeiro;
	printf("{%d, %d, %d}", no.dado.linha, no.dado.coluna, no.dado.rotulo);
	
	while (no.prox != NULL){
		no = *no.prox;
		printf(" -> {%d, %d, %d}", no.dado.linha, no.dado.coluna, no.dado.rotulo);
		
	} 
}