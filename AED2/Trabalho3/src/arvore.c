#include "../include/arvore.h"
#include "../include/vet.h"
#include <stdlib.h>
#include <stdio.h>

// Estrutura que representa um nó da árvore binária
typedef struct ArvoreBin
{
    struct ArvoreBin *esquerda; // ponteiro para subárvore esquerda
    struct ArvoreBin *direita;  // ponteiro para subárvore direita
    int dado;                   // valor armazenado no nó
} ArvoreBin;

/**
 * Calcula a altura de uma árvore binária.
 * Retorna 0 se a árvore for vazia.
 */
int altura(ArvoreBin *arvore){
    if(arvore == NULL)
    {
        return 0;
    }
    else{
        int alt_Esq = altura(arvore->esquerda);
        int alt_Dir = altura(arvore->direita);
        int alt;
        if(alt_Esq > alt_Dir){
            alt = alt_Esq;
        }
        else{
            alt = alt_Dir;
        }
        return 1 + alt;
    }
}

/**
 * Inicializa uma árvore binária, definindo o ponteiro da raiz como NULL.
 */
void inicializa(ArvoreBin **raiz)
{
    *raiz = NULL;
}

/**
 * Insere um valor em uma árvore binária de forma iterativa.
 * Permite valores duplicados.
 */
void insereArvoreBinaria(ArvoreBin **ptrRaiz, int valor)
{
    ArvoreBin *aux = *ptrRaiz;
    while ((aux))
    {
        if (aux->dado > valor)
        {
            ptrRaiz = &(aux->esquerda);
        }
        else
        {
            ptrRaiz = &(aux->direita);
        }
        aux = *ptrRaiz;
    }

    *ptrRaiz = (ArvoreBin *)malloc(sizeof(ArvoreBin));
    inicializa(&((*ptrRaiz)->esquerda));
    inicializa(&((*ptrRaiz)->direita));
    (*ptrRaiz)->dado = valor;
}

/**
 * Busca um valor em uma árvore binária.
 * Retorna o ponteiro para o nó encontrado ou NULL se não existir.
 */
ArvoreBin *buscaArvoreBin(ArvoreBin *raiz, int dado)
{
    ArvoreBin *aux = raiz;
    while (aux != NULL)
    {
        if (aux->dado > dado)
        {
            aux = aux->esquerda;
        }
        else if (aux->dado < dado)
        {
            aux = aux->direita;
        }
        else
        {
            return aux;
        }
    }
    return NULL;
}

/**
 * Percorre a árvore em pós-ordem (esquerda, direita, raiz) e imprime os valores.
 */
void caminhaPos(ArvoreBin *raiz)
{
    if (raiz == NULL)
        return;
    caminhaPos(raiz->esquerda);
    caminhaPos(raiz->direita);
    printf("%d ", raiz->dado);
}

/**
 * Percorre a árvore em pré-ordem (raiz, esquerda, direita) e imprime os valores.
 */
void caminhaPre(ArvoreBin *raiz)
{
    if (raiz == NULL)
        return;
    printf("%d ", raiz->dado);
    caminhaPre(raiz->esquerda);
    caminhaPre(raiz->direita);
}

/**
 * Percorre a árvore em ordem central (esquerda, raiz, direita) e imprime os valores.
 */
void caminhaCentral(ArvoreBin *raiz)
{
    if (raiz == NULL)
        return;
    caminhaCentral(raiz->esquerda);
    printf("%d ", raiz->dado);
    caminhaCentral(raiz->direita);
}

/**
 * Insere todos os elementos de um vetor em uma árvore binária.
 * Se opcao == 0, permite duplicatas. Se opcao != 0, evita duplicatas.
 */
void vetorEmArvoreBin(Vetor vetor, ArvoreBin **ptrRaiz, int tam, int opcao)
{
    for (int i = 0; i < tam; i++)
    {
        if(opcao == 0)
        {
            insereArvoreBinaria(ptrRaiz, vetor[i]);
        }
        else
        {
            insereArvoreBinSemDuplicata(ptrRaiz, vetor[i]);
        }
    }
}

/**
 * Constrói uma árvore binária balanceada a partir de um vetor ordenado.
 * Usa abordagem recursiva dividindo sempre no meio.
 */
void vetorOrdenadoEmArvoreBin(Vetor vetor, ArvoreBin **ptrRaiz, int inicio, int fim)
{
    if (inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;
        insereArvoreBinaria(ptrRaiz, vetor[meio]);
        vetorOrdenadoEmArvoreBin(vetor, ptrRaiz, inicio, meio - 1);
        vetorOrdenadoEmArvoreBin(vetor, ptrRaiz, meio + 1, fim);
    }
}

/**
 * Libera toda a memória alocada pela árvore binária.
 * Faz a liberação em pós-ordem.
 */
void liberaArvore(ArvoreBin *raiz)
{
    if (raiz == NULL)
        return;
    liberaArvore(raiz->esquerda);
    liberaArvore(raiz->direita);
    free(raiz);
}

/**
 * Insere um valor em uma árvore binária **sem permitir duplicatas**.
 * Se o valor já estiver presente, a função não faz nada.
 */
void insereArvoreBinSemDuplicata(ArvoreBin **ptrRaiz, int valor)
{
    ArvoreBin *aux = *ptrRaiz;
    while ((aux))
    {
        if (aux->dado > valor)
        {
            ptrRaiz = &(aux->esquerda);
        }
        else if(aux->dado < valor)
        {
            ptrRaiz = &(aux->direita);
        }
        else {
            return; // valor já existe, não insere
        }
        aux = *ptrRaiz;
    }

    *ptrRaiz = (ArvoreBin *)malloc(sizeof(ArvoreBin));
    inicializa(&((*ptrRaiz)->esquerda));
    inicializa(&((*ptrRaiz)->direita));
    (*ptrRaiz)->dado = valor;
}

Lista buscaPorDesigualdade(ArvoreBin* ptrRaiz, unsigned modo, int coefComparador) {
    Lista resultado;
    resultado.prim = NULL;

    void busca(ArvoreBin* no){
        if (no == NULL) return;

        // Decide se insere este nó
        int inserir = 0;
        switch (modo) {
            case 0: if (no->coeficiente > coefComparador) inserir = 1; break;
            case 1: if (no->coeficiente < coefComparador) inserir = 1; break;
            case 2: if (no->coeficiente <= coefComparador) inserir = 1; break;
            case 3: if (no->coeficiente >= coefComparador) inserir = 1; break;
            default: break;
        }

        if (inserir) {
            insereNaLista(&resultado, no->numero);
        }

        // Continua a busca nos filhos
        busca(no->esq);
        busca(no->dir);
    }

    busca(ptrRaiz);

    return resultado;
}