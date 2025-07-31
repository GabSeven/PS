/*Segundo trabalho Parte 2 - bibliotecas fila, pilha e funções para PDI*/

/*

Implementação da fila:
	- Cada nó devera conter os campos necessários para a fila usada nas
	funções de processamento de imagem.
	- A busca, inserção e remoção deverão trabalhar com esses campos;
		* No caso da busca, desenvolva somente para os campos que precisam ser buscados no algoritmo

*/

#ifndef __FILA_DINAMICA_H__
#define __FILA_DINAMICA_H__


/*
	Estrutura para armazenar um nó de uma fila.
	A estrutura pode armazenar todos os dados desejados ou então.
	Pode ser criada uma struct que auxiliar que guarda os dados de interesse.
	Deve se substituir a linha 16 deste arquivo pela declaração dos dados
	a serem usados.
*/
typedef struct {
    int linha;
    int coluna;
    int rotulo;
} Pixel;

struct no_fila{
	Pixel dado;
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
int enfilera(struct fila *f, Pixel d);

/*Remove o primeiro da fila. Retorna 1 se foi possível remover, 0 caso contrário*/
int desenfilera(struct fila *f);

#endif