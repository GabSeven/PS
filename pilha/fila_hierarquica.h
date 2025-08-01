#ifndef __FILA_HIERARQUICA_H__
#define __FILA_HIERARQUICA_H__

#include "fila_dinamica.h" // usa a fila dinâmica como base

#define MAX_NIVEIS 256 // 256 níveis de prioridade

// Estrutura da fila hierárquica: vetor de filas
struct fila_hierarquica {
    struct fila niveis[MAX_NIVEIS]; // cada posição representa uma fila de prioridade
};

// Inicializa todas as filas dentro da fila hierárquica
void inicializa_fila_hierarquica(struct fila_hierarquica *fh);

// Insere um elemento na fila do nível de prioridade especificado
// Retorna 1 se inseriu com sucesso, 0 caso contrário
int enfileira_fh(struct fila_hierarquica *fh, Pixel dado, int prioridade);

// Remove e retorna o elemento de maior prioridade da fila hierárquica
Pixel desenfileira_fh(struct fila_hierarquica *fh);

// Retorna 1 se a fila hierárquica está completamente vazia
int fila_hierarquica_vazia(struct fila_hierarquica *fh);

// Imprime todas as filas da hierarquia, da mais prioritária para a menos
void escreve_fila_hierarquica(struct fila_hierarquica *fh);

#endif
