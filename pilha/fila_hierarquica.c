#include <stdio.h>
#include "fila_hierarquica.h"
#include "fila_dinamica.h"

typedef struct fila Fila;
typedef struct no_fila No;

void inicializa_fila_hierarquica(struct fila_hierarquica *fh){
    for (int i = 0; i < MAX_NIVEIS; i++ ){
        inicializa_fila(&fh->niveis[i]);
    }
}

int enfileira_fh(struct fila_hierarquica *fh, Pixel dado, int prioridade) {
    if (prioridade >= 0 && prioridade < MAX_NIVEIS) {
        enfileira(&fh->niveis[prioridade], dado);
        
        return 1;
    } else {
        return 0;
    }
}

// sempre verificar se a fila esta vazia antes de executar a funcao
// Remove e retorna o elemento de maior prioridade da fila hierárquica
Pixel desenfileira_fh(struct fila_hierarquica *fh) {
    int i= 0, encontrou = 0;

    while(!encontrou && fila_vazia(&fh->niveis[i])) {
        i++;
    }

    Pixel px = fh->niveis[i].primeiro->dado;
    desenfileira(&fh->niveis[i]);
    return px;
}

// Retorna 1 se a fila hierárquica está completamente vazia
int fila_hierarquica_vazia(struct fila_hierarquica *fh) {
    int nao_encontrou = 1, i = 0;
    while (nao_encontrou && i < MAX_NIVEIS) {
        if (!fila_vazia(&fh->niveis[i])) {
            nao_encontrou = 0;
        }
        i++;
    }
    return nao_encontrou;
}


// Imprime todas as filas da hierarquia, da mais prioritária para a menos
void escreve_fila_hierarquica(struct fila_hierarquica *fh) {
    int i = 0;
    for (i = 0; i < MAX_NIVEIS; i ++) {
        if (!fila_vazia(&fh->niveis[i])) {
            printf("Fila [%d] ",i);
            escreve_fila(&fh->niveis[i]);
            printf("\n");
        }
    }
}

