#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vet.h"

void criaVetor(Vetor *vetor, int tamanho)
{
    vetor = calloc(tamanho, sizeof(int));
}

void copiaVetor(Vetor destino, Vetor entrada, int tamanho)
{
    for (int x = 0; x < tamanho; x++)
    {
        destino[x] = entrada[x];
    }
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

void bolha(Vetor v, int tamVet)
{
    int x, y, aux;

    for (x = 0; x < tamVet - 1; x++)
    {
        for (y = 0; y < tamVet - 1 - x; y++)
        {
            if (v[y] > v[y + 1])
            {
                aux = v[y];
                v[y] = v[y + 1];
                v[y + 1] = aux;
            }
        }
    }
}

void selectionSort(Vetor v, int tamVet)
{

    int x, y, menor, aux;
    x = 0;
    while (x < tamVet - 1)
    {
        menor = x;
        y = x + 1;
        while (y < tamVet)
        {
            if (v[y] < v[menor])
            {
                menor = y;
            }
            y++;
        }
        aux = v[x];
        v[x] = v[menor];
        v[menor] = aux;
        x++;
    }
}

void insertionSort(Vetor v, int tamVet)
{
    int x, y, pivot;
    x = 1;
    while (x < tamVet)
    {
        y = x - 1;
        pivot = v[x];
        while (y >= 0 && pivot < v[y])
        {
            v[y + 1] = v[y];
            y--;
        }
        v[y + 1] = pivot;
        x++;
    }
}

void quickSortR(Vetor v, int inicio, int fim)
{
    int pivot, i, j, meio, aux;
    i = inicio;
    j = fim;
    meio = (i + j) / 2;
    pivot = v[meio];
    while (i <= j)
    {
        while (v[i] < pivot)
        {
            i++;
        }
        while (v[j] > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    }
    if (inicio < j)
    {
        quickSortR(v, inicio, j);
    }
    if (i < fim)
    {
        quickSortR(v, i, fim);
    }
}

void quickSort(Vetor v, int tamVet)
{
    if (tamVet > 1)
    {
        quickSortR(v, 0, tamVet - 1);
    }
}

void mergeSortR(Vetor v, Vetor aux, int inicio, int fim)
{

    int a, b, k;
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergeSortR(v, aux, inicio, meio);
        mergeSortR(v, aux, meio + 1, fim);
        a = inicio;
        b = meio + 1;
        k = inicio;

        while (a <= meio && b <= fim)
        {
            if (v[a] < v[b])
            {
                aux[k] = v[a];
                a++;
            }
            else
            {
                aux[k] = v[b];
                b++;
            }
            k++;
        }
        while (a <= meio)
        {
            aux[k] = v[a];
            a++;
            k++;
        }
        while (b <= fim)
        {
            aux[k] = v[b];
            b++;
            k++;
        }

        for (k = inicio; k <= fim; k++)
        {
            v[k] = aux[k];
        }
    }
}

void mergeSort(Vetor v, int tamVet)
{
    int *aux;
    aux = (int *)malloc(sizeof(int) * tamVet);
    mergeSortR(v, aux, 0, tamVet - 1);
    free(aux);
}