#include "../include/avl.h"
#include "../include/vet.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct ArvoreAvl
{
    struct ArvoreAvl *esquerda;
    struct ArvoreAvl *direita;
    int dado;
    int altura;
} ArvoreAvl;

void inicializaAvl(ArvoreAvl **raiz)
{
    *raiz = NULL;
}

void caminhaPos(ArvoreAvl *raiz)
{
    if (raiz == NULL)
        return;
    caminhaPos(raiz->esquerda);
    caminhaPos(raiz->direita);
    printf("%d ", raiz->dado);
}

void caminhaPre(ArvoreAvl *raiz)
{
    if (raiz == NULL)
        return;
    printf("%d ", raiz->dado);
    caminhaPre(raiz->esquerda);
    caminhaPre(raiz->direita);
}

void caminhaCentral(ArvoreAvl *raiz)
{
    if (raiz == NULL)
        return;
    caminhaCentral(raiz->esquerda);
    printf("%d ", raiz->dado);
    caminhaCentral(raiz->direita);
}

void atualizar_altura(ArvoreAvl *avl)
{
    if (avl != NULL)
    {
        avl->altura = 1 + max(altura(avl->esquerda), altura(avl->direita));
    }
}

int altura(ArvoreAvl *arvoreAvl)
{
    if (arvoreAvl == NULL)
    {
        return 0;
    }
    return arvoreAvl->altura;
}

int fator_balanceamento(ArvoreAvl *arvoreAvl)
{
    if (arvoreAvl == NULL)
        return 0;
    return altura(arvoreAvl->direita) - altura(arvoreAvl->esquerda);
}

int max(int ha, int hb)
{
    if (ha > hb)
    {
        return ha;
    }
    return hb;
}

ArvoreAvl *rotacao_simples_direita(ArvoreAvl *arvore1)
{
    ArvoreAvl *arvore2 = arvore1->esquerda;
    arvore1->esquerda = arvore2->direita;
    arvore2->direita = arvore1;

    atualizar_altura(arvore1);
    atualizar_altura(arvore2);

    return arvore2;
}

ArvoreAvl *rotacao_simples_esquerda(ArvoreAvl *arvore1)
{
    ArvoreAvl *arvore2 = arvore1->direita;
    arvore1->direita = arvore2->esquerda;
    arvore2->esquerda = arvore1;

    atualizar_altura(arvore1);
    atualizar_altura(arvore2);

    return arvore2;
}

ArvoreAvl *rotacao_dupla_direita(ArvoreAvl *arvore1)
{
    arvore1->esquerda = rotacao_simples_esquerda(arvore1->esquerda);
    return rotacao_simples_direita(arvore1);
}

ArvoreAvl *rotacao_dupla_esquerda(ArvoreAvl *arvore1)
{
    arvore1->direita = rotacao_dupla_direita(arvore1);
    return rotacao_simples_esquerda(arvore1);
}

ArvoreAvl *inserirAvl(ArvoreAvl *avl, int chave)
{
    if (avl == NULL)
    {
        ArvoreAvl *novo = (ArvoreAvl *)malloc(sizeof(ArvoreAvl));
        novo->dado = chave;
        novo->altura = 1;
        novo->direita = NULL;
        novo->esquerda = NULL;
        return novo;
    }
    if (avl->dado > chave)
    {
        avl->esquerda = inserirAvl(avl->esquerda, chave);
    }
    else if (avl->dado < chave)
    {
        avl->direita = inserirAvl(avl->direita, chave);
    }
    else
    {
        return avl;
    }
    atualizar_altura(avl);
    int fb = fator_balanceamento(avl);
    if (fb > 1 && chave > avl->direita->dado)
    {
        return rotacao_simples_esquerda(avl);
    }
    if (fb < -1 && chave < avl->esquerda->dado)
    {
        return rotacao_simples_direita(avl);
    }
    if (fb > 1 && chave < avl->direita->dado)
    {
        return rotacao_dupla_esquerda(avl);
    }
    if (fb < -1 && chave > avl->esquerda->dado)
    {
        return rotacao_simples_direita(avl);
    }
    return avl;
}

void vetorEmAvl(Vetor vetor, ArvoreAvl **ptrRaiz, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        *ptrRaiz = inserirAvl(*ptrRaiz, vetor[i]);
    }
}
