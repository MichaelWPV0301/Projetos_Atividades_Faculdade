#include "../include/avl.h"
#include "../include/vet.h"
#include <stdlib.h>
#include <stdio.h>

// Estrutura da árvore AVL
typedef struct ArvoreAvl
{
    struct ArvoreAvl *esquerda; // Ponteiro para subárvore esquerda
    struct ArvoreAvl *direita;  // Ponteiro para subárvore direita
    int dado;                   // Valor armazenado no nó
    int altura;                 // Altura do nó na árvore
} ArvoreAvl;

// Conta o número de nós na árvore
int contaNos(ArvoreAvl* raiz) {
    if (raiz == NULL) return 0;
    return 1
         + contaNos(raiz->esquerda)
         + contaNos(raiz->direita);
}

// Inicializa a árvore AVL como vazia
void inicializaAvl(ArvoreAvl **raiz)
{
    *raiz = NULL;
}

// Percorre a árvore em pós-ordem (esquerda, direita, raiz)
void caminhaPosAvl(ArvoreAvl *raiz)
{
    if (raiz == NULL)
        return;
    caminhaPosAvl(raiz->esquerda);
    caminhaPosAvl(raiz->direita);
    printf("%d ", raiz->dado);
}

// Percorre a árvore em pré-ordem (raiz, esquerda, direita)
void caminhaPreAvl(ArvoreAvl *raiz)
{
    if (raiz == NULL)
        return;
    printf("%d ", raiz->dado);
    caminhaPreAvl(raiz->esquerda);
    caminhaPreAvl(raiz->direita);
}

// Percorre a árvore em ordem central (esquerda, raiz, direita)
void caminhaCentralAvl(ArvoreAvl *raiz)
{
    if (raiz == NULL)
        return;
    caminhaCentralAvl(raiz->esquerda);
    printf("%d ", raiz->dado);
    caminhaCentralAvl(raiz->direita);
}

// Atualiza a altura de um nó com base nas alturas dos filhos
void atualizar_altura(ArvoreAvl *avl)
{
    if (avl != NULL)
    {
        avl->altura = 1 + max(alturaAvl(avl->esquerda), alturaAvl(avl->direita));
    }
}

// Retorna a altura de um nó ou 0 se for NULL
int alturaAvl(ArvoreAvl *arvoreAvl)
{
    if (arvoreAvl == NULL)
    {
        return 0;
    }
    return arvoreAvl->altura;
}

// Calcula o fator de balanceamento (direita - esquerda)
int fator_balanceamento(ArvoreAvl *arvoreAvl)
{
    if (arvoreAvl == NULL)
        return 0;
    return alturaAvl(arvoreAvl->direita) - alturaAvl(arvoreAvl->esquerda);
}

// Retorna o maior entre dois valores inteiros
int max(int ha, int hb)
{
    if (ha > hb)
    {
        return ha;
    }
    return hb;
}

// Rotação simples à direita (para casos de desbalanceamento à esquerda)
ArvoreAvl *rotacao_simples_direita(ArvoreAvl *arvore1)
{
    ArvoreAvl *arvore2 = arvore1->esquerda;
    arvore1->esquerda = arvore2->direita;
    arvore2->direita = arvore1;

    atualizar_altura(arvore1);
    atualizar_altura(arvore2);

    return arvore2;
}

// Rotação simples à esquerda (para casos de desbalanceamento à direita)
ArvoreAvl *rotacao_simples_esquerda(ArvoreAvl *arvore1)
{
    ArvoreAvl *arvore2 = arvore1->direita;
    arvore1->direita = arvore2->esquerda;
    arvore2->esquerda = arvore1;

    atualizar_altura(arvore1);
    atualizar_altura(arvore2);

    return arvore2;
}

// Rotação dupla à direita (esquerda-direita)
ArvoreAvl *rotacao_dupla_direita(ArvoreAvl *arvore1)
{
    arvore1->esquerda = rotacao_simples_esquerda(arvore1->esquerda);
    return rotacao_simples_direita(arvore1);
}

// Rotação dupla à esquerda (direita-esquerda)
ArvoreAvl *rotacao_dupla_esquerda(ArvoreAvl *arvore1)
{
    arvore1->direita = rotacao_simples_direita(arvore1->direita);
    return rotacao_simples_esquerda(arvore1);
}

// Insere um novo nó na árvore AVL mantendo o balanceamento
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
    if (avl && avl->dado > chave)
    {
        avl->esquerda = inserirAvl(avl->esquerda, chave);
    }
    else if (avl && avl->dado < chave)
    {
        avl->direita = inserirAvl(avl->direita, chave);
    }
    else{
        return avl; // Evita inserção de duplicatas
    }

    atualizar_altura(avl);
    int fb = fator_balanceamento(avl);

    // Caso Direita Direita
    if (fb > 1 && avl->direita && chave > avl->direita->dado)
    {
        return rotacao_simples_esquerda(avl);
    }

    // Caso Esquerda Esquerda
    if (fb < -1 && avl->esquerda && chave < avl->esquerda->dado)
    {
        return rotacao_simples_direita(avl);
    }

    // Caso Direita Esquerda
    if (fb > 1 && avl->direita && chave < avl->direita->dado)
    {
        return rotacao_dupla_esquerda(avl);
    }

    // Caso Esquerda Direita
    if (fb < -1 && avl->esquerda && chave > avl->esquerda->dado)
    {
        return rotacao_dupla_direita(avl);
    }

    return avl;
}

// Busca um valor na árvore AVL
ArvoreAvl* buscaArvoreAvl(ArvoreAvl *raiz, int dado){
    ArvoreAvl *aux = raiz;
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

// Insere todos os elementos de um vetor na árvore AVL
void vetorEmAvl(Vetor vetor, ArvoreAvl **ptrRaiz, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        *ptrRaiz = inserirAvl(*ptrRaiz, vetor[i]);
    }
}

// Libera toda a memória alocada pela árvore AVL
void liberaArvoreAvl(ArvoreAvl *raiz){
    if(raiz==NULL){
        return;
    }
    liberaArvoreAvl(raiz->esquerda);
    liberaArvoreAvl(raiz->direita);
    free(raiz);
}
