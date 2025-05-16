#include <stdio.h>    // Para entrada e saída padrão
#include <stdlib.h>   // Para malloc, calloc, rand, etc.
#include <time.h>     // Para mudar a seed do rand() de acordo com o tempo
#include <math.h>     // Para funções matemáticas 
#include "../include/vet.h"  // Inclusão do cabeçalho com as definições de funções e tipo Vetor

typedef int *Vetor;  // Define Vetor como ponteiro para int..

// Aloca memória para um vetor de inteiros com o tamanho especificado
void criaVetor(Vetor* vetor, int tamanho)
{
    *vetor = calloc(tamanho, sizeof(int));
}

// Libera a memória alocada para o vetor
void liberaVetor(Vetor* vetor)
{
    free(*vetor);
}

// Copia os elementos do vetor 'entrada' para o vetor 'destino'
void copiaVetor(Vetor destino, Vetor entrada, int tamanho)
{
    for (int x = 0; x < tamanho; x++)
    {
        destino[x] = entrada[x];
    }
}

// Mostra o conteúdo do vetor no formato [a, b, c, ...]
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

// Preenche o vetor com valores aleatórios (sem ordenação)
void populaVetorAleatorio(Vetor vetor, int limite, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = rand()%(limite+1);
    }
}

// Preenche o vetor com valores aleatórios em ordem crescente (positivo)
void populaVetorAleatorioOrdenado(Vetor vetor, int limite, int tamanho)
{
    vetor[0] = rand()%(limite+1);
    for (int i = 1; i < tamanho; i++)
    {
        vetor[i] = vetor[i - 1] + (rand()%limite) + 1;  // Garante que os valores fiquem em ordem crescente
    }
}

void populaVetorParcialmenteOrdenado(Vetor vetor, int limite, int tamanho, int prctDesordem){

    populaVetorAleatorioOrdenado(vetor, limite, tamanho);

    int trocas = prctDesordem*tamanho / 100;
    int j = 0;
    int indice;
    int aux;
    while (j < trocas){
        indice = rand()%tamanho;
        aux = vetor[j];
        vetor[j] = vetor[indice];
        vetor[indice] = aux;
        j++;
    }
}

// Busca sequencial (linear) por um valor no vetor
int buscaSequencialVetor(Vetor vetor, int valor, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (vetor[i] == valor)
        {
            return i;   //Posição do valor encontrado
        }
    }
    return -1;  // Valor não encontrado
}

// Busca binária em vetor ordenado
int buscaBinariaVetor(Vetor vetor, int valor, int tamanho)
{
    int inicio = 0, fim = tamanho - 1, meio;
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
            return meio;  //Posição do valor encontrado
        }
    }
    return -1;  // Valor não encontrado
}

// Ordenação usando o algoritmo Bubble Sort
void bolha(Vetor vetor, int tamVet)
{
    int aux;
    for (int x = 0; x < tamVet - 1; x++)
    {
        for (int y = 0; y < tamVet - 1 - x; y++)
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

// Ordenação usando o algoritmo Selection Sort
void selectionSort(Vetor vetor, int tamVet)
{
    int menor, aux;
    for (int x = 0; x < tamVet - 1; x++)
    {
        menor = x;
        for (int y = x + 1; y < tamVet; y++)
        {
            if (vetor[y] < vetor[menor])
            {
                menor = y;
            }
        }
        aux = vetor[x];
        vetor[x] = vetor[menor];
        vetor[menor] = aux;
    }
}

// Ordenação usando o algoritmo Insertion Sort
void insertionSort(Vetor vetor, int tamVet)
{
    int pivot, y;
    for (int x = 1; x < tamVet; x++)
    {
        pivot = vetor[x];
        y = x - 1;
        while (y >= 0 && pivot < vetor[y])
        {
            vetor[y + 1] = vetor[y];
            y--;
        }
        vetor[y + 1] = pivot;
    }
}

// Função recursiva do Quick Sort
void quickSortR(Vetor vetor, int inicio, int fim)
{
    int i = inicio, j = fim, meio = (i + j) / 2;
    int pivot = vetor[meio], aux;
    while (i <= j)
    {
        while (vetor[i] < pivot) i++;
        while (vetor[j] > pivot) j--;
        if (i <= j)
        {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    }
    if (inicio < j) quickSortR(vetor, inicio, j);
    if (i < fim) quickSortR(vetor, i, fim);
}

// Interface principal para chamar o Quick Sort
void quickSort(Vetor vetor, int tamVet)
{
    if (tamVet > 1)
    {
        quickSortR(vetor, 0, tamVet - 1);
    }
}

// Função recursiva do Merge Sort
void mergeSortR(Vetor vetor, Vetor aux, int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergeSortR(vetor, aux, inicio, meio);
        mergeSortR(vetor, aux, meio + 1, fim);

        int a = inicio, b = meio + 1, k = inicio;

        while (a <= meio && b <= fim)
        {
            if (vetor[a] < vetor[b])
            {
                aux[k++] = vetor[a++];
            }
            else
            {
                aux[k++] = vetor[b++];
            }
        }

        while (a <= meio)
        {
            aux[k++] = vetor[a++];
        }

        while (b <= fim)
        {
            aux[k++] = vetor[b++];
        }

        for (k = inicio; k <= fim; k++)
        {
            vetor[k] = aux[k];  // Copia os elementos ordenados de volta para o vetor original
        }
    }
}

// Interface principal para chamar o Merge Sort
void mergeSort(Vetor vetor, int tamVet)
{
    int *aux = (int *)malloc(sizeof(int) * tamVet);  // Vetor auxiliar para o merge
    mergeSortR(vetor, aux, 0, tamVet - 1);
    free(aux);  // Libera o vetor auxiliar após a ordenação
}
