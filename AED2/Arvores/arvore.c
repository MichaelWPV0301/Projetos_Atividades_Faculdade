#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int *Vetor;

void criaVetor(Vetor *vetor, int tamanho)
{
    printf("LIBERA POHA");
    *vetor = calloc(tamanho, sizeof(int));
    printf("liberou");
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
    Arvore *a = (Arvore *)malloc(sizeof(Arvore));
    criaArvore(a);
    for (int x = 0; x < tamVet; x++)
    {
        insereArvoreBinaria(a->raiz, *v[x]);
    }
    return a;
}

void insereArvoreLeft(TipoNo *no, int valor)
{
    TipoNo *novo = (TipoNo *)malloc(sizeof(TipoNo));
    no->esquerda = novo;
    novo->valor = valor;
    novo->direita = NULL;
    novo->esquerda = NULL;
}

void insereArvoreRight(TipoNo *no, int valor)
{
    TipoNo *novo = (TipoNo *)malloc(sizeof(TipoNo));
    no->direita = novo;
    novo->valor = valor;
    novo->direita = NULL;
    novo->esquerda = NULL;
}

TipoNo *buscaElemento(Arvore *arvore, int nivel, int filho)
{
    int filhos = pow(2, nivel - 1);
    TipoNo *no = arvore->raiz;

    if (filho > filhos)
    {
        return arvore->raiz;
    }
    while (nivel > 2)
    {
        filhos = filhos / 2;
        if (filho <= filhos / 2)
        {
            no = no->esquerda;
        }
        else
        {
            no = no->direita;
        }
        if (!no)
            return NULL;
        nivel--;
    }
    return no;
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
    printf("oi");
    populaVetorAleatorioOrdenado(v, 30);
    printf("Vetor Aletatorio: ");
    mostraVetor(v, 30);
    arvore2 = transformaVetorArvoreBinaria(&v, 30);
    printf("Mostrar Ordenado: ");
    mostraArvoreOrdenada(arvore2->raiz);
    printf("\nMostrar Posfixada: ");
    mostraPosfixada(arvore2->raiz);
    printf("\nMostrar Prefixada: ");
    mostraPreFixada(arvore2->raiz);
    printf("\n");
}