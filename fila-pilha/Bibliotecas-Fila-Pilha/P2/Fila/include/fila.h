/*Segundo trabalho Parte 2 - bibliotecas fila, pilha e funções para PDI*/

/*

Implementação da fila:
	- Cada nó devera conter os campos necessários para a fila usada nas
	funções de processamento de imagem.
	- A busca, inserção e remoção deverão trabalhar com esses campos;
		* No caso da busca, desenvolva somente para os campos que precisam ser buscados no algoritmo

*/

#ifndef __FILA_H__
#define __FILA_H__


/*
	Estrutura para armazenar um nó de uma fila.
	A estrutura pode armazenar todos os dados desejados ou então.
	Pode ser criada uma struct que auxiliar que guarda os dados de interesse.
	Deve se substituir a linha 16 deste arquivo pela declaração dos dados
	a serem usados.
*/

struct no_fila{
	int dado;
	struct no_fila *prox;
};

/*
	Estrutura para armazenar os ponteiros de primeiro e ultimo da lista	
*/
struct fila{
	struct no_fila *primeiro, *ultimo;
};


/*recebe uma fila e inicializa ela, numa fila vazia*/
void inicializa_fila(struct fila *f);

/*retorna 1 se a fila está vazia, ou 0 caso contrário*/
int fila_vazia(struct fila *f);

/*Insere d no final da fila. Retorna 1 se foi possível inserir, 0 caso contrário
Não se esqueça de laterar o tipo de dado a ser inserido na fila*/
int enfilera(struct fila *f, int d);

/*Remove o primeiro da fila. Retorna 1 se foi possível remover, 0 caso contrário*/
int desenfilera(struct fila *f);

/*Obtém os dados do primeiro elemento da fila e amazena em ret.
Além disso, a função retorna 1 quando conseguiu obter o primeiro, ou 0 quando não foi
possível obter o primeiro elemento (fila vazia) */
int priemiro(struct fila *f, int *ret);

/*verifica se o valor v está presente no campo dado de algum nó da fila*/
int busca_fila(struct fila *f, int v);

/*imprime o conteúdo da fila com o valor mais a esquerda sendo o primeiro da fila*/
void escreve_fila(struct fila *f);

#endif