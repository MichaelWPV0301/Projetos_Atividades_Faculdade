#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include "../include/vet.h" // Inclusão da definição do tipo Vetor

// Definição da estrutura da árvore AVL (incompleta aqui, completa no .c)
typedef struct ArvoreAvl ArvoreAvl;

/**
 * Retorna a altura de um nó da árvore AVL.
 */
int alturaAvl(ArvoreAvl *arvoreAvl);

/**
 * Calcula o fator de balanceamento de um nó (direita - esquerda).
 */
int fator_balanceamento(ArvoreAvl *arvoreAvl);

/**
 * Conta o número total de nós na árvore.
 */
int contaNos(ArvoreAvl* raiz);

/**
 * Retorna o maior entre dois inteiros.
 */
int max(int ha, int hb);

/**
 * Atualiza a altura de um nó com base nas alturas dos filhos.
 */
void atualizar_altura(ArvoreAvl *avl);

/**
 * Percorre a árvore em pós-ordem (esquerda, direita, raiz) e imprime os dados.
 */
void caminhaPosAvl(ArvoreAvl *raiz);

/**
 * Percorre a árvore em pré-ordem (raiz, esquerda, direita) e imprime os dados.
 */
void caminhaPreAvl(ArvoreAvl *raiz);

/**
 * Percorre a árvore em ordem central (esquerda, raiz, direita) e imprime os dados.
 */
void caminhaCentralAvl(ArvoreAvl *raiz);

/**
 * Inicializa a árvore AVL como vazia.
 */
void inicializaAvl(ArvoreAvl **raiz);

/**
 * Insere todos os elementos de um vetor na árvore AVL.
 */
void vetorEmAvl(Vetor vetor, ArvoreAvl **ptrRaiz, int tam);

/**
 * Libera toda a memória alocada para a árvore AVL.
 */
void liberaArvoreAvl(ArvoreAvl* raiz);

/**
 * Realiza uma rotação simples à direita para balancear a árvore.
 */
ArvoreAvl *rotacao_simples_direita(ArvoreAvl *arvore1);

/**
 * Realiza uma rotação simples à esquerda para balancear a árvore.
 */
ArvoreAvl *rotacao_simples_esquerda(ArvoreAvl *arvore1);

/**
 * Realiza uma rotação dupla à direita (esquerda-direita) para balancear a árvore.
 */
ArvoreAvl *rotacao_dupla_direita(ArvoreAvl *arvore1);

/**
 * Realiza uma rotação dupla à esquerda (direita-esquerda) para balancear a árvore.
 */
ArvoreAvl *rotacao_dupla_esquerda(ArvoreAvl *arvore1);

/**
 * Insere um valor na árvore AVL e realiza balanceamentos se necessário.
 */
ArvoreAvl *inserirAvl(ArvoreAvl *avl, int chave);

/**
 * Busca um valor na árvore AVL.
 */
ArvoreAvl *buscaArvoreAvl(ArvoreAvl *raiz, int dado);

#endif
