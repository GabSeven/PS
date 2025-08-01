#include <stdio.h>
#include "fila_dinamica.h"
#include "fila_hierarquica.h"
typedef struct fila Fila;
typedef struct fila_hierarquica FilaH;
// typedef struct Pixel Pixel;
// typedef struct no_fila No;


int main() {
    FilaH fH;
    inicializa_fila_hierarquica(&fH);

    // Fila f;
    // inicializa_fila(&f);
    // printf("%d",fila_vazia(&f));
    // enfilera(&fH.niveis[0], (Pixel) {1, 2, 3});

    enfilera_fh(&fH, (Pixel) {1, 2, 3}, 0);
    enfilera_fh(&fH, (Pixel) {1, 2, 3}, 0);
    enfilera_fh(&fH, (Pixel) {1, 2, 3}, 0);
    enfilera_fh(&fH, (Pixel) {1, 2, 3}, 2);

    // if (fila_vazia(&fH.niveis[0])) {
    //     printf("vazio");
    // } {

    //     printf("\nPrimeiro elemento: {%d}", fH.niveis[0].primeiro->dado.linha);
    // }

    escreve_fila_hierarquica(&fH);

    return 0;
}