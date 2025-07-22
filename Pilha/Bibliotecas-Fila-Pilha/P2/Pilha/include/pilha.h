/*Segundo trabalho Parte 2 - bibliotecas fila, pilha e funções para PDI*/

/*
Implementação da fila:
	- Cada nó devera conter os campos necessários para a pilha usada nas
	funções de processamento de imagem.
	- A busca, inserção e remoção deverão trabalhar com esses campos;
		* No caso da busca, desenvolva somente para os campos que precisam ser buscados no algoritmo
*/

#ifndef __PILHA_H__
#define __PILHA_H__

/*Nó da pilha*/
struct no_pilha{
    int dado;
    struct no_pilha *prox;
};

/*Estrutura da pilha, contendo um ponteiro para o topo*/
struct pilha{
    struct no_pilha *topo;
};

/*Função que inicializa a pilha*/
void inicializa_pilha(struct pilha *p);

/*Função que vevrifica se a pilha p está vazia. Retorna 1 para o caso de
pilha vazia, 0 caso contrário*/
int pilha_vazia(struct pilha *p);

/*Insere valor no topo da pilha p. Retorna 1 quando conseguiu inserir, 
0 caso contrário*/
int empilha(struct pilha *p, int valor);

/*Remove o topo da pilha e coloca o dado do nó do topo na variavel ret.
Além disso, retorna 1 quando foi possível desempilhar, ou 0 caso contário*/
int desempilha(struct pilha *p, int *ret);

/*retorna o elemento que está no topo da pilha. Se a função for
usada quando a pilha esta vazia, ira ocorrer um erro em tempo de
execucao*/
int topo(struct pilha *p);

/*busca pelo valor v na pilha */
int busca_pilha(struct pilha *p, int v);

/*Imprime na tela os valores na pilha, com o topo sendo o elemento mais a
esquerda*/
void mostra_pilha(struct pilha *p);
#endif
