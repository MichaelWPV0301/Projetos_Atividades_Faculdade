#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TipoNo
{
    int valor;
    struct TipoNo *esquerda;
    struct TipoNo *direita;
} TipoNo;

typedef struct Arvore
{
    TipoNo *raiz;
} Arvore;

typedef int *Vetor;

void criaVetor(Vetor *vetor, int tamanho)
{
    *vetor = calloc(tamanho, sizeof(int));
}

void liberaVetor(Vetor *vetor)
{
    free(*vetor);
}

void populaVetorAleatorioOrdenado(Vetor vetor, int tamanho)
{
    vetor[0] = 0;
    for (int i = 1; i < tamanho; i++)
    {
        vetor[i] = vetor[i - 1] + abs(rand() % 10); // Garante que os valores fiquem em ordem crescente
    }
}

void mostraVetor(Vetor vetor, int tamanho)
{
    printf("[");
    if (tamanho)
    {
        printf("%d", vetor[0]);
    }
    for (int x = 1; x < tamanho; x++)
    {
        printf(", %d", vetor[x]);
    }
    printf("]");
}

void criaNo(TipoNo *no, int valor)
{
    no->esquerda = NULL;
    no->direita = NULL;
    no->valor = valor;
}

void criaArvore(Arvore *arvore)
{
    arvore->raiz = NULL;
}

TipoNo *insereArvoreBinaria(TipoNo *raiz, int valor)
{
    if (raiz == NULL)
    {
        TipoNo *raizNova = (TipoNo *)malloc(sizeof(TipoNo));
        raizNova->direita = NULL;
        raizNova->esquerda = NULL;
        raizNova->valor = valor;
        return raizNova;
    }
    if (valor <= raiz->valor)
    {
        raiz->esquerda = insereArvoreBinaria(raiz->esquerda, valor);
    }
    else
    {
        raiz->direita = insereArvoreBinaria(raiz->direita, valor);
    }
    return raiz;
}

Arvore *transformaVetorArvoreBinaria(Vetor *v, int tamVet)
{
    Arvore *a = (Arvore *) malloc(sizeof(Arvore));
    criaArvore(a);
    for (int x = 0; x < tamVet; x++)
    {
        a->raiz = insereArvoreBinaria(a->raiz, (*v)[x]);
    }
    return a;
}


void mostraArvoreOrdenada(TipoNo *raiz)
{
    if (raiz != NULL)
    {
        mostraArvoreOrdenada(raiz->esquerda);
        printf("%d ", raiz->valor);
        mostraArvoreOrdenada(raiz->direita);
    }
}
void mostraPosfixada(TipoNo *raiz)
{
    if (raiz != NULL)
    {
        mostraArvoreOrdenada(raiz->esquerda);
        mostraArvoreOrdenada(raiz->direita);
        printf("%d ", raiz->valor);
    }
}
void mostraPreFixada(TipoNo *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->valor);
        mostraArvoreOrdenada(raiz->esquerda);
        mostraArvoreOrdenada(raiz->direita);
    }
}

int main()
{
    int valor;
    Arvore arvore;
    criaArvore(&arvore);
    valor = 0;
    printf("\nQual valor do novo nó você quer adicionar na árvore binária? [-1] se não quiser: ");
    scanf("%d", &valor);
    while (valor != -1)
    {
        arvore.raiz = insereArvoreBinaria(arvore.raiz, valor);
        printf("\nQual valor do novo nó você quer adicionar na árvore binária? [-1] se não quiser: ");
        scanf("%d", &valor);
    }
    printf("Mostrar Ordenado: ");
    mostraArvoreOrdenada(arvore.raiz);
    printf("\nMostrar Posfixada: ");
    mostraPosfixada(arvore.raiz);
    printf("\nMostrar Prefixada: ");
    mostraPreFixada(arvore.raiz);
    printf("\n");






    Arvore *arvore2;
    Vetor v;
    printf("Criando vetor aleatório...\n");
    criaVetor(&v, 30);
    populaVetorAleatorioOrdenado(v, 30);
    printf("Vetor Aletatorio: ");
    mostraVetor(v, 30);
    arvore2 = transformaVetorArvoreBinaria(&v, 30);
    printf("\n\nMostrar Ordenado: ");
    mostraArvoreOrdenada(arvore2->raiz);
    printf("\n\nMostrar Posfixada: ");
    mostraPosfixada(arvore2->raiz);
    printf("\n\nMostrar Prefixada: ");
    mostraPreFixada(arvore2->raiz);
    printf("\n");
}