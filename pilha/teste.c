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

    if (fila_vazia(&fH.niveis[0])) {
        printf("vazio");
    } {

        printf("\nPrimeiro elemento: {%d}", fH.niveis[0].primeiro->dado.linha);
    }
    // printf("\nPrimeiro elemento: {%d, %d, %d}", fH.niveis[0].primeiro->dado.linha,fH.niveis[0].primeiro->dado.coluna, fH.niveis[0].primeiro->dado.rotulo);
    // printf("\nÚltimo elemento: {%d, %d, %d}", f.ultimo->dado.linha, f.ultimo->dado.coluna, f.ultimo->dado.rotulo);
    // enfilera(&f, (Pixel) {3, 2, 1});
    // printf("\nPrimeiro elemento: {%d, %d, %d}", f.primeiro->dado.linha,f.primeiro->dado.coluna, f.primeiro->dado.rotulo);
    // printf("\nÚltimo elemento: {%d, %d, %d}", f.ultimo->dado.linha, f.ultimo->dado.coluna, f.ultimo->dado.rotulo);
    // desenfilera(&f);
    // printf("\nPrimeiro elemento: {%d, %d, %d}", f.primeiro->dado.linha,f.primeiro->dado.coluna, f.primeiro->dado.rotulo);
    // printf("\nÚltimo elemento: {%d, %d, %d}", f.ultimo->dado.linha, f.ultimo->dado.coluna, f.ultimo->dado.rotulo);
    

    return 0;
}