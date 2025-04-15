#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vet.h"

typedef int *Vetor;

void criaVetor(Vetor* vetor, int tamanho)
{
    *vetor = calloc(tamanho, sizeof(int));
}

void liberaVetor(Vetor* vetor)
{
    free(*vetor);
}

void copiaVetor(Vetor destino, Vetor entrada, int tamanho)
{
    for (int x = 0; x < tamanho; x++)
    {
        destino[x] = entrada[x];
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

void populaVetorAleatorio(Vetor vetor, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = rand();
    }
}

void populaVetorAleatorioOrdenado(Vetor vetor, int tamanho)
{
    vetor[0] = 0;
    for (int i = 1; i < tamanho; i++)
    {
        vetor[i] = vetor[i - 1] + abs(rand() % 10);
    }
}

int buscaSequencialVetor(Vetor vetor, int valor, int tamanho)
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        if (vetor[i] == valor)
        {
            return i;
        }
    }
    return -1;
}

int buscaBinariaVetor(Vetor vetor, int valor, int tamanho)
{
    double calculaDesvioPadrao(double *vetor, double media, int tamanho);
    int inicio, meio, fim;
    inicio = 0;
    fim = tamanho - 1;
    while (inicio <= fim)
    {
        meio = inicio + (fim - inicio) / 2;
        if (vetor[meio] < valor)
        {
            inicio = meio + 1;
        }
        else if (vetor[meio] > valor)
        {
            fim = meio - 1;
        }
        else
        {
            return meio;
        }
    }
    return -1;
}

void bolha(Vetor vetor, int tamVet)
{
    int x, y, aux;

    for (x = 0; x < tamVet - 1; x++)
    {
        for (y = 0; y < tamVet - 1 - x; y++)
        {
            if (vetor[y] > vetor[y + 1])
            {
                aux = vetor[y];
                vetor[y] = vetor[y + 1];
                vetor[y + 1] = aux;
            }
        }
    }
}

void selectionSort(Vetor vetor, int tamVet)
{

    int x, y, menor, aux;
    x = 0;
    while (x < tamVet - 1)
    {
        menor = x;
        y = x + 1;
        while (y < tamVet)
        {
            if (vetor[y] < vetor[menor])
            {
                menor = y;
            }
            y++;
        }
        aux = vetor[x];
        vetor[x] = vetor[menor];
        vetor[menor] = aux;
        x++;
    }
}

void insertionSort(Vetor vetor, int tamVet)
{
    int x, y, pivot;
    x = 1;
    while (x < tamVet)
    {
        y = x - 1;
        pivot = vetor[x];
        while (y >= 0 && pivot < vetor[y])
        {
            vetor[y + 1] = vetor[y];
            y--;
        }
        vetor[y + 1] = pivot;
        x++;
    }
}

void quickSortR(Vetor vetor, int inicio, int fim)
{
    int pivot, i, j, meio, aux;
    i = inicio;
    j = fim;
    meio = (i + j) / 2;
    pivot = vetor[meio];
    while (i <= j)
    {
        while (vetor[i] < pivot)
        {
            i++;
        }
        while (vetor[j] > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    }
    if (inicio < j)
    {
        quickSortR(vetor, inicio, j);
    }
    if (i < fim)
    {
        quickSortR(vetor, i, fim);
    }
}

void quickSort(Vetor vetor, int tamVet)
{
    if (tamVet > 1)
    {
        quickSortR(vetor, 0, tamVet - 1);
    }
}

void mergeSortR(Vetor vetor, Vetor aux, int inicio, int fim)
{

    int a, b, k;
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergeSortR(vetor, aux, inicio, meio);
        mergeSortR(vetor, aux, meio + 1, fim);
        a = inicio;
        b = meio + 1;
        k = inicio;

        while (a <= meio && b <= fim)
        {
            if (vetor[a] < vetor[b])
            {
                aux[k] = vetor[a];
                a++;
            }
            else
            {
                aux[k] = vetor[b];
                b++;
            }
            k++;
        }
        while (a <= meio)
        {
            aux[k] = vetor[a];
            a++;
            k++;
        }
        while (b <= fim)
        {
            aux[k] = vetor[b];
            b++;
            k++;
        }

        for (k = inicio; k <= fim; k++)
        {
            vetor[k] = aux[k];
        }
    }
}

void mergeSort(Vetor vetor, int tamVet)
{
    int *aux;
    aux = (int *)malloc(sizeof(int) * tamVet);
    mergeSortR(vetor, aux, 0, tamVet - 1);
    free(aux);
}