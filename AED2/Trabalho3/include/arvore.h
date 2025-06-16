#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_iNCLUDED

#include "../include/vet.h"

// Define a estrutura opaca ArvoreBin, que será implementada no .c
typedef struct ArvoreBin ArvoreBin;

/**
 * Busca um valor em uma árvore binária.
 * Retorna um ponteiro para o nó encontrado ou NULL se não existir.
 */
ArvoreBin* buscaArvoreBin(ArvoreBin* raiz, int dado);

/**
 * Retorna a altura da árvore binária.
 */
int altura(ArvoreBin *arvore);

/**
 * Inicializa a árvore, atribuindo NULL à raiz.
 */
void inicializa(ArvoreBin** raiz);

/**
 * Insere um valor na árvore binária (permite duplicatas).
 */
void insereArvoreBinaria(ArvoreBin** ptrRaiz, int valor);

/**
 * Realiza percurso pós-ordem na árvore e imprime os valores.
 */
void caminhaPos(ArvoreBin* raiz);

/**
 * Realiza percurso pré-ordem na árvore e imprime os valores.
 */
void caminhaPre(ArvoreBin* raiz);

/**
 * Realiza percurso em-ordem (central) na árvore e imprime os valores.
 */
void caminhaCentral(ArvoreBin* raiz);

/**
 * Insere todos os elementos de um vetor na árvore binária.
 * Se opcao == 0, insere com duplicatas; se opcao != 0, evita duplicatas.
 */
void vetorEmArvoreBin(Vetor vetor, ArvoreBin** ptrRaiz, int tam, int opcao);

/**
 * Libera toda a memória alocada para a árvore binária.
 */
void liberaArvore(ArvoreBin* raiz);

/**
 * Constrói uma árvore binária balanceada a partir de um vetor ordenado.
 */
void vetorOrdenadoEmArvoreBin(Vetor vetor, ArvoreBin **ptrRaiz, int inicio, int fim);

/**
 * Insere um valor na árvore binária apenas se ele ainda não existir (sem duplicatas).
 */
void insereArvoreBinSemDuplicata(ArvoreBin** ptrRaiz, int valor);

#endif
