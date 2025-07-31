#include <stdio.h>
#include "fila_hierarquica.h"
#include "fila_dinamica.h"
typedef struct fila Fila;

void inicializa_fila_hierarquica(struct fila_hierarquica *fh){
    for (int i = 0; i < MAX_NIVEIS; i++ ){
        inicializa_fila(&fh->niveis[i]);
    }
}

int enfilera_fh(struct fila_hierarquica *fh, Pixel dado, int prioridade) {
    if (prioridade < 0 || prioridade >= MAX_NIVEIS) {
        printf("erro");
        return 0;
    } else {
        enfilera(&fh->niveis[prioridade], dado);
        return 1;
    }
}

// Remove o elemento de maior prioridade da fila hierárquica
// Retorna 1 se removeu algo, 0 se está vazia
int desenfilera_fh(struct fila_hierarquica *fh) {
    int encontrou = 0, i = 0;

    while (!encontrou && i < MAX_NIVEIS) {
        if (!fila_vazia(&fh->niveis[0])) {
            encontrou = 1;
        }
        i++;
    }

    if (encontrou) {

    } else {
        return 0;
    }
}