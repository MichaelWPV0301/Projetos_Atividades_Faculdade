#ifndef VETOR_H_INCLUDED
#define VETOR_H_INCLUDED

typedef int *Vetor;

void criaVetor(Vetor vetor, int tamanho);

void copiaVetor(Vetor destino, Vetor entrada, int tamanho);

void populaVetorAleatorioOrdenado(Vetor vetor, int tamanho);

void populaVetorAleatorio(Vetor vetor, int tamanho);

int buscaSequencialVetor(Vetor vetor, int valor, int tamanho);

int buscaBinariaVetor(Vetor vetor, int valor, int tamanho);

void bolha(Vetor vetor, int tamVet);

void selectionSort(Vetor vetor, int tamVet);

void insertionSort(Vetor vetor, int tamVet);

void quickSortR(Vetor vetor, int inicio, int fim);

void quickSort(Vetor vetor, int tamVet);

void mergeSortR(Vetor vetor, Vetor aux, int inicio, int fim);

void mergeSort(Vetor vetor, int tamVet);

#endif