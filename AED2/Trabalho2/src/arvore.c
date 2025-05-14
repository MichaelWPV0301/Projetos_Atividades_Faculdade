#include "../include/arvore.h"
#include "../include/vet.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct ArvoreBin
{
    struct ArvoreBin *esquerda;
    struct ArvoreBin *direita;
    int dado;
} ArvoreBin;

void inicializa(ArvoreBin **raiz)
{
    *raiz = NULL;
}

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

void caminhaPos(ArvoreBin *raiz)
{
    if (raiz == NULL)
        return;
    caminhaPos(raiz->esquerda);
    caminhaPos(raiz->direita);
    printf("%d ", raiz->dado);
}

void caminhaPre(ArvoreBin *raiz)
{
    if (raiz == NULL)
        return;
    printf("%d ", raiz->dado);
    caminhaPre(raiz->esquerda);
    caminhaPre(raiz->direita);
}

void caminhaCentral(ArvoreBin *raiz)
{
    if (raiz == NULL)
        return;
    caminhaCentral(raiz->esquerda);
    printf("%d ", raiz->dado);
    caminhaCentral(raiz->direita);
}

void vetorEmArvoreBin(Vetor vetor, ArvoreBin **ptrRaiz, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        insereArvoreBinaria(ptrRaiz, vetor[i]);
    }
}
