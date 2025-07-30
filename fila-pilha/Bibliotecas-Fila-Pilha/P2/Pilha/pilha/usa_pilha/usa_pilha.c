#include "pilha.h"
#include <stdio.h>

int main(){
    struct pilha p;
    int r;
    inicializa_pilha(&p);
    int numeros[]={8,2,3,5,1};
    for(int i=0;i<5;i++){
        empilha(&p, numeros[i]);
        mostra_pilha(&p);
    }
    desempilha(&p,&r);
    desempilha(&p,&r);
    mostra_pilha(&p);
    r = topo(&p);
    printf("topo: %d\n", r);
    mostra_pilha(&p);
}
