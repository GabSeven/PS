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
int enfilera(struct fila *f, Pixel d){
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
