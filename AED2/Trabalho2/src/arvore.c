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

int altura(ArvoreBin *arvore){
    if(arvore == NULL)
    {
        return 0;
    }
    else{
        int alt_Esq = altura(arvore->esquerda);
        int alt_Dir = altura(arvore->direita);
        int alt;
        if(alt_Esq>alt_Dir){
            alt = alt_Esq;
        }
        else{
            alt = alt_Dir;
        }
        return 1 + alt;
    }
}

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

void vetorEmArvoreBin(Vetor vetor, ArvoreBin **ptrRaiz, int tam, int opcao)
{
    for (int i = 0; i < tam; i++)
    {
        if(opcao==0)
        {
        insereArvoreBinaria(ptrRaiz, vetor[i]);
        }
        else
        {
        insereArvoreBinSemDuplicata(ptrRaiz, vetor[i]);
        }
    }
}

void vetorOrdenadoEmArvoreBin(Vetor vetor, ArvoreBin **ptrRaiz, int inicio, int fim)
{
    if (inicio<=fim){
        int meio = inicio + (fim-inicio)/2;
        insereArvoreBinaria(ptrRaiz, vetor[meio]);
        vetorOrdenadoEmArvoreBin(vetor, ptrRaiz, inicio, meio-1);
        vetorOrdenadoEmArvoreBin(vetor, ptrRaiz, meio+1, fim);
    }
}

void liberaArvore(ArvoreBin *raiz)
{
    if (raiz == NULL)
        return;
    liberaArvore(raiz->esquerda);
    liberaArvore(raiz->direita);
    free(raiz);
}
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
        else{return;}
        aux = *ptrRaiz;
    }

    *ptrRaiz = (ArvoreBin *)malloc(sizeof(ArvoreBin));
    inicializa(&((*ptrRaiz)->esquerda));
    inicializa(&((*ptrRaiz)->direita));
    (*ptrRaiz)->dado = valor;
}
